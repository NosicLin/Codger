#ifndef _CODGER_OBJECT_ARRAY_H_
#define _CODGER_OBJECT_ARRAY_H_
#include"gr_object.h"
#include<assert.h>
#define GR_ARRAY_SMALL_SIZE 12

#define GR_ARRAY_DEBUG
struct gr_array
{
	INHERIT_GROBJECT;
	long a_flags;
	ssize_t a_cap;
	ssize_t a_size;
	struct gr_object** a_objects;
};

typedef struct gr_array GrArray;
extern GrTypeInfo Gr_Type_Array;

struct gr_array_iter
{
	INHERIT_GROBJECT;
	GrArray* i_host;
	size_t i_cur_pos;
};

typedef struct gr_array_iter GrArrayIter;
extern GrTypeInfo Gr_Type_Array_Iter;


GrArray* GrArray_GcNew();
GrArray* GrArray_GcNewFlag(long);
GrArray* GrArray_GcNewWithSize(ssize_t size);

int GrArray_Init(GrArray*);
int GrArray_Resize(GrArray*);

int GrArray_Push(GrArray*,GrObject* item);
GrObject* GrArray_Pop(GrArray*);

int GrArray_Set(GrArray*,ssize_t index,GrObject* item);
GrObject* GrArray_Get(GrArray*,ssize_t index);

int GrArray_Insert(GrArray*,ssize_t index,GrObject* item);
int GrArray_Remove(GrArray*,ssize_t index);

GrArray* GrArray_Plus(GrArray* ,GrArray*);

GrArrayIter* GrArray_Iter(GrArray*);

GrArrayIter* GrArrayIter_GcNew(GrArray* host);
GrObject* GrArrayIter_Next(GrArrayIter* iter);

static inline ssize_t GrArray_Size(GrArray* ga)
{
	return ga->a_size;
}

int GrArray_Bool(GrArray*);
int GrArray_Print(GrArray*,FILE* f);

static inline int GrArray_Verify(GrObject* ga)
{
	return  GrObject_Type(ga)==&Gr_Type_Array;
}



#ifdef GR_ARRAY_DEBUG
static inline GrArray* GR_TO_A(GrObject* g)
{
	assert(GrArray_Verify(g));
	return (GrArray*)g;
}
static inline GrObject* A_TO_GR(GrArray* g)
{
	return (GrObject*) g;
}
#else 

#define GR_TO_A(x) ((GrArray*)(x))
#define GA_TO_R(x) ((GrObject*)(x))

#endif  /*GR_ARRAY_DEBUG*/

#endif /*_CODGER_OBJECT_ARRAY_H_*/




