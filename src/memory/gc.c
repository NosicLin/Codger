#include"gc.h"
#include"memory.h"
#include"mem_base.h"
#include<object/gr_object.h>
#include"utility_c/marocs.h"
#include"utility_c/list_head.h"
#include<string.h>
#include<engine/except.h>
#include<engine/eg_thread.h>
#include<engine/eg_sframe.h>

#define GC_ANALYZE 


#ifdef GRGC_MEM_TOOL_DEBUG 
void* __GrGc_New(size_t size,struct gr_type_info* info)
{
    void* ptr=GrMem_Alloc(size);
    ((GrObject*)ptr)->g_type=info;
    return ptr;
}

void* __GrGc_Alloc(size_t size,struct gr_type_info* info,long flags)
{
    return __GrGc_New(size,info);
}
int GrModule_GcInit(){return 1;}
int GrModule_GcExit(){return 1;}


#else 

#define GC_BLOCK_SIZE GR_PAGE_SIZE

#define GC_ADDR_SHIFT 3
#define GC_ADDR_LOW_MASK ((1ul<<GC_ADDR_SHIFT)-1)
#define GC_ADDR_HIGH_MASK (~GC_ADDR_LOW_MASK)

#define GC_ROUND_ADDR(x) (((x)+GC_ADDR_LOW_MASK)&GC_ADDR_HIGH_MASK)
#define GC_BLOCK_HEADER_NEED GC_ROUND_ADDR(sizeof(struct block_header))

#define GC_MAX_ALLOC_SIZE (GR_PAGE_SIZE-GC_BLOCK_HEADER_NEED)

#define GC_MAX_HEAP_LEVEL 3
#define GC_HEAP_LEVEL_MASK ((1ul<<GC_MAX_HEAP_LEVEL)-1)

#define GC_BLOCK_REF_LOW (1ul<<4)
#define GC_BLOCK_NEED_DESTUCT (1ul<<5)

#define GC_COLLECTION_TIGGER_MIN_BLOCK_NU 100
#define GC_COLLECTION_TIGGER_MAX_BLOCK_NU 10000
#define GC_COLLECTION_TIGGER_OBS_RATIO 2 

struct block_header
{
    struct list_head b_link;
    long b_flags;
    size_t b_free_pos;
    size_t b_max_pos;
#ifdef GRGC_DEBUG
	char* b_name;
	unsigned long b_check_sum;
#endif 
};


struct gc_heap
{
    long g_flags;
    struct list_head g_blocks;
    struct block_header* g_cur;

	size_t g_block_nu;
    size_t g_obs_nu;
	size_t g_last_alive_nu;

	/* scan info,used for garbage collection */
    struct block_header* g_collection;
    size_t g_scan;
#ifdef GRGC_DEBUG
	char* g_name;
#endif 
};

#define GC_GET_BLOCK_HEADER(g) \
    ((struct block_header*)(GR_PAGE_ROUND_UPPER(g)))

#define GC_GET_HEAP_LEVEL(g) \
    (GC_GET_BLOCK_HEADER(g)->b_flags&GC_HEAP_LEVEL_MASK)


#ifdef GRGC_DEBUG 

/* it is usefull when use memory debug tool like valgrind */
void gc_raise_memerr()
{
	int* a=0;
	*a=3;
}
static unsigned long grgc_checksum(unsigned long addr)
{
    return (addr<<8)^(addr>>8);
}

#define GC_OBS_HEADER_CHECK(g) \
	do{ \
		BUG_ON(((unsigned long)(g)&GC_ADDR_LOW_MASK), \
				"addr(g)=%lx",(long)(g));  \
		BUG_ON(((GrObject*)(g))->g_header.g_check_sum!=grgc_checksum((unsigned long)(g)),"addr=%lx",(long)(g)); \
	}while(0)

static inline void GrGc_InitObsHeader(GrObject* g,struct gr_type_info* info)
{
	g->g_header.g_check_sum=grgc_checksum((unsigned long)g);
	g->g_type=info;
	/*
	printf("alloc %s add=%lx, from %s\n",GrObject_Name(g),
			(long)g,
			GC_GET_BLOCK_HEADER(g)->b_name);
	*/
}
#define GC_BLOCK_HEADER_CHECK(b) \
	do{ \
		BUG_ON(!GR_PAGE_ALIGNED(b),"addr=%lx",(long)(b)); \
		BUG_ON(((struct block_header*)(b))->b_check_sum!=grgc_checksum((unsigned long )(b)),"block_addr=%lx,checksum=%lx",(long)(b), \
				((struct block_header*)(b))->b_check_sum); \
	}while(0)

#else 

#define GC_OBS_HEADER_CHECK(g)
#define GC_BLOCK_HEADER_CHECK(b)
#define GrGc_InitObsHeader(g,info) \
	do{ \
		((GrObject*)(g))->g_type=info; \
	}while(0) 

#endif /*GRGC_DEBUG*/




void* __GrGc_New(size_t size,struct gr_type_info*);
void* __GrGc_Alloc(size_t size,struct gr_type_info*,long flags);

void* __GrGc_SafeNew(size_t size,struct gr_type_info*);
void* __GrGc_SafeAlloc(size_t size,struct gr_type_info*);

int GrGc_Collection();




/* every heap has some block link together*/
/* heap.b_blocks                       heap.g_cur
 *      |  	                                |
 *      |                                   |
 *      V                                   V
 * +-----+ ---> +-----+ ---> +-----+ ---> +-----+
 * |     | <--- |     | <--- |     | <--- |     |
 * +-----+      +-----+      +-----+      +-----+
 *                  
 *
 */

/* every block has some objects in it 
 * +--------------+
 * |  Object 1    |
 * |--------------|
 * |  Object 2    |  <--- scan 
 * |--------------|
 * |    .....     |
 * |--------------|
 * |  Object n    |
 * |--------------+
 * |  Frea Area   |  <---- free_pos
 * |   .......    |
 * +--------------+
 */



#ifdef GRGC_DEBUG 
void gc_block_header_print(struct block_header* b)
{
	printf("@block_header\n{\n");
	printf("\tflags=");
	if(b->b_flags&GrGc_HEAP_YOUNG)
	{
		printf("GrGc_HEAP_YOUNG");
	}
	if(b->b_flags&GrGc_HEAP_OLD)
	{
		printf("GRGC_HEAP_OLD");
	}
	if(b->b_flags&GRGC_HEAP_STATIC)
	{
		printf("GRGC_HEAP_STATIC");
	}
	printf("\n");

	printf("\tbegin_ops=%lx\n",(long)b);
	printf("\tfree_pos=%lx\n",(long)(b->b_free_pos));
	printf("\tmax_pos=%lx\n",(long)(b->b_max_pos));
	printf("}\n");
}
void gc_heap_print(struct gc_heap* g)
{
	printf("Heap{\n");
	printf("\tg->name=%s\n",g->g_name);
	printf("\tg->block_nu=%d\n",g->g_block_nu);
	printf("\tg->obs_nu=%d\n",g->g_obs_nu);
	printf("\tg->last_alive_nu=%d\n",g->g_last_alive_nu);
	printf("}\n");
}
#endif 




/* garbage collection heap,total three generation: young,old and static 
 *
 * @young:
 *      object in young heap will be regard as not living too long,
 * so garbage collection work more times here,if after two collection,an
 * object still live, it will be upgrade to old heap
 *
 * @old:
 *      an area not collection too frequently
 *
 * @static:
 *      if an object alloc here,it will alive in all the system running 
 * time,and it address will not change,so before alloc ,
 * think it is really worth.
 */
static struct gc_heap __heap[5];

static struct gc_heap* gc_young=__heap+0;
static struct gc_heap* gc_old=__heap+2;
static struct gc_heap* gc_static=__heap+4;


/* another heap, when garbage collection work,
 * it will move alive object to another area,
 * when collection over,two area
 */

static struct gc_heap* gc_young_anothor=__heap+1;
static struct gc_heap* gc_old_another=__heap+3;

/* two for gc_young,two for old,and one for static */

static int s_collection_switch=1;
static int s_collection_level=0;
static int s_collection_working=0;

#ifdef GRGC_DEBUG
static int s_collection_old_nu=0;
static int s_collection_young_nu=0;
#endif 

static inline int gc_tigger_algrithom(struct gc_heap* g)
{
	int level=g->g_flags&GC_HEAP_LEVEL_MASK;
	if(level==GrGc_HEAP_YOUNG)
	{
		if(g->g_block_nu<GC_COLLECTION_TIGGER_MIN_BLOCK_NU)
		{
			return 0;
		}
		if(g->g_obs_nu>(g->g_last_alive_nu<<GC_COLLECTION_TIGGER_OBS_RATIO))
		{
			return 1;
		}
	}
	if(level==GrGc_HEAP_OLD)
	{
		if(g->g_block_nu<GC_COLLECTION_TIGGER_MIN_BLOCK_NU)
		{
			return 0;
		}
		if(g->g_block_nu>GC_COLLECTION_TIGGER_MAX_BLOCK_NU)
		{
			return 1;
		}
		if(g->g_obs_nu>(g->g_last_alive_nu<<GC_COLLECTION_TIGGER_OBS_RATIO))
		{
			return 1;
		}
	}
	return 0;
}

static inline void gc_tigger_collection(struct gc_heap* g)
{
	int expect_level=g->g_flags&GC_HEAP_LEVEL_MASK;
	if(expect_level==GrGc_HEAP_STATIC)
	{
		return ;
	}
	if(s_collection_working==1)
	{
		return ;
	}
	if(s_collection_switch==0)
	{
		return ;
	}
	if(gc_tigger_algrithom(g))
	{
		EgThread* t=EgThread_GetSelf();
		EG_THREAD_SET_FLAGS(t,EG_THREAD_FLAGS_GC_WORK);
		if(expect_level>s_collection_level)
		{
			s_collection_level=expect_level;
		}
	}

}

static int gc_heap_enlarge(register struct gc_heap* g)
{
	/* alloc a page */
	register struct block_header* h=(struct block_header*)Gr_AllocPage();
	//printf("alloc block addr=%lx \n",(long)h);

	if(h==NULL) return -1;
	h->b_flags=g->g_flags;
	h->b_free_pos=(size_t)h+GC_BLOCK_HEADER_NEED;
	h->b_max_pos=(size_t)h+GC_BLOCK_SIZE;


	/* link to g->g_blocks */
	list_add_tail(&h->b_link,&g->g_blocks);
	g->g_block_nu++;

	/* set cur is h */
	g->g_cur=h;


	gc_tigger_collection(g);

#ifdef GRGC_DEBUG
	h->b_check_sum=grgc_checksum((unsigned long)h);
	h->b_name=g->g_name;
#endif 
	return 0;
}



void* gc_heap_alloc(register struct gc_heap* g,struct gr_type_info* info)
{
	register size_t alloc_size=info->t_size;
	register struct block_header* cur=g->g_cur;

	register size_t ptr=cur->b_free_pos;
	register size_t free_pos=GC_ROUND_ADDR(ptr+alloc_size);


	if(alloc_size>GC_MAX_ALLOC_SIZE)
	{
		WARN("AllocSize(%d) Is Too Big,Max=(%lu)",
				alloc_size,GC_MAX_ALLOC_SIZE);
		return NULL;
	}
	/* check whether current block have enough space to alloc */
	if(free_pos<=cur->b_max_pos)
	{
		cur->b_free_pos=free_pos;
		GrGc_InitObsHeader((GrObject*)ptr,info);
		g->g_obs_nu++;
		if(info->t_ops->t_destruct)
		{
			cur->b_flags|=GC_BLOCK_NEED_DESTUCT;
		}
		return (void*)ptr;
	}
	else  /* enlarge heap */
	{
		if(gc_heap_enlarge(g)<0)
		{
			return NULL;
		}
	}

	/* use new block to alloc */
	cur=g->g_cur;
	ptr=cur->b_free_pos;
	cur->b_free_pos=GC_ROUND_ADDR(ptr+alloc_size);

	GrGc_InitObsHeader((GrObject*)ptr,info);
	g->g_obs_nu++;
	if(info->t_ops->t_destruct)
	{
		cur->b_flags|=GC_BLOCK_NEED_DESTUCT;
	}
	return (void*)ptr;
}





void* __GrGc_New(size_t size,struct gr_type_info* info)
{
	assert(size==info->t_size);
	void* ptr=gc_heap_alloc(gc_young,info);
	return ptr;
}

void* __GrGc_Alloc(size_t size,struct gr_type_info* info,long flags)
{
	assert(size==info->t_size);
	void* ptr=0;
	switch(flags)
	{
		case GrGc_HEAP_YOUNG:
			ptr=gc_heap_alloc(gc_young,info);
			break;
		case GrGc_HEAP_OLD:
			ptr=gc_heap_alloc(gc_old,info);
			break;
		case GrGc_HEAP_STATIC:
			ptr=gc_heap_alloc(gc_static,info);
			break;
		default:
			BUG("UnKown Flags");
	}
	return ptr;
}

struct gc_migrate 
{
	GrObject m_object;
	void* m_addr;
};

#define GC_NEED_UPGRADE(g) ((GrObject*)(g))->g_upgrade
#define GC_IS_REF_LOW(g) ((GrObject*)(g))->g_ref_low

#define GC_COPY_MARK_FLAGS(copy_g,g) \
	do{ \
		((GrObject*)(copy_g))->g_type=((GrObject*)(g))->g_type; \
	}while(0)

#define GC_MARK_REF_LOW_LEVEL(g) \
	do{ \
		((GrObject*)(g))->g_ref_low=1; \
		GC_GET_BLOCK_HEADER(g)->b_flags|=GC_BLOCK_REF_LOW;\
	}while(0)  

#define GC_MARK_NEXT_UPGRADE(g) \
	do{ \
		((GrObject*)(g))->g_upgrade=1; \
	}while(0)

#define GC_MARK_MIGRATE(g,addr) \
	do{ \
		assert(GrObject_Type((GrObject*)(g))->t_size<=GC_MAX_ALLOC_SIZE);\
		g->g_type=(struct gr_type_info*)GrObject_Type((GrObject*)(g))->t_size; \
		((struct gc_migrate*)(g))->m_addr=(void*)(addr); \
	}while(0)

#define GC_IS_MIGRATED(g) ((size_t)((GrObject*)(g))->g_type<=GC_MAX_ALLOC_SIZE)

#define GC_MIGRATED_ADDR(g) (((struct gc_migrate*)(g))->m_addr)

static inline void gc_memcpy(GrObject* des,GrObject* src,size_t length)
{
	BUG_ON(GrObject_Type(des)->t_size!=length,"%d!=%d",
			GrObject_Type(des)->t_size,length);
	memcpy((char*)des+sizeof(GrObject),
			(char*)src+sizeof(GrObject),
			length-sizeof(GrObject));
}






void* GrGc_Update(void* ptr)
{
#ifdef GRGC_DEBUG
	GC_OBS_HEADER_CHECK(ptr);
	struct block_header* bh=GC_GET_BLOCK_HEADER(ptr);
	GC_BLOCK_HEADER_CHECK(bh);
#endif 

	GrObject* g=(GrObject*)ptr;
	GrObject* copy_g;
	struct gr_type_info* info;
	int g_level=GC_GET_HEAP_LEVEL(g);



	/* if current only collection young area,
	 * but g object alloc in old area or static area,
	 * so just return it 
	 */
	if(g_level>s_collection_level)
	{
		return g;
	}

	/* copy object to another area 
	 * and return copied address
	 */

	if(GC_IS_MIGRATED(g))
	{
		return GC_MIGRATED_ADDR(g);
	}
	/*
	   printf("g_level=%d,name=%s,block_addr=%lx,s_collection_level=%d ",
	   g_level,GC_GET_BLOCK_HEADER(ptr)->b_name,
	   (long)GC_GET_BLOCK_HEADER(ptr),
	   s_collection_level);
	   printf("object_name=%s addr=%lx\n",GrObject_Name(g),(long)g);
	   */

	/* g object come from youn area */
	info=GrObject_Type(g);
	if(g_level==GrGc_HEAP_YOUNG)
	{
		/* check upgrade g or not */
		if(GC_NEED_UPGRADE(g))
		{
			/* upgrade g object to old area,
			 * mask it ref young object */
			if(s_collection_level==GrGc_HEAP_OLD)
			{
				copy_g=gc_heap_alloc(gc_old_another,info);
			}
			else
			{
				copy_g=gc_heap_alloc(gc_old,info);
			}
			if(copy_g==NULL)
			{
				GrGc_MemErr();
				return NULL;
			}
			GC_MARK_REF_LOW_LEVEL(copy_g);
		}
		/* object is too younger, so we still alloc it from youn area
		 * if next time garbage collection work, it still alive,it will 
		 * be upgrade to old area
		 */
		else 
		{
			copy_g=gc_heap_alloc(gc_young_anothor,info);
			if(copy_g==NULL)
			{
				GrGc_MemErr();
				return NULL;
			}
			GC_MARK_NEXT_UPGRADE(copy_g);
		}
		gc_memcpy(copy_g,g,info->t_size);
		GC_MARK_MIGRATE(g,copy_g);
		return copy_g;

	}
	/* collection level is GrGc_HEAP_OLD, so object in old area also 
	 * copy to another old area 
	 */
	if(g_level==GrGc_HEAP_OLD)
	{
		copy_g=gc_heap_alloc(gc_old_another,info);
		if(copy_g==NULL)
		{
			GrGc_MemErr();
			return NULL;
		}
		GC_COPY_MARK_FLAGS(copy_g,g);
		gc_memcpy(copy_g,g,info->t_size);
		GC_MARK_MIGRATE(g,copy_g);
		return copy_g;
	}

	/* never here */
	assert(0);
	return NULL;
}

static int gc_level_valied(int level)
{
	if(level==GrGc_HEAP_YOUNG)
	{
		return 1;
	}
	if(level==GrGc_HEAP_OLD)
	{
		return 1;
	}
	return 0;
}


static int gc_heap_scan_all(struct gc_heap* h)
{
	register struct gc_heap* cur_heap=h;

	register struct block_header* cur_block=h->g_collection;
	register size_t scan=cur_heap->g_scan;

	register size_t obs_size;
	register GrObject* cur_obs;

	int ret=0;


	//assert((cur_heap->g_flags&GC_HEAP_LEVEL_MASK)<=s_collection_level);
	while(1)
	{
		/* First scan all object in cur_block */
		while(scan<cur_block->b_free_pos)
		{
			cur_obs=(GrObject*) scan;

			GC_OBS_HEADER_CHECK(cur_obs);
			GrObject_GcUpdate(cur_obs);

			obs_size=GrObject_Type(cur_obs)->t_size;
			scan+=GC_ROUND_ADDR(obs_size);
		}
		/* if this block is not last block,so change cur_block
		 * and scan it */
		if(cur_block->b_link.next!=&cur_heap->g_blocks)
		{
			cur_block=list_entry(cur_block->b_link.next,
					struct block_header,b_link);

			scan=((size_t)cur_block)+GC_BLOCK_HEADER_NEED;
			continue;
		}
		/* all object in heap has scaned */
		break;
	}

	/* check whether we have scaned objects or not */
	if(cur_heap->g_collection!=cur_block||cur_heap->g_scan!=scan)
	{
		ret=1;
	}
	else 
	{
		ret=0;
	}

	/* update scan info */
	cur_heap->g_collection=cur_block;
	cur_heap->g_scan=scan;

	return ret;
}


/* only scan object in heap that reference low level object */
static int gc_heap_scan_mark_low(struct gc_heap* h)
{

	register struct gc_heap* cur_heap=h;

	register struct block_header* cur_block=h->g_collection;
	register size_t scan=cur_heap->g_scan;


	register size_t obs_size;
	register GrObject* cur_obs;

	int ret=0;

	assert((cur_heap->g_flags&GC_HEAP_LEVEL_MASK)>s_collection_level);

	while(1)
	{
		/* if cur_block has object reference low level object*/
		if(cur_block->b_flags&GC_BLOCK_REF_LOW)
		{
			while(scan<cur_block->b_free_pos)
			{
				cur_obs=(GrObject*) scan;
				GC_OBS_HEADER_CHECK(cur_obs);
				obs_size=GrObject_Type(cur_obs)->t_size;
				if(GC_IS_REF_LOW(cur_obs))
				{
					GrObject_GcUpdate(cur_obs);
				}
				scan+=GC_ROUND_ADDR(obs_size);
			}
		}
		/* scan next block */
		if(cur_block->b_link.next!=&cur_heap->g_blocks)
		{
			cur_block=list_entry(cur_block->b_link.next,
					struct block_header,b_link);

			scan=((size_t)cur_block)+GC_BLOCK_HEADER_NEED;
			continue;
		}
		break;
	}

	if(cur_heap->g_collection!=cur_block||cur_heap->g_scan!=scan)
	{
		ret=1;
	}
	else 
	{
		ret=0;
	}

	/* update collection info */
	cur_heap->g_collection=cur_block;
	cur_heap->g_scan=scan;

	return ret;
}

static int gc_heap_destory(struct gc_heap* h)
{
	struct block_header* cur_block;
	size_t scan;

	GrObject* cur_obs;
	size_t obs_size;

	/* traver every block and destruct every garbage object in block 
	 * then free block 
	 */
	while(!list_empty(&h->g_blocks))
	{
		cur_block=list_entry(h->g_blocks.next,struct block_header,b_link);
		list_del(&cur_block->b_link);

		if(cur_block->b_flags&GC_BLOCK_NEED_DESTUCT)
		{
			scan=(size_t)cur_block+GC_BLOCK_HEADER_NEED;
			while(scan<cur_block->b_free_pos)
			{
				cur_obs=(GrObject*)scan;
				if(GC_IS_MIGRATED(cur_obs))
				{
					obs_size=(size_t)cur_obs->g_type;
				}
				else
				{
					obs_size=GrObject_Type(cur_obs)->t_size;
					GrObject_Destruct(cur_obs);
				}
				scan+=GC_ROUND_ADDR(obs_size);
			}
		}
		/*
		   printf("free %s block addr=%lx\n",cur_block->b_name,
		   (long)(cur_block));
		   */
#ifdef GRGC_DEBUG
		cur_block->b_check_sum=0;
#endif
		Gr_FreePage(cur_block);
	}

	return 0;
}


static inline int gc_heap_init(struct gc_heap* h,long level)
{
	INIT_LIST_HEAD(&h->g_blocks);
	h->g_flags=level;
	h->g_cur=0;
	h->g_obs_nu=0;
	h->g_last_alive_nu=0;
	h->g_block_nu=0;
	h->g_collection=0;
	h->g_scan=0;
#ifdef GRGC_DEBUG
	if(level==GrGc_HEAP_YOUNG)
	{
		h->g_name="Young";
	}
	else if(level==GrGc_HEAP_OLD)
	{
		h->g_name="Old";
	}
	else if (level==GrGc_HEAP_STATIC)
	{
		h->g_name="Static";
	}
	else 
	{
		assert(0);
	}
#endif 
	if(gc_heap_enlarge(h)<0)
	{
		return -1;
	}

	return 0;
}

static inline void gc_heap_init_collection_info(struct gc_heap* h)
{
	h->g_collection=list_entry(h->g_blocks.next,
			struct block_header,b_link);
	h->g_scan=(size_t)(h->g_collection)+GC_BLOCK_HEADER_NEED;
}


static int gc_collection_begin()
{
	if(s_collection_level==GrGc_HEAP_YOUNG)
	{
		//printf("init youn another\n");
		if(gc_heap_init(gc_young_anothor,GrGc_HEAP_YOUNG)<0)
		{
			return -1;
		}
		gc_heap_init_collection_info(gc_young_anothor);
		gc_heap_init_collection_info(gc_old);
		gc_heap_init_collection_info(gc_static);

		return 0;
	}
	else if(s_collection_level==GrGc_HEAP_OLD)
	{
		if(gc_heap_init(gc_young_anothor,GrGc_HEAP_YOUNG)<0)
		{
			return -1;
		}

		if(gc_heap_init(gc_old_another,GrGc_HEAP_OLD)<0)
		{
			return -1;
		}

		gc_heap_init_collection_info(gc_young_anothor);
		gc_heap_init_collection_info(gc_old_another);
		gc_heap_init_collection_info(gc_static);
		return 0;
	}
	else 
	{
		assert(0);
	}
	return -1;

}

static void gc_collection_end()
{
	struct gc_heap* temp;
	if(s_collection_level==GrGc_HEAP_YOUNG)
	{
		temp=gc_young;
		gc_young=gc_young_anothor;
		gc_young_anothor=temp;
		gc_heap_destory(gc_young_anothor);

		gc_young->g_last_alive_nu=gc_young->g_obs_nu;
	}
	else if(s_collection_level==GrGc_HEAP_OLD)
	{
		temp=gc_young;
		gc_young=gc_young_anothor;
		gc_young_anothor=temp;

		gc_heap_destory(gc_young_anothor);
		gc_young->g_last_alive_nu=gc_young->g_obs_nu;

		temp=gc_old;

		gc_old=gc_old_another;
		gc_old_another=temp;

		gc_heap_destory(gc_old_another);
		gc_old->g_last_alive_nu=gc_old->g_obs_nu;
	}
	else
	{
		assert(0);
	}
}





int GrGc_CleanGarbage()
{
	BUG_ON(!gc_level_valied(s_collection_level),"level=%d",s_collection_level);
	if(gc_tigger_algrithom(gc_old))
	{
		s_collection_level=GrGc_HEAP_OLD;
	}

#ifdef GRGC_DEBUG
	if(s_collection_level==GrGc_HEAP_YOUNG)
	{
		s_collection_young_nu++;
	}
	if(s_collection_level==GrGc_HEAP_OLD)
	{
		s_collection_old_nu++;
	}
#endif 

	s_collection_working=1;
	gc_collection_begin();

	EgThread* t=EgThread_GetSelf();

	/* Roots:
	 *  1)Data Stack;
	 *  2)StackFrame;
	 *  3)Modules
	 *  4)EgThread->relval
	 */

	/* First Update Data Stack */
	GrObject** dstack=t->t_dstack;
	assert(dstack);
	size_t sp=t->t_sp;
	size_t i;
	//	printf("begin scan data stack......\n");
	for(i=0;i<sp;i++)
	{
		dstack[i]=GrGc_Update(dstack[i]);
	}

	/* Second Update StackFrame */
	//	printf("begin scan stack frame......\n");
	EgSframe* cur_sf=t->t_fstack;
	while(cur_sf!=NULL)
	{
		cur_sf->f_scope=(GrScope*)GrGc_Update((GrScope*)(cur_sf->f_scope));
		cur_sf->f_host=GrGc_Update(cur_sf->f_host);
		cur_sf=cur_sf->f_link;
	}

	/* Thirdth Update Module */
	/* TODO */

	/* Fourth Update EgThread->retval */

	//	printf("begin EgThread->t_relval .....\n");
	if(t->t_relval!=NULL)
	{
		t->t_relval=GrGc_Update(t->t_relval);
	}
	//	printf("begin EgThread->t_host .....\n");
	t->t_host=GrGc_Update(t->t_host);


	/* Scan Heap And Update Object */
	if(s_collection_level==GrGc_HEAP_YOUNG)
	{
		while(1)
		{
			//			printf("begin scan gc_static......\n");
			//if(gc_heap_scan_all(gc_static))
			if(gc_heap_scan_mark_low(gc_static))
			{
				continue;
			}
			//			printf("begin scan gc_old......\n");
			//if(gc_heap_scan_all(gc_old))
			if(gc_heap_scan_mark_low(gc_old))
			{
				continue;
			}
			//			printf("begin scan gc_young_anothor......\n");
			if(gc_heap_scan_all(gc_young_anothor))
			{
				continue;
			}

			/* scan over */
			break;
		}
	}
	else if(s_collection_level==GrGc_HEAP_OLD)
	{
		while(1)
		{
			//			printf("begin scan gc_static......\n");
			//if(gc_heap_scan_all(gc_static))
			if(gc_heap_scan_mark_low(gc_static))
			{
				continue;
			}
			//			printf("begin scan gc_old_another......\n");
			if(gc_heap_scan_all(gc_old_another))
			{
				continue;
			}
			//			printf("begin scan gc_young_anothor......\n");
			if(gc_heap_scan_all(gc_young_anothor))
			{
				continue;
			}
			break;
		}
	}
	else
	{
		assert(0);
	}

	gc_collection_end();
	s_collection_level=0;
	s_collection_working=0;

	return 0;
}
void GrGc_Intercept(void* d,void* s)
{
	GC_OBS_HEADER_CHECK(d);
	GC_OBS_HEADER_CHECK(s);

	if(GC_GET_HEAP_LEVEL(d)>GC_GET_HEAP_LEVEL(s))
	{
		GC_MARK_REF_LOW_LEVEL(d);
	}
}
void GrGc_MarkRefLow(void* ptr)
{
	GC_OBS_HEADER_CHECK(ptr);
	GC_MARK_REF_LOW_LEVEL(ptr);
}

int GrGc_IsRefLow(void* ptr)
{
	return GC_IS_REF_LOW(ptr);
}

void GrGc_Disable()
{
	s_collection_switch=0;
}
void GrGc_Enable()
{
	s_collection_switch=1;
}


int GrModule_GcInit()
{
#ifdef GRGC_DEBUG
	__heap->g_name="Heap0";
	(__heap+1)->g_name="Heap1";
	(__heap+2)->g_name="Heap2";
	(__heap+3)->g_name="Heap3";
	(__heap+4)->g_name="Heap4";
#endif 
	if(gc_heap_init(gc_young,GrGc_HEAP_YOUNG)<0)
	{
		return -1;
	}
	if(gc_heap_init(gc_old,GrGc_HEAP_OLD)<0)
	{
		return -1;
	}
	if(gc_heap_init(gc_static,GrGc_HEAP_STATIC)<0)
	{
		return -1;
	}
	return 0;
}

int GrModule_GcExit()
{
	/*
	   printf("Collection Times Info{\n");
	   printf("\t YoungArea=%d\n",s_collection_young_nu);
	   printf("\t OldArea=%d\n",s_collection_old_nu);
	   printf("}\n");
	   */

	/*
	   gc_heap_print(gc_young);
	   gc_heap_print(gc_old);
	   gc_heap_print(gc_static);
	   */
	gc_heap_destory(gc_young);
	gc_heap_destory(gc_old);
	gc_heap_destory(gc_static);
	return 0;
}

void GrGc_MemErr()
{
	GrErr_MemFormat("Can't Alloc Memory For Garbage collection");
	assert(0);
}

#endif 
