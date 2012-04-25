/*  level one wrapper c lib call  malloc realloc free */
void* GrMem_Malloc(size_t);
void* GrMem_Realloc(void* ptr,size_t);
void GrMem_Free(void* ptr);

#define GrMem_New(type,n) \
	((type*) GrMem_Malloc(sizeof(type)*(n)))

#define GrMem_Del GrMem_Free


/* level two GrPool, cache memory */


struct GrPoolHeader{
	struct list_head p_silbing;
};


