#ifndef _GR_MEMORY_MEM_BASE_H_
#define _GR_MEMORY_MEM_BASE_H_
#include<stdlib.h>

static inline void* Gr_Alloc(size_t size)
{
	size= size==0?1:size;
	return malloc(size);
}

static inline void Gr_Free(void* ptr)
{
	free(ptr);
}

void* Gr_AllocPage();
void Gr_FreePage(void* ptr);
void Gr_PrintAreaNum();

#define GR_PAGE_SHIFT 12 
#define GR_PAGE_SIZE (1ul<<GR_PAGE_SHIFT)
#define GR_PAGE_LOW_MASK (GR_PAGE_SIZE-1)
#define GR_PAGE_HIGH_MASK (~GR_PAGE_LOW_MASK)

#define GR_PAGE_ROUND_LOWER(p) \
	(((unsigned long)(p)+GR_PAGE_LOW_MASK)&GR_PAGE_HIGH_MASK)

#define GR_PAGE_ROUND_UPPER(p) \
	((unsigned long)(p) & GR_PAGE_HIGH_MASK)

#define GR_PAGE_ALIGNED(p) \
	(!((unsigned long)(p) &GR_PAGE_LOW_MASK))

#endif  /*_GR_MEMORY_MEM_BASE_H_*/

