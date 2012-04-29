#ifndef _CODGER_OBJECT_ROBJECT_H_
#define _CODGER_OBJECT_ROBJECT_H_
#include<stdio.h>
struct gr_type_info;

struct  gr_object 
{
	struct gr_type_info* g_type;
};
typedef struct gr_object GrObject;

#include"type_info.h"

#define INHERIT_GROBJECT struct gr_object g_base 
#define TO_GROBJECT(x) ((GrObject*)x)

#define GR_TYPE_ADDR_MASK (~((1ul<<2)-1))
static inline GrTypeInfo* GrObject_Type(GrObject* gr)
{
	return (GrTypeInfo*)((size_t)(gr->g_type)&GR_TYPE_ADDR_MASK);
}

#define GR_CMP_NOT_SUPPORT -2
extern GrObject* GR_OPS_NOT_SUPPORT;
	
#endif /*_CODGER_OBJECT_ROBJECT_H_*/




