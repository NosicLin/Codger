#ifndef _CODGER_OBJECT_GR_SCOPE_H_
#define _CODGER_OBJECT_GR_SCOPE_H_

#include"gr_object.h"
#include"gr_hash.h"

struct gr_scope
{
	struct gr_scope* s_upper;
	GrHash* s_table;
};
typedef struct gr_scope GrScope;

extern GrTypeInfo Gr_Type_Scope;

GrScope* GrScope_GcNew(GrScope*);
int GrScope_Init(GrScope*,GrScope*);

#endif /*_CODGER_OBJECT_GR_SCOPE_H_*/


	
