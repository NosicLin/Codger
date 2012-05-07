#ifndef _CODGER_OBJECT_LOCAL_FUNC_H_
#define _CODGER_OBJECT_LOCAL_FUNC_H_
#include"gr_object.h"
#include"gr_array.h"


typedef GrObject* (*GrCFunc)(GrObject*,GrArray*);

struct gr_inner_func
{
	INHERIT_GROBJECT;
	long i_as_exe;
	long i_args_nu;
	GrCFunc i_func;
};

typedef struct gr_inner_func GrInnerFunc;

extern GrTypeInfo Gr_Type_Inner_Func;

GrInnerFunc* GrInnerFunc_GcNew(GrCFunc,long);
GrInnerFunc* GrInnerFunc_GcNewFlag(GrCFunc,long,long);

GrObject* GrInnerFunc_Call(GrInnerFunc*,GrObject*,GrArray*);

static inline void GrInnerFunc_SetAsExecute(GrInnerFunc* f)
{
	f->i_as_exe=1;
}
static inline void GrInnerFunc_ClrAsExecute(GrInnerFunc* f)
{
	f->i_as_exe=0;
}


#endif 

