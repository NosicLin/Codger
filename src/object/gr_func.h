#ifndef _CODGER_OBJECT_FUNC_H_
#define _CODGER_OBJECT_FUNC_H_
#include"gr_object.h"
#include"gr_array.h"
#include"gr_scope.h"
#include"gr_opcode.h"

#define GR_FUNC_DEBUG

struct gr_func
{
	INHERIT_GROBJECT;
	GrScope* f_livein;
	GrArray* f_default_args;
	GrOpcode* f_codes;
};
typedef struct gr_func GrFunc;
extern GrTypeInfo Gr_Type_Func;

GrFunc* GrFunc_GcNew();
GrFunc* GrFunc_GcNewFlag(long);
static inline void GrFunc_SetScope(GrFunc* f,GrScope* s)
{
	f->f_livein=s;
}
static inline void GrFunc_SetDefaultArgs(GrFunc* f,GrArray* args)
{
	f->f_default_args=args;
}
static inline void GrFunc_SetOpcode(GrFunc* f,GrOpcode* op)
{
	f->f_codes=op;
}

static inline int GrFunc_Verify(GrObject* f)
{
	return GrObject_Type(f)==&Gr_Type_Func;
}

GrObject* GrFunc_Call(GrFunc*,GrArray*);

#ifdef GR_FUNC_DEBUG
static inline GrFunc* GR_TO_FUNC(GrObject* f)
{
	assert(GrFunc_Verify(f));
	return (GrFunc*) f;
}
static inline GrObject* FUNC_TO_GR(GrFunc* f)
{
	return (GrObject*) f;
}
#else 

#define GR_TO_FUNC(x) ((GrFunc*)(x))
#define FUNC_TO_GR(x) ((GrObject*)(x))

#endif /*GR_FUNC_DEBUG*/

#endif  /* _CODGER_OBJECT_FUNC_H_*/



