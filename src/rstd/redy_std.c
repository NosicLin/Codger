#include<stdio.h>
#include<stdlib.h>
void* ry_malloc(ssize_t size)
{
	return malloc(size);
}

void ry_free(void* ptr)
{
	free(ptr);
}

void ryerr_nomemory(){}
