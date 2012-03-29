#ifndef _REDY_RSTD_REDY_STD_H_
#define _REDY_RSTD_REDY_STD_H_
#include<sys/types.h>
void* ry_malloc(ssize_t);
void ry_free(void* ptr);
void ryerr_nomemory();

#endif /*_REDY_RSTD_REDY_STD_H_*/
