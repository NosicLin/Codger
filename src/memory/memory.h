#ifndef _GR_MEMORY_MEMORY_H_
#define _GR_MEMORY_MEMORY_H_
void* Gr_MemAlloc(size_t size);
void Gr_MemFree(void* ptr);

int GrModule_MemInit();

#endif 
