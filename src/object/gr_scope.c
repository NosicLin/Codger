#include"gr_scope.h"
#include<memory/gc.h>
#include<memory/memory.h>
#include<engine/except.h>

GrScope* GrScope_GcNew(GrScope* upper)
{
	GrScope* s=GrGc_New(GrScope,&Gr_Type_Scope);
	if(s==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Scope Object");
		return NULL;
	}
	if(GrScope_Init(s,upper)<0)
	{
		return NULL;
	}
	return s;
}

inline int GrScope_Init(GrScope* s,GrScope* upper)
{
	GrHash* h=GrHash_GcNew();
	if(h==NULL)
	{
		return -1;
	}
	s->s_table=h;
	s->s_upper=upper;
	return 0;
}


