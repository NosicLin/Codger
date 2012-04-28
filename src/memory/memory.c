#include"memory.h"
#include"mem_base.h"
#include<utility_c/marocs.h>
#include<utility_c/list_head.h>
#include<string.h>
#include<assert.h>

#define GR_MEM_SMALL_BLOCK 256 
#define GR_MEM_ALIGN_SIZE (1ul<<3)
#define GR_MEM_ALIGN_SHIFT 3
#define GR_MEM_ALIGN_LOW_MASK (GR_MEM_ALIGN_SIZE-1)
#define GR_MEM_ALIGN_HIGH_MASK (~GR_MEM_ALIGN_LOW_MASK)

#define GR_MEM_ROUND_LOWER(x) \
	(GR_MEM_ALIGN_HIGH_MASK&((x)+GR_MEM_ALIGN_LOW_MASK))

#define GR_MEM_ROUND_UPPER(x) \
	(GR_MEM_ALIGN_HIGH_MASK&(x))

#define GR_SIZE_TO_BLOCK_IDX(x) \
	(x==0?0:(((x)-1)>>GR_MEM_ALIGN_SHIFT))

#define GR_MEM_MAX_SLOT_NU (256>>GR_MEM_ALIGN_SHIFT)

#define DEFAULT_PAGES_IDX_NU 1024

struct block_header
{
	struct block_header* b_next;
};

struct page_header
{
	struct list_head p_link;
	struct block_header* p_free_block;

	int p_page_idx;
	short int p_slot_idx;
	short int p_block_used;
	short int p_free_pos;
};

struct slot_header
{
	struct list_head s_free_page;
	struct list_head s_full_page;
	short int s_block_size;
	short int s_alloc_offset;
	short int s_block_nu;

};

static struct slot_header slots[GR_MEM_SMALL_BLOCK>>GR_MEM_ALIGN_SHIFT];


/* static  data used pages_index */
static void** pages_idx_array=0;
static int pages_idx_cap=DEFAULT_PAGES_IDX_NU;
static int pages_idx_free_pos=0;
static int pages_idx_next=-1;


static inline int page_idx_enlarge()
{
	int enlarge_size=pages_idx_cap<<1;
	if(enlarge_size<0)
	{
		return -1;
	}
	void** new_idx=(void**)Gr_Alloc(enlarge_size*sizeof(void*));
	if(new_idx==NULL)
	{
		return -1;
	}
	memcpy(new_idx,pages_idx_array,sizeof(void*) * pages_idx_cap);
	Gr_Free(pages_idx_array);
	pages_idx_array=new_idx;
	pages_idx_cap=enlarge_size;
	return 0;
}
static inline int pages_idx_alloc(void* ptr)
{

	int ret;
	if(pages_idx_next!=-1)
	{
		ret=pages_idx_next;
		pages_idx_next=(int) pages_idx_array[ret];
		pages_idx_array[ret]=ptr;
		return ret;
	}
	if(pages_idx_free_pos==pages_idx_cap)
	{
		if(page_idx_enlarge()<0)
		{
			return -1;
		}
	}
	ret=pages_idx_free_pos++;
	pages_idx_array[ret]=ptr;
	return ret;
}

static inline void pages_idx_free(int pos)
{
	assert(pos<pages_idx_free_pos);
	pages_idx_array[pos]=(void*)pages_idx_next;
	pages_idx_next=pos;
}













void* slot_alloc(register struct slot_header* s)
{
	register struct block_header* ptr;
	register struct page_header* h=0;
	int page_idx=0;
	/* make sure this is free page to alloc */
	if(list_empty(&s->s_free_page))
	{
		h=(struct page_header*)Gr_AllocPage();
		if(h==NULL)
		{
			return NULL;
		}
		page_idx=pages_idx_alloc((void*)h);
		if(page_idx<0)
		{
			Gr_FreePage(h);
			return NULL;
		}

		/* init page_header */ 
		memset(h,0,sizeof(*h));

		h->p_slot_idx=(s-slots);

		h->p_page_idx=page_idx;

		list_add(&h->p_link,&s->s_free_page);

		h=0;
	}
	/* get the free page*/
	h=list_entry(s->s_free_page.next,struct page_header,p_link);

	/* alloc a block from page */
	if(h->p_free_block)
	{
		ptr=h->p_free_block;
		h->p_free_block=ptr->b_next;
	}
	else
	{
		assert(h->p_free_pos<s->s_block_nu);
		ptr=(struct block_header*)((unsigned long)h+s->s_alloc_offset+
					h->p_free_pos++*s->s_block_size);
	}
	h->p_block_used++;

	/* if all block in page has allocate
	 * link it to s_full_page
	 */

	if(h->p_block_used==s->s_block_nu)
	{
		list_del(&h->p_link);
		list_add(&h->p_link,&s->s_full_page);
	}
	return (void*) ptr;
}




void* Gr_MemAlloc(size_t size)
{
	/* if size is bigger than GR_MEM_SMALL_BLOCK
	 * alloc it from c lib heap 
	 */
	if(size>GR_MEM_SMALL_BLOCK)
	{
		return Gr_Alloc(size);
	}

	/* size is smaller than GR_MEM_SMALL_BLOCK
	 * used our method to quick alloc 
	 */

	/* map size to slot */
	int idx=GR_SIZE_TO_BLOCK_IDX(size);

	/* get slot_header */
	struct slot_header* s=&slots[idx];
	void* ptr=0;

	ptr=slot_alloc(s);
	return ptr;
}

void Gr_MemFree(void* ptr)
{
	register struct block_header* b=(struct block_header*)ptr;
	register struct page_header* h=(struct page_header*)GR_PAGE_ROUND_UPPER(ptr);
	assert(GR_PAGE_ALIGNED(h));
	register struct slot_header* s;

	/* if ptr come from c lib heap, reference h->p_page_idx is safe
	 * because operating system organize memory by page */

	register int page_idx=h->p_page_idx;


	/* if page_idx >=pages_idx_free_pos,
	 * we can sure it come from c lib heap
	 */
	if(page_idx>=pages_idx_free_pos)
	{
		Gr_Free(ptr);
		return ;
	}

	/* confirm where ptr come from */
	if(pages_idx_array[page_idx]!=(void*)h)
	{
		/* ptr alloc from c lib heap */
		Gr_Free(ptr);
		return;
	}

	assert(h->p_slot_idx<GR_MEM_MAX_SLOT_NU);

	s=&slots[h->p_slot_idx];

	/* all the block in the page has previously allocate,
	 * now it belong to free page,so link it to s_free_page
	 */

	if(h->p_block_used==s->s_block_nu)
	{
		list_del(&h->p_link);
		list_add_tail(&h->p_link,&s->s_free_page);
	}

	h->p_block_used--;
	b->b_next=h->p_free_block;
	h->p_free_block=b;

	/* if all block in page are free,we free the page to mem_base */
	if(h->p_block_used==0)
	{
		list_del(&h->p_link);
		Gr_FreePage(h);
		pages_idx_free(page_idx);
	}
}


int GrModule_MemInit()
{
	pages_idx_array=(void**)Gr_Alloc(DEFAULT_PAGES_IDX_NU*sizeof(void*));
	if(pages_idx_array==NULL)
	{
		return -1;
	}
	int i=0;
	struct slot_header* s;
	for(i=0;i<GR_MEM_MAX_SLOT_NU;i++)
	{
		s=&slots[i];
		INIT_LIST_HEAD(&s->s_free_page);
		INIT_LIST_HEAD(&s->s_full_page);
		s->s_block_size=(i+1)<<GR_MEM_ALIGN_SHIFT;
		s->s_alloc_offset=GR_MEM_ROUND_LOWER(sizeof(struct page_header));
		s->s_block_nu=(GR_PAGE_SIZE-s->s_alloc_offset)/s->s_block_size;

	}
	return 0;
}





		


	

	
















