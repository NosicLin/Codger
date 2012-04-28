#include"mem_base.h"
#include<utility_c/marocs.h>
#include<utility_c/list_head.h>
#include<assert.h>

/* area size 1M,used for alloc page */
#define GR_AREA_SIZE 1024*1024


//#define GR_AREA_SUPPORT_CACHE
#ifdef GR_AREA_SUPPORT_CACHE
#define GR_AREA_CACHE_NU 200
static struct area_header* area_cached[GR_AREA_CACHE_NU];
static int area_free_nu=0;
#endif 

struct page_header
{
	/* used to link free page together */
	struct page_header* p_next;
};

struct area_header
{
	struct list_head a_link;
	/* pointer to a big area, and split it by page size */
	unsigned long  a_block;	

	/* make sure round page */
	unsigned long  a_alloc_start;

	/* free page link together */
	struct page_header* a_free_pages;

	/* all page number */
	int a_page_nu;

	/* current alloc pos */
	short int a_free_pos;

	/* page_used */
	short int a_page_used;
	
};

static inline void print_area(struct area_header* h)
{
	printf("area_header{\n");
	printf("\ta_block=%lx\n",h->a_block);
	printf("\ta_alloc_start=%lx\n",h->a_alloc_start);
	printf("\ta_page_nu=%d\n",h->a_page_nu);
	printf("\ta_free_pos=%d\n",h->a_free_pos);
	printf("\ta_page_used=%d\n",h->a_page_used);
	printf("}\n");
}


static struct area_header* alloc_area()
{
#ifdef GR_AREA_SUPPORT_CACHE
	if(area_free_nu)
	{
		return area_cached[--area_free_nu];
	}
#endif 

	struct area_header* h=(struct area_header*)malloc(sizeof(*h)+GR_AREA_SIZE);
	if(h==NULL) return NULL;
	INIT_LIST_HEAD(&h->a_link);
	h->a_block=(unsigned long)h+sizeof(*h);
	h->a_alloc_start=GR_PAGE_ROUND_LOWER(h->a_block);
	h->a_free_pages=NULL;
	h->a_page_nu=(GR_AREA_SIZE-(h->a_alloc_start-h->a_block))>>GR_PAGE_SHIFT;
	h->a_free_pos=0;
	h->a_page_used=0;

//	print_area(h);
	return h;
}
	


static void free_area(struct area_header* h)
{
#ifdef GR_AREA_SUPPORT_CACHE
	if(area_free_nu<GR_AREA_CACHE_NU)
	{
		area_cached[area_free_nu++]=h;
		return ;
	}
#endif
	assert(h->a_page_used==0);
	free(h);

}

inline void* area_alloc_page(struct area_header* h)
{
	struct page_header* p=0;
	if(h->a_free_pages)
	{
		p=h->a_free_pages;
		h->a_free_pages=p->p_next;
		h->a_page_used++;
		return (void*) p;
	}
	if(h->a_free_pos<h->a_page_nu)
	{
		h->a_page_used++;
		return (void*) (h->a_alloc_start+((h->a_free_pos++)<<GR_PAGE_SHIFT));

	}

	/* all page in area is allcoate */
	return NULL;
}


inline int page_belong_to_area(struct area_header* h,void* ptr)
{
	int shift_count;
	if((unsigned long)ptr>=h->a_alloc_start)
	{
		shift_count= ((unsigned long)ptr-h->a_alloc_start)>>GR_PAGE_SHIFT;
		if(shift_count<h->a_page_nu)
		{
			return 1;
		}
	}
	return 0;
}





inline void area_free_page(struct area_header* h ,void* ptr)
{
	assert(GR_PAGE_ALIGNED(ptr));
	assert(page_belong_to_area(h,ptr));

	struct page_header* p=(struct page_header*)ptr;
	p->p_next=h->a_free_pages;
	h->a_free_pages=p;

	h->a_page_used--;
}

inline int area_all_page_free(struct area_header* h)
{
	return h->a_page_used==0;
}
inline int area_full(struct area_header* h)
{
	return h->a_page_used==h->a_page_nu;
}

/* link together area has free page */
LIST_HEAD(area_page_free_link);

/* link together area that allcoate all its pages */
LIST_HEAD(area_page_full_link);

void* Gr_AllocPage()
{
	struct area_header* h=0;
	void* page=0;

	/* if area_page_free_link is empty */
	/* alloc a area */
	if(list_empty(&area_page_free_link))
	{
		h=alloc_area();
		if(h==NULL)
		{
			return NULL;
		}
		list_add(&h->a_link,&area_page_free_link);
		h=NULL;
	}
	/* get the first area in area_page_free_link */
	h=list_entry(area_page_free_link.next,struct area_header,a_link);

	/* take a page from area*/
	page=area_alloc_page(h);

	assert(page);

	/* if all page in area area allocate */
	/* move it to area_page_full_link */
	if(area_full(h))
	{
		list_del(&h->a_link);
		list_add(&h->a_link,&area_page_full_link);
	}
	return page;
}

void Gr_FreePage(void* ptr)
{

	assert(GR_PAGE_ALIGNED(ptr));

	struct area_header* h=0;


	/* travserse area_page_free_link to find page's area */
	list_for_each_entry(h,&area_page_free_link,a_link)
	{
		/* if ptr is in area range */
		if(page_belong_to_area(h,ptr))
		{
			area_free_page(h,ptr);

			/* if all page in are is not used,
			 * give back it to operating system 
			 */
			if(area_all_page_free(h))
			{
				list_del(&h->a_link);
				free_area(h);
			}
			return ;
		}
	}


	/* travserse area_page_full_link to find page's area */
	list_for_each_entry(h,&area_page_full_link,a_link)
	{
		/* if ptr is in area range */
		if(page_belong_to_area(h,ptr))
		{

			area_free_page(h,ptr);
			/* not area has free page,so move it to area_page_free_link */
			list_del(&h->a_link);
			list_add_tail(&h->a_link,&area_page_free_link);
			return ;
		}
	}

	BUG("Find Page's Area Failed");


}
