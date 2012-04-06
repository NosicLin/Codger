#ifndef _CODGER_RSTD_GR_STD_H_
#define _CODGER_RSTD_GR_STD_H_
#include<sys/types.h>
void* gr_malloc(ssize_t);
void gr_free(void* ptr);
void grerr_nomemory();
#endif 
