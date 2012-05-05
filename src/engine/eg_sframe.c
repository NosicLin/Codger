#include"eg_sframe.h"
#include<memory/memory.h>
#include"except.h"
#include<string.h>

EgSframe* EgSframe_NewFromFunc(GrFunc* func)
{
	EgSframe* sf=GrMem_Alloc(sizeof(*sf));
	if(sf==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For EgSframe");
		return NULL;
	}
	memset(sf,0,sizeof(*sf));

	GrScope* sc=GrScope_GcNew(func->f_livein);
	if(sc==NULL)
	{
		GrMem_Free(sf);
		return NULL;
	}
	sf->f_scope=sc;
	sf->f_codes=func->f_codes;
	return sf;
}

EgSframe* EgSframe_NewFromModule(GrModule* m)
{

	EgSframe* sf=GrMem_Alloc(sizeof(*sf));
	if(sf==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For EgSframe");
		return NULL;
	}
	memset(sf,0,sizeof(*sf));

	GrScope* sc=GrScope_GcNew(NULL);
	if(sc==NULL)
	{
		GrMem_Free(sf);
		return NULL;
	}
	sf->f_scope=sc;
	sf->f_codes=m->m_codes;
	return sf;
}


