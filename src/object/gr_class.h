#ifndef _CODGER_OBJECT_CLASS_H_
#define _CODGER_OBJECT_CLASS_H_
#include"gr_object.h"
#include"gr_hash.h"
#include"gr_string.h"
#include"gr_symbol.h"
#include"gr_instance.h"

#define GR_CLASS_PERM_MASK ((0x1l<<3)-1)

#define GR_CLASS_STATIC (0x1<<4)

#define GR_CLASS_PUBLIC (0x1l)
#define GR_CLASS_PROTECTED (0x1l<<1)
#define GR_CLASS_PRIVATE (0x1l<<2)

struct gr_class
{
	INHERIT_GROBJECT;
	struct gr_class* c_inhert;
	GrString* c_name;
	GrHash* c_symbols;
	GrHash* c_template;
	GrTypeInfo* c_instance_type;
};

typedef struct gr_class GrClass;

extern GrTypeInfo Gr_Type_Class;


GrClass* GrClass_GcNew();
GrClass* GrClass_GcNewFlag(long);

int GrClass_SetInherit(GrClass* c,GrObject* g);

static inline void GrClass_SetTemplate(GrClass* c,GrHash* t)
{
	c->c_template=t;
}
static inline int GrClass_Verify(GrObject* g)
{
	return GrObject_Type(g)==&Gr_Type_Class;
}

int GrClass_SetAttr(GrClass*,GrObject*,GrObject*);
GrObject* GrClass_GetAttr(GrClass*,GrObject*);
int GrClass_AddAttr(GrClass*,GrObject*,GrObject*);

int GrClass_TemplateAdd(GrClass*,GrObject*,GrObject*);


GrInstance* GrClass_CreateInstance(GrClass*);
GrInstance* GrClass_CreateInstanceFlag(GrClass*,long);



#endif 

