#ifndef _CODGER_OBJECT_INSTANCE_H_
#define _CODGER_OBJECT_INSTANCE_H_

#include"gr_object.h"
#include"gr_hash.h"

struct gr_instance
{
	INHERIT_GROBJECT;
	GrHash* i_symbols;
};

typedef struct gr_instance GrInstance;

extern struct gr_type_ops instance_type_ops;

GrInstance* GrInstance_GcNew(GrTypeInfo* );
GrInstance* GrInstance_GcNewFlag(GrTypeInfo* ,long);

int GrInstance_Print(GrInstance*,FILE*);


GrObject* GrInstance_GetAttr(GrInstance*,GrObject*);
int GrInstance_SetAttr(GrInstance*,GrObject*,GrObject*);


#endif 


