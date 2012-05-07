#include"gr_util.h"
#include"gr_symbol.h"
#include"gr_hash.h"
#include"gr_class.h"
#include<utility_c/marocs.h>
#include<engine/except.h>



GrHash* GrUtil_CreateInnerMethodsFlag(GrInnerFuncEntry* es,long flags)
{
	GrHash* h=GrHash_GcNewFlag(flags);
	if(h==NULL) return NULL;
	if(GrUtil_FillInnerMethodsFlag(h,es,flags)<0)
	{
		return NULL;
	}
	return h;
}


int GrUtil_FillInnerMethodsFlag(GrHash* h,GrInnerFuncEntry* es,long flags)
{
	GrSymbol* s;
	GrInnerFunc* f;
	int ret;

	while(es->e_name!=NULL)
	{

		s=GrSymbol_GcNewFlagFromStr(es->e_name,es->e_permission,flags);
		if(s==NULL) return -1;
		assert(((GrObject*)s)->g_type);
		f=GrInnerFunc_GcNewFlag(es->e_func,es->e_arg_nu,flags);
		if(f==NULL) return -1;

		ret=GrHash_Map(h,(GrObject*)s,(GrObject*)f);
		if(ret<0) return -1;
		es++;
	}
	return 0;
}



GrObject* GrUtil_BaseTypeGetAttr(GrObject* g,GrObject* k,long perm)
{
	GrTypeInfo* g_type=GrObject_Type(g);

	GrClass* g_class=g_type->t_class;

	BUG_ON(g_class==NULL,"%s.t_class Filed Not Init",GrObject_Name(g));

	GrHashEntry* entry=GrHash_GetEntry(g_class->c_template,k);
	if(!GrHashEntry_Valid(entry))
	{
		if(GrString_Verify(k))
		{
			GrErr_NameFormat("%s Has No Symbol '%s'",
					GrObject_Name(g),((GrString*)k)->s_value);
			return NULL;
		}
		else 
		{
			GrErr_NameFormat("%s' Hash No Such Symbol",GrObject_Name(g));
			return NULL;
		}
	}
	assert(GrSymbol_Verify(entry->e_key));
	if(!GrUtil_CheckGetAttr((GrSymbol*)(entry->e_key),perm))
	{
		return NULL;
	}
	return entry->e_value;
}

int GrUtil_BaseTypeSetAttr(GrObject* g,GrObject* k,GrObject* v,long perm)
{
	if(GrString_Verify(k))
	{
		GrErr_NameFormat("%s Has No Symbol '%s'",GrObject_Name(g),((GrString*)k)->s_value);
	}
	else
	{
		GrErr_NameFormat("%s Hash No Such Symbol",GrObject_Name(g));
	}
	return -1;
}



int GrUtil_CheckSetAttr(GrSymbol* sy,long perm)
{
	return 1;
}
int GrUtil_CheckGetAttr(GrSymbol* sy,long perm)
{
	return 1;
}



ssize_t GrUtil_HashNotSupport(GrObject* x)
{
	GrErr_HashFormat("%s Not Support Hash");
	return -1;
}

























