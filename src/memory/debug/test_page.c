#include"mem_base.h"
#include"assert.h"
#include<stdio.h>

#define SLOT_SIZE (1024*128)
void* ptr[SLOT_SIZE];

int main()
{

	int i;
	/*
	printf("Page_Shift=%d\n",GR_PAGE_SHIFT);
	printf("Page_Size=%ld\n",GR_PAGE_SIZE);
	printf("Page_Low_Mask=%lx\n",GR_PAGE_LOW_MASK);
	printf("Page_High_Mask=%lx\n",GR_PAGE_HIGH_MASK);
	*/
	int j=0;
	while(j<10)
	{
		for(i=0;i<SLOT_SIZE/3;i++)
		{
			ptr[i]=Gr_AllocPage();
			assert(GR_PAGE_ALIGNED(ptr[i]));
			*((int*)(ptr[i]+4))=i;

		}

		for(i=0;i<SLOT_SIZE/6;i++)
		{
			assert(*((int*)(ptr[i]+4))==i);
			Gr_FreePage(ptr[i]);
			assert(GR_PAGE_ALIGNED(ptr[i]));

		}
		for(i=0;i<SLOT_SIZE/6;i++)
		{
			ptr[i]=Gr_AllocPage();
			assert(GR_PAGE_ALIGNED(ptr[i]));
			*((int*)(ptr[i]+4))=i;
		}


		for(i=SLOT_SIZE/3;i<SLOT_SIZE/2;i++)
		{
			ptr[i]=Gr_AllocPage();
			assert(GR_PAGE_ALIGNED(ptr[i]));
			*((int*)(ptr[i]+4))=i;
		}

		for(i=0;i<SLOT_SIZE/3;i++)
		{
			assert(*((int*)(ptr[i]+4))==i);
			Gr_FreePage(ptr[i]);
			assert(GR_PAGE_ALIGNED(ptr[i]));

		}
		for(i=0;i<SLOT_SIZE/3;i++)
		{
			ptr[i]=Gr_AllocPage();
			assert(GR_PAGE_ALIGNED(ptr[i]));
			*((int*)(ptr[i]+4))=i;
		}


		for(i=SLOT_SIZE/2;i<SLOT_SIZE;i++)
		{
			ptr[i]=Gr_AllocPage();
			assert(GR_PAGE_ALIGNED(ptr[i]));
			*((int*)(ptr[i]+4))=i;
		}

		for(i=0;i<SLOT_SIZE;i++)
		{
			assert(*((int*)(ptr[i]+4))==i);
			Gr_FreePage(ptr[i]);
			assert(GR_PAGE_ALIGNED(ptr[i]));
		}

		j++;
	}
	return 0;
}





