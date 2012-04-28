#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SLOT_SIZE (1024*1024)
int* ptr[SLOT_SIZE];

int main()
{
	//	GrModule_MemInit();
	int i=0;
	int size=0;
	srand((unsigned int)time(NULL));

	for(i=0;i<SLOT_SIZE;i++)
	{
		size=rand()%500+1;

		ptr[i]=malloc(size);
		*(ptr[i])=1;
		assert(ptr[i]!=NULL);
	}

	int j=0;
	while(j<100)
	{

		for(i=j%1;i<SLOT_SIZE;i+=2)
		{
			free(ptr[i]);
		}
		for(i=j%1;i<SLOT_SIZE;i+=2)
		{
			size=rand()%500+1;
			ptr[i]=malloc(size);
			*(ptr[i])=1;
		}
		j++;
	}
	for(i=0;i<SLOT_SIZE;i++)
	{
		free(ptr[i]);
	}

	return 0;
}




