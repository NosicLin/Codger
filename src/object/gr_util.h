#ifndef _CODGER_OBJECT_UTIL_H_
#define _CODGER_OBJECT_UTIL_H_
#include"gr_inner_func.h"
#include"gr_hash.h"
#include"gr_symbol.h"

struct gr_inner_func_entry
{
	const char* e_name;
	long  e_permission;
	GrCFunc e_func;
	long e_arg_nu;
};

typedef struct gr_inner_func_entry GrInnerFuncEntry;

GrHash* GrUtil_CreateInnerMethodsFlag(GrInnerFuncEntry*,long);
int GrUtil_FillInnerMethodsFlag(GrHash*,GrInnerFuncEntry*,long);

int GrUtil_FillWithGrString(GrHash*,GrInnerFuncEntry*,long);

int GrUtil_CheckSetAttr(GrSymbol*,long);
int GrUtil_CheckGetAttr(GrSymbol*,long);

int GrUtil_HashNotSupport(GrObject*);
GrObject* GrUtil_BaseTypeGetAttr(GrObject*,GrObject*,long);
int GrUtil_BaseTypeSetAttr(GrObject*,GrObject*,GrObject*,long);

#endif 

