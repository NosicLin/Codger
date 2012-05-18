#include"gr_instance.h"
#include<memory/gc.h>
#include"gr_string.h"
#include"gr_symbol.h"
#include"gr_class.h"
#include<engine/except.h>
#include"gr_util.h"

GrInstance* GrInstance_GcNew(GrTypeInfo* t)
{
	GrInstance* i=GrGc_New(GrInstance,t);
	if(i==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For InstanceObject");
		return NULL;
	}
	GrHash* s=GrHash_GcNew();
	if(s==NULL) return NULL;

	i->i_symbols=s;

	return i;
}


GrInstance* GrInstance_GcNewFlag(GrTypeInfo* t,long f)
{
	GrInstance* i=GrGc_Alloc(GrInstance,t,f);
	if(t==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For InstanceObject");
		return NULL;
	}
	GrHash* s=GrHash_GcNew();
	if(s==NULL) return NULL;

	i->i_symbols=s;

	GrGc_Intercept(i,s);
	return i;
}

GrObject* GrInstance_GetAttr(GrInstance* ic,GrObject* k)
{
	GrHashEntry* entry;
	entry=GrHash_GetEntry(ic->i_symbols,k);
	if(entry==NULL) return NULL;
	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		return entry->e_value;
	}

	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	entry=GrHash_GetEntry(cl->c_template,k);
	if(entry==NULL) return NULL;
	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		return entry->e_value;
	}

	if(GrString_Verify(k))
	{
		GrErr_NameFormat("%s Instance Has No Symbol '%s'",
				cl->c_name->s_value,GR_TO_S(k)->s_value);
		return NULL;
	}
	else
	{
		GrErr_NameFormat("%s Instance Has No Such Symbol",
				cl->c_name->s_value);
		return NULL;
	}
}
int GrInstance_SetAttr(GrInstance* ic,GrObject* k,GrObject* v)
{
	GrHashEntry* entry;
	entry=GrHash_GetEntry(ic->i_symbols,k);
	if(entry==NULL) return -1;
	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		entry->e_value=v;
		GrGc_Intercept(ic->i_symbols,v);
		return 0;
	}

	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	entry=GrHash_GetEntry(cl->c_template,k);
	if(entry==NULL) return -1;

	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		GrHash_Map(ic->i_symbols,entry->e_key,v);
		GrGc_Intercept(ic->i_symbols,v);
		return 0;
	}

	if(GrString_Verify(k))
	{
		GrErr_NameFormat("%s Instance Has No Symbol '%s'",
				cl->c_name->s_value,GR_TO_S(k)->s_value);
		return -1;
	}
	else
	{
		GrErr_NameFormat("%s Instance Has No Such Symbol",
				cl->c_name->s_value);
		return -1;
	}
}

int GrInstance_GcUpdate(GrInstance* ic)
{
	ic->i_symbols=GrGc_Update(ic->i_symbols);
	return 0;
}


static int gi_set_attr(GrInstance* ic,GrObject* k,GrObject* v,long perm)
{
	assert(GrString_Verify(k));
	GrHashEntry* entry;
	entry=GrHash_GetEntry(ic->i_symbols,k);
	if(entry==NULL) return -1;

	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(!GrUtil_CheckSetAttr((GrSymbol*)(entry->e_key),perm))
		{
			GrErr_PermFormat("'%s' Symbol In %s.Instance Is %s",
					((GrString*)k)->s_value,cl->c_name->s_value,
					GrSymbol_PermName((GrSymbol*)entry->e_key));
			return -1;
		}
		entry->e_value=v;
		GrGc_Intercept(ic->i_symbols,v);
		return 0;
	}


	assert(cl->c_template);
//	fprintf(stderr,"cl->c_template=%lx \n",(long)cl->c_template);
	entry=GrHash_GetEntry(cl->c_template,k);
	if(entry==NULL) return -1;

	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(!GrUtil_CheckSetAttr((GrSymbol*)(entry->e_key),perm))
		{
			GrErr_PermFormat("'%s' Symbol In %s.Instance Is %s",
					((GrString*)k)->s_value,cl->c_name->s_value,
					GrSymbol_PermName((GrSymbol*)entry->e_key));

			return -1;
		}
		GrHash_Map(ic->i_symbols,entry->e_key,v);
		GrGc_Intercept(ic->i_symbols,v);
		return 0;
	}

	GrErr_NameFormat("%s Instance Has No Symbol '%s'",
			cl->c_name->s_value,GR_TO_S(k)->s_value);
	return -1;
}


static GrObject* gi_get_attr(GrInstance* ic, GrObject* k,long perm)
{
	assert(GrString_Verify(k));
	GrHashEntry* entry;

	/* first find from instance symbols */
	entry=GrHash_GetEntry(ic->i_symbols,k);

	if(entry==NULL) return NULL;


	/* get instance class */
	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(!GrUtil_CheckGetAttr((GrSymbol*)(entry->e_key),perm))
		{
			GrErr_PermFormat("'%s' Symbol In %s.Instance Is %s",
					((GrString*)k)->s_value,cl->c_name->s_value,
					GrSymbol_PermName((GrSymbol*)entry->e_key));
			return NULL;
		}
		return entry->e_value;
	}


	/* if symbol not in instance symbol,
	 * then find it from class template */ 
	entry=GrHash_GetEntry(cl->c_template,k);
	if(entry==NULL) return NULL;

	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(!GrUtil_CheckGetAttr((GrSymbol*)(entry->e_key),perm)<0)
		{
			GrErr_PermFormat("'%s' Symbol In %s.Instance Is %s",
					((GrString*)k)->s_value,cl->c_name->s_value,
					GrSymbol_PermName((GrSymbol*)entry->e_key));
			return NULL;
		}
		return entry->e_value;
	}

	GrErr_NameFormat("%s Instance Has No Symbol '%s'",
			cl->c_name->s_value,GR_TO_S(k)->s_value);
	return NULL;
}

int GrInstance_Print(GrInstance* ic,FILE* f)
{
	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	fprintf(f,"%s Instance At %lx",cl->c_name->s_value,(long)ic);
	return 0;
}

struct gr_type_ops instance_type_ops=
{
	.t_get_attr=(GrGetAttrFunc)gi_get_attr,
	.t_set_attr=(GrSetAttrFunc)gi_set_attr,
	.t_print=(GrPrintFunc)GrInstance_Print,
	.t_gc_update=(GrGcUpdateFunc)GrInstance_GcUpdate,
};
















