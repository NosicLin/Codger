#include"memory.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SLOT_SIZE 1000
int* ptr[SLOT_SIZE]={0};

int main()
{
	GrModule_MemInit();
	int i=0;
	int size=0;
	srand((unsigned int)time(NULL));

	for(i=0;i<SLOT_SIZE;i++)
	{
		size=8;
		ptr[i]=Gr_MemAlloc(size);
		*(ptr[i])=2;
		assert(ptr[i]!=NULL);
	}
	int j=0;
	while(j<2)
	{
		for(i=j%1;i<SLOT_SIZE;i+=2)
		{
			Gr_MemFree(ptr[i]);
		}
		for(i=j%1;i<SLOT_SIZE;i+=2)
		{
			size=8;
			ptr[i]=Gr_MemAlloc(size);
			*(ptr[i])=2;
		}
		j++;

	}
	for(i=0;i<SLOT_SIZE;i++)
	{
		Gr_MemFree(ptr[i]);
	}
	return 0;
}




