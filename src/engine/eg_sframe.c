#include"eg_sframe.h"
#include<memory/memory.h>
#include"except.h"
#include<string.h>
#include<object/gr_consts.h>
#define SFRAME_CACHE_MAX_NU 200

static EgSframe* sframe_caches[SFRAME_CACHE_MAX_NU];
static int sframe_caches_nu=0; 

static inline EgSframe* egsframe_alloc_cache()
{
	EgSframe* sf=NULL;
	if(sframe_caches_nu>0)
	{
		sf=sframe_caches[--sframe_caches_nu];
	}
	else
	{
		sf=GrMem_Alloc(sizeof(*sf));
	}
	return sf;
}



EgSframe* EgSframe_NewFromFunc(GrFunc* func)
{
	EgSframe* sf=egsframe_alloc_cache();
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
	sf->f_host=Gr_Object_Nil;
	sf->f_scope=sc;
	sf->f_codes=func->f_codes;
	sf->f_relval=NULL;
	return sf;
}

EgSframe* EgSframe_NewFromModule(GrModule* m)
{
	EgSframe* sf=egsframe_alloc_cache();
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
	sf->f_host=Gr_Object_Nil;
	sf->f_scope=sc;
	sf->f_codes=m->m_codes;
	return sf;
}

void EgSframe_Free(EgSframe* f)
{
	if(sframe_caches_nu>SFRAME_CACHE_MAX_NU)
	{
		GrMem_Free(f);
	}
	else
	{
		sframe_caches[sframe_caches_nu++]=f;
	}

}

