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

#ifdef GRGC_DEBUG

static long grgc_checksum(long addr)
{
	return (addr<<8)^(addr>>8);
}

static inline void GrGC_HeaderCheck(GrObject* g)
{
	assert(g->g_header.g_check_sum==grgc_checksum((long)g));
}
static inline void GrGc_InitHeader(GrObject* g,struct gr_type_info* info)
{
	g->g_header.g_check_sum=grgc_checksum((long)g);
	g->g_type=info;
}

#else 
#define GrGC_HeaderCheck(g)
#define GrGc_InitHeader(g,info) ((GrObject*)(g))->g_type=info

#endif /*GRGC_DEBUG*/



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

void* __GrGc_New(size_t size,struct gr_type_info*);
void* __GrGc_Alloc(size_t size,struct gr_type_info*,long flags);

void* __GrGc_SafeNew(size_t size,struct gr_type_info*);
void* __GrGc_SafeAlloc(size_t size,struct gr_type_info*);

int GrGc_Collection();

struct block_header
{
	struct list_head b_link;
	long b_flags;
	size_t b_free_pos;
	size_t b_max_pos;
};

struct gc_heap
{
	long g_flags;
	struct list_head g_blocks;
	struct block_header* g_cur;
	int g_obs_nu;

	struct block_header* g_collection;
	size_t g_scan;
};


#define GC_GET_BLOCK_HEADER(g) \
	((struct block_header*)((long)(g)&GC_ADDR_HIGH_MASK))

#define GC_GET_HEAP_LEVEL(g) \
	(GC_GET_BLOCK_HEADER(g)->b_flags&GC_HEAP_LEVEL_MASK)



#if 0
static void gc_block_header_print(struct block_header* b)
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
#endif 




/* garbage collection heap,total three generation: young,old and static 
 *
 * @young:
 * 		object in young heap will be regard as not living too long,
 * so garbage collection work more times here,if after two collection,an
 * object still live, it will be upgrade to old heap
 *
 * @old:
 * 		an area not collection too frequently
 *
 * @static:
 * 		if an object alloc here,it will alive in all the system running 
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

static int gc_heap_enlarge(register struct gc_heap* g)
{
	/* alloc a page */
	register struct block_header* h=(struct block_header*)Gr_AllocPage();

	if(h==NULL) return -1;
	h->b_flags=g->g_flags;
	h->b_free_pos=(size_t)h+GC_BLOCK_HEADER_NEED;
	h->b_max_pos=(size_t)h+GC_BLOCK_SIZE;

	/* link to g->g_blocks */
	list_add(&h->b_link,&g->g_blocks);

	/* set cur is h */
	g->g_cur=h;
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
		GrGc_InitHeader((GrObject*)ptr,info);
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

	GrGc_InitHeader((GrObject*)ptr,info);
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

static int s_collection_level=0;
static struct gr_type_info s_migrate={};
#define GC_NEED_UPGRADE(g) (g)->g_upgrade
#define GC_IS_REF_LOW(g) (g)->g_ref_low

#define GC_COPY_MARK_FLAGS(copy_g,g) \
	do{ \
		(copy_g)->g_type=(g)->g_type; \
	}while(0)

#define GC_MARK_REF_LOW_LEVEL(g) \
	do{ \
		g->g_ref_low=1; \
	}while(0)  

#define GC_MARK_NEXT_UPGRADE(g) \
	do{ \
		g->g_upgrade=1; \
	}while(0)

#define GC_MARK_MIGRATE(g,addr) \
	do{ \
		g->g_type=&s_migrate; \
		((struct gc_migrate*)(g))->m_addr=(void*)(addr); \
	}while(0)

#define GC_IS_MIGRATED(g) ((g)->g_type==&s_migrate)

#define GC_MIGRATED_ADDR(g) (((struct gc_migrate*)(g))->m_addr)

static inline void gc_memcpy(GrObject* des,GrObject* src,size_t length)
{
	memcpy((char*)des+sizeof(GrObject),
			(char*)src+sizeof(GrObject),
			length-sizeof(GrObject));
}
		





void* GrGc_Update(void* ptr)
{
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
			GC_COPY_MARK_FLAGS(copy_g,g);
			GC_MARK_REF_LOW_LEVEL(copy_g);
		}
		else
		{
			copy_g=gc_heap_alloc(gc_young_anothor,info);
			if(copy_g==NULL)
			{
				GrGc_MemErr();
				return NULL;
			}
			GC_COPY_MARK_FLAGS(copy_g,g);
			GC_MARK_NEXT_UPGRADE(copy_g);
		}

		gc_memcpy(copy_g,g,info->t_size);
		GC_MARK_MIGRATE(g,copy_g);
		return copy_g;
	}
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

	assert((cur_heap->g_flags&GC_HEAP_LEVEL_MASK)<s_collection_level);
	while(1)
	{
		while(scan<cur_block->b_free_pos)
		{
			cur_obs=(GrObject*) scan;
			obs_size=GrObject_Type(cur_obs)->t_size;

			GrObject_GcUpdate(cur_obs);
			scan+=obs_size;
		}
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

	cur_heap->g_collection=cur_block;
	cur_heap->g_scan=scan;

	return ret;
}

static int gc_heap_scan_mark_low(struct gc_heap* h)
{

	register struct gc_heap* cur_heap=h;

	register struct block_header* cur_block=h->g_collection;
	register size_t scan=cur_heap->g_scan;


	register size_t obs_size;
	register GrObject* cur_obs;

	int ret=0;

	assert((cur_heap->g_flags&GC_HEAP_LEVEL_MASK)<s_collection_level);
	while(1)
	{

		while(scan<cur_block->b_free_pos)
		{
			cur_obs=(GrObject*) scan;
			obs_size=GrObject_Type(cur_obs)->t_size;
			if(GC_IS_REF_LOW(cur_obs))
			{
				GrObject_GcUpdate(cur_obs);
			}
			scan+=obs_size;
		}
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

	cur_heap->g_collection=cur_block;
	cur_heap->g_scan=scan;

	return ret;
}

int gc_heap_destory()
{
	/*TODO */

	return 0;
}


static inline int gc_heap_init(struct gc_heap* h,long level)
{
	INIT_LIST_HEAD(&h->g_blocks);
	h->g_flags=level;
	h->g_cur=0;
	h->g_obs_nu=0;
	h->g_collection=0;
	h->g_scan=0;
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
	}
	else if(s_collection_level==GrGc_HEAP_OLD)
	{
		temp=gc_young;
		gc_young=gc_young_anothor;
		gc_young_anothor=temp;

		gc_heap_destory(gc_young_anothor);

		temp=gc_old;
		gc_old=gc_old_another;
		gc_old_another=temp;

		gc_heap_destory(gc_old_another);
	}
	else
	{
		assert(0);
	}
}





int GrGc_Collection(int level)
{
	gc_collection_begin();

	assert(gc_level_valied(level));
	s_collection_level=level;


	EgThread* t=EgThread_GetSelf();

	/* Roots:
	 * 	1)Data Stack;
	 * 	2)StackFrame;
	 * 	3)Modules
	 */

	/* First Update Data Stack */
	GrObject** dstack=t->t_dstack;
	assert(dstack);
	size_t sp=t->t_sp;
	size_t i;
	for(i=0;i<sp;i++)
	{
		dstack[i]=GrGc_Update(dstack[i]);
	}

	/* Second Update StackFrame */
	EgSframe* cur_sf=t->t_fstack;
	while(cur_sf!=NULL)
	{
		cur_sf->f_scope=(GrScope*)GrGc_Update((GrScope*)(cur_sf->f_scope));
		cur_sf->f_host=GrGc_Update(cur_sf->f_host);
		cur_sf=cur_sf->f_link;
	}

	/* Thirdth Update Module */
	/* TODO */


	/* Scan Heap And Update Object */
	if(s_collection_level==GrGc_HEAP_YOUNG)
	{
		while(1)
		{
			if(gc_heap_scan_mark_low(gc_static))
			{
				continue;
			}
			if(gc_heap_scan_mark_low(gc_old))
			{
				continue;
			}
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
			if(gc_heap_scan_mark_low(gc_static))
			{
				continue;
			}
			if(gc_heap_scan_all(gc_old_another))
			{
				continue;
			}
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
	return 0;
}


int GrModule_GcInit()
{
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
	gc_heap_destory(gc_young);
	gc_heap_destory(gc_old);
	gc_heap_destory(gc_static);
	return 0;
}

void GrGc_MemErr()
{
	GrErr_MemFormat("Can't Alloc Memory For Garbage collection");
}

#endif 
