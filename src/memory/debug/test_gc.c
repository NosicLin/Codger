#include"memory.h"
#include"object/gr_object.h"
#include"gc.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SLOT_SIZE (1024*1024)
int* ptr[SLOT_SIZE]={0};
struct gr_type_info t_info[257];

int main()
{
	GrModule_MemInit();
	GrModule_GcInit();

	int i=0;
	for(i=0;i<257;i++)
	{
		t_info[i].t_size=i;
	}
	int size=0;
	srand((unsigned int)time(NULL));

	for(i=0;i<SLOT_SIZE;i++)
	{
		size=rand()%256+1;
		ptr[i]=GrGc_New(int,t_info+size);
		*(ptr[i])=2;
		assert(ptr[i]!=NULL);
	}
	int j=0;
	while(j<10)
	{
		for(i=j%1;i<SLOT_SIZE;i+=2)
		{
			size=rand()%256+1;
			ptr[i]=GrGc_New(int,t_info+size);
			*(ptr[i])=2;
		}
		j++;

	}
	GrModule_MemExit();
	return 0;
}




