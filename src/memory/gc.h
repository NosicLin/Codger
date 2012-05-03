#ifndef _GR_MEMORY_GC_H_
#define _GR_MEMORY_GC_H_


#define GrGc_New(TypeName,type_info) \
	((TypeName*)__GrGc_New(sizeof(TypeName),type_info))

#define GrGc_HEAP_YOUNG (1ul<<0)
#define GrGc_HEAP_OLD (1ul<<1)
#define GrGc_HEAP_STATIC (1ul<<2)

#define GRGC_HEAP_YOUNG GrGc_HEAP_YOUNG 
#define GRGC_HEAP_OLD GrGc_HEAP_OLD 
#define GRGC_HEAP_STATIC GrGc_HEAP_STATIC

#define GrGc_Alloc(TypeName,type_info,flags) \
	((TypeName*)__GrGc_Alloc(sizeof(TypeName),type_info,flags))

#define GrGc_AllocStatic(TypeName,type_info)\
	((TypeName*)__GrGc_Alloc(sizeof(TypeName),type_info,GrGc_HEAP_STATIC))

#define GrGc_AllocYoung(TypeName,type_info) \
	((TypeName*)__GrGc_Alloc(sizeof(TypeName),type_info,GrGc_HEAP_YONG))

#define GrGc_AllocOld(TypeName,type_info) \
	((TypeName*)__GrGc_Alloc(sizeof(TypeName),type_info,GrGc_HEAP_OLD))


struct gr_type_info;

void* __GrGc_New(size_t size,struct gr_type_info*);
void* __GrGc_Alloc(size_t size,struct gr_type_info*,long flags);


#define GrGc_SafeNew(TypeName,type_info) \
	((TypeName*)__GrGc_SafeNew(sizeof(TypeName),type_info))

#define GrGc_SafeAlloc(TypeName,type_info,flags) \
	((TypeName*) __GrGc_SafeAlloc(sizeof(TypeName),type_info,flags))

#define GrGc_SafeAllocStatic(TypeName,type_info) \
	((TypeName*) __GrGc_SafeAlloc(sizeof(TypeName),type_info,GrGc_HEAP_STATIC))

#define GrGc_SafeAllocYoung(TypeName,type_info) \
	((TypeName*) __GrGc_SafeAlloc(sizeof(TypeName),type_info,GrGc_HEAP_YONG))

#define GrGc_SafeAllocOld(TypeName,type_info) \
	((TypeName*) __GrGc_SafeAlloc(sizeof(TypeName),type_info,GrGc_HEAP_OLD))

void* __GrGc_SafeNew(size_t size,struct gr_type_info*);
void* __GrGc_SafeAlloc(size_t size,struct gr_type_info*);

int GrGc_Collection();

int GrModule_GcInit();
int GrModule_GcExit();

#endif  /*_GR_MEMORY_GC_H_*/

