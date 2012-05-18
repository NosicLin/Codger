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

int GrUtil_FillWithGrString(GrHash* h,GrInnerFuncEntry* es,long flags)
{
	GrString* s;
	GrInnerFunc* f;
	int ret;

	while(es->e_name!=NULL)
	{

		s=GrString_GcNewFlag(es->e_name,flags);
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
	assert(GrString_Verify(k));
	GrTypeInfo* g_type=GrObject_Type(g);

	GrClass* g_class=g_type->t_class;

	BUG_ON(g_class==NULL,"%s.t_class Filed Not Init",GrObject_Name(g));

	GrHashEntry* entry=GrHash_GetEntry(g_class->c_template,k);
	if(entry==NULL) return NULL;
	if(!GrHashEntry_Valid(entry))
	{
		GrErr_NameFormat("%s Has No Symbol '%s'",
				GrObject_Name(g),((GrString*)k)->s_value);
		return NULL;
	}
	assert(GrSymbol_Verify(entry->e_key));
	return entry->e_value;
}

int GrUtil_BaseTypeSetAttr(GrObject* g,GrObject* k,GrObject* v,long perm)
{
	assert(GrString_Verify(k));
	GrTypeInfo* g_type=GrObject_Type(g);

	GrClass* g_class=g_type->t_class;

	BUG_ON(g_class==NULL,"%s.t_class Filed Not Init",GrObject_Name(g));

	GrHashEntry* entry=GrHash_GetEntry(g_class->c_template,k);
	if(!GrHashEntry_Valid(entry))
	{
		GrErr_NameFormat("%s Has No Symbol '%s'",
				GrObject_Name(g),((GrString*)k)->s_value);
		return -1;
	}

	assert(GrSymbol_Verify(entry->e_key));
	GrErr_PermFormat("%s Symbol In '%s' Is Protected",
			((GrString*)k)->s_value,GrObject_Name(g));

	return -1;
}



int GrUtil_CheckSetAttr(GrSymbol* sy,long perm)
{
	//printf("perm=%lx\n",perm);
	long flags=sy->s_flags;
	if(perm)
	{
		return 1;
	}
	else
	{
		if(flags&GR_CLASS_PRIVATE)
		{
			return 0;
		}
		if(flags&GR_CLASS_PROTECTED)
		{
			return 0;
		}
		if(flags&GR_CLASS_PUBLIC)
		{
			return 1;
		}
	}
	return 1;
}
int GrUtil_CheckGetAttr(GrSymbol* sy,long perm)
{
	//printf("perm=%lx\n",perm);
	long flags=sy->s_flags;
	if(perm)
	{
		return 1;
	}
	else
	{
		if(flags&GR_CLASS_PRIVATE)
		{
			return 0;
		}
		if(flags&GR_CLASS_PROTECTED)
		{
			return 1;
		}
		if(flags&GR_CLASS_PUBLIC)
		{
			return 1;
		}
	}
	return 1;
}



ssize_t GrUtil_HashNotSupport(GrObject* x)
{
	GrErr_HashFormat("%s Not Support Hash");
	return -1;
}

























