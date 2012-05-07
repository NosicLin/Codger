#ifndef _CODGER_OBJECT_CLASS_H_
#define _CODGER_OBJECT_CLASS_H_
#include"gr_object.h"
#include"gr_hash.h"
#include"gr_string.h"
#include"gr_symbol.h"

struct gr_class
{
	INHERIT_GROBJECT;
	struct gr_class* c_inhert;
	GrHash* c_symbols;
	GrHash* c_template;
};

typedef struct gr_class GrClass;

GrTypeInfo Gr_Type_Class;

GrClass* GrClass_GcNew();
GrClass* GrClass_GcNewFlag(long);

static inline void GrClass_SetInherit(GrClass* c,GrClass* g)
{
	c->c_inhert=g;
}

static inline void GrClass_SetTemplate(GrClass* c,GrHash* t)
{
	c->c_template=t;
}

int GrClass_SetAttr(GrClass*,GrObject*,GrObject*);
GrObject* GrClass_GetAttr(GrClass*,GrObject*);
int GrClass_AddAttr(GrClass*,GrSymbol*,GrObject*);

GrObject* GrClass_CreateInstance(GrClass*);



#endif 

