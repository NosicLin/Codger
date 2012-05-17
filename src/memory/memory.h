#ifndef _GR_MEMORY_MEMORY_H_
#define _GR_MEMORY_MEMORY_H_

#include"mem_base.h"

#define GR_MEM_TOOL_DEBUG
#ifdef  GR_MEM_TOOL_DEBUG

#define GrMem_Alloc Gr_Alloc
#define GrMem_Free Gr_Free

#else

#define  GrMem_Alloc Gr_MemAlloc
#define GrMem_Free Gr_MemFree 

#endif  /*MEM_TOOL_DEBUG*/

void* Gr_MemAlloc(size_t size);
void Gr_MemFree(void* ptr);


int GrModule_MemInit();
int GrModule_MemExit();

#endif 
