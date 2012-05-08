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
	GrHash* s=GrHash_GcNewFlag(f);
	if(s==NULL) return NULL;

	i->i_symbols=s;

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


static int gi_set_attr(GrInstance* ic,GrObject* k,GrObject* v,long perm)
{
	GrHashEntry* entry;
	entry=GrHash_GetEntry(ic->i_symbols,k);
	if(entry==NULL) return -1;
	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(GrUtil_CheckSetAttr((GrSymbol*)(entry->e_key),perm)<0)
		{
			GrErr_NameFormat("Access Has No Perm");
			return -1;
		}
		entry->e_value=v;
		return 0;
	}

	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	entry=GrHash_GetEntry(cl->c_template,k);
	if(entry==NULL) return -1;

	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(GrUtil_CheckSetAttr((GrSymbol*)(entry->e_key),perm)<0)
		{
			GrErr_NameFormat("Access Has No Perm");
			return -1;
		}
		GrHash_Map(ic->i_symbols,entry->e_key,v);
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


static GrObject* gi_get_attr(GrInstance* ic, GrObject* k,long perm)
{
	GrHashEntry* entry;

	entry=GrHash_GetEntry(ic->i_symbols,k);

	if(entry==NULL) return NULL;
	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(GrUtil_CheckGetAttr((GrSymbol*)(entry->e_key),perm)<0)
		{
			GrErr_NameFormat("Access Has No Perm");
			return NULL;
		}
		return entry->e_value;
	}

	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;
	assert(cl);

	entry=GrHash_GetEntry(cl->c_template,k);
	if(entry==NULL) return NULL;
	if(GrHashEntry_Valid(entry))
	{
		assert(GrSymbol_Verify(entry->e_key));
		if(GrUtil_CheckGetAttr((GrSymbol*)(entry->e_key),perm)<0)
		{
			GrErr_NameFormat("Access Has No Perm");
			return NULL;
		}
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

int GrInstance_Print(GrInstance* ic,FILE* f)
{
	GrClass* cl=GrObject_Type((GrObject*)ic)->t_class;

	fprintf(f,"%s Instance At %lx",cl->c_name->s_value,(long)ic);
	return 0;
}

struct gr_type_ops instance_type_ops=
{
	.t_get_attr=(GrGetAttrFunc)gi_get_attr,
	.t_set_attr=(GrSetAttrFunc)gi_set_attr,
	.t_print=(GrPrintFunc)GrInstance_Print,
};
















