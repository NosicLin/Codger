#ifndef _GR_MEMORY_MEMORY_H_
#define _GR_MEMORY_MEMORY_H_
void* Gr_MemAlloc(size_t size);
void Gr_MemFree(void* ptr);

#define  GrMem_Alloc Gr_MemAlloc
#define GrMem_Free Gr_MemFree 

int GrModule_MemInit();
int GrModule_MemExit();

#endif 
