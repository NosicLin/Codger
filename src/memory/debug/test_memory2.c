#include"memory.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SLOT_SIZE  20
void* ptr[SLOT_SIZE];

int main()
{
	GrModule_MemInit();
	int i=0;
	int size=0;
	srand((unsigned int)time(NULL));
	
	for(i=0;i<SLOT_SIZE;i++)
	{
		size=20;

		ptr[i]=Gr_MemAlloc(size);
		assert(ptr[i]!=NULL);
		printf("%lu \n",(unsigned long)ptr[i]);
	}
	for(i=0;i<SLOT_SIZE;i++)
	{
		Gr_MemFree(ptr[i]);
	}
	return 0;
}




