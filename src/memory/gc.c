#include"gc.h"
#include"memory.h"
#include"mem_base.h"
#include<object/gr_object.h>
#include"utility_c/marocs.h"
#include"utility_c/list_head.h"


#define GC_BLOCK_SIZE GR_PAGE_SIZE

#define GC_ADDR_SHIFT 3
#define GC_ADDR_LOW_MASK ((1ul<<GC_ADDR_SHIFT)-1)
#define GC_ADDR_HIGH_MASK (~GC_ADDR_LOW_MASK)

#define GC_ROUND_ADDR(x) (((x)+GC_ADDR_LOW_MASK)&GC_ADDR_HIGH_MASK)
#define GC_BLOCK_HEADER_NEED GC_ROUND_ADDR(sizeof(struct block_header))

#define GC_MAX_ALLOC_SIZE (GR_PAGE_SIZE-GC_BLOCK_HEADER_NEED)


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
};


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

//static struct gc_heap* gc_young_anothor=__heap+1;
//static struct gc_heap* gc_old_another=__heap+3;

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
		*(struct gr_type_info**)ptr=info;
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
	*(struct gr_type_info**)ptr=info;
	return (void*)ptr;
}





void* __GrGc_New(size_t size,struct gr_type_info* info)
{
	return gc_heap_alloc(gc_young,info);
}

void* __GrGc_Alloc(size_t size,struct gr_type_info* info,long flags)
{
	switch(flags)
	{
		case GrGc_HEAP_YONG:
			return gc_heap_alloc(gc_young,info);
		case GrGc_HEAP_OLD:
			return gc_heap_alloc(gc_old,info);
		case GrGc_HEAP_STATIC:
			return gc_heap_alloc(gc_static,info);
	}

	BUG("UnKown Flags");
	return NULL;
}

int GrModule_GcInit()
{
	int i=0;
	struct gc_heap* g;
	for(g=__heap;i<5;i++,g++)
	{
		INIT_LIST_HEAD(&g->g_blocks);
		g->g_cur=0;
		g->g_obs_nu=0;
		if(gc_heap_enlarge(g)<0)
		{
			return -1;
		}
	}
	__heap[0].g_flags=GrGc_HEAP_YONG;
	__heap[1].g_flags=GrGc_HEAP_YONG;
	__heap[2].g_flags=GrGc_HEAP_OLD;
	__heap[3].g_flags=GrGc_HEAP_OLD;
	__heap[4].g_flags=GrGc_HEAP_STATIC;
	return 0;
}

int GrModule_GcExit()
{
	/*TODO*/
	return 0;
}
