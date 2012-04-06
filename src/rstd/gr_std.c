#include<stdlib.h>
#include<stdio.h>
#include"gr_std.h"
void*  gr_malloc(ssize_t size)
{
	return malloc(size);

}
void gr_free(void* ptr)
{
	free(ptr);
}
void grerr_nomemory(){}
