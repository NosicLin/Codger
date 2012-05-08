#include"gr_class.h"
#include<memory/gc.h>
#include<engine/except.h>
#include"gr_hash.h"
#include"gr_symbol.h"
#include"gr_util.h"
#include"gr_instance.h"
#include<memory/memory.h>


GrClass* GrClass_GcNew()
{
	GrClass* c=GrGc_New(GrClass,&Gr_Type_Class);
	if(c==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For ClassObject");
		return NULL;
	}
	
	GrHash* h=GrHash_GcNew();
	if(h==NULL)
	{
		return NULL;
	}
	c->c_symbols=h;

	GrHash* t=GrHash_GcNew();
	if(t==NULL) return NULL;

	GrTypeInfo* i_type=GrMem_Alloc(sizeof(*i_type));
	if(i_type==NULL) return NULL;

	i_type->t_class=c;
	i_type->t_name="InstanceObject";
	i_type->t_ops=&instance_type_ops;
	i_type->t_size=sizeof(GrInstance);

	c->c_instance_type=i_type;
	c->c_template=t;
	c->c_inhert=NULL;
	return c;
}


GrClass* GrClass_GcNewFlag(long flags)
{
	GrClass* c=GrGc_Alloc(GrClass,&Gr_Type_Class,flags);
	if(c==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For ClassObject");
		return NULL;
	}
	
	GrHash* h=GrHash_GcNewFlag(flags);
	if(h==NULL)
	{
		return NULL;
	}
	c->c_symbols=NULL;

	GrHash* t=GrHash_GcNewFlag(flags);
	if(t==NULL) return NULL;

	c->c_template=t;
	c->c_inhert=NULL;
	return c;
}

int GrClass_SetAttr(GrClass* s,GrObject* k,GrObject* v)
{
	GrHashEntry* entry= GrHash_GetEntry(s->c_symbols,k);
	if(!GrHashEntry_Valid(entry))
	{
		if(GrString_Verify(k))
		{
			GrErr_NameFormat("ClassObject Has No Symbol '%s'",
					((GrString*)k)->s_value);
			return -1;
		}
		else
		{
			GrErr_NameFormat("ClassObject Has No Such Symbol");
			return -1;
		}

	}
	assert(GrSymbol_Verify(entry->e_key));
	entry->e_value=v;
	return 0;
}

GrObject* GrClass_GetAttr(GrClass* s,GrObject* k)
{
	GrHashEntry* entry= GrHash_GetEntry(s->c_symbols,k);
	if(!GrHashEntry_Valid(entry))
	{
		if(GrString_Verify(k))
		{
			GrErr_NameFormat("ClassObject Has No Symbol '%s'",
					((GrString*)k)->s_value);
			return NULL;
		}
		else
		{
			GrErr_NameFormat("ClassObject Has No Such Symbol");
			return NULL;
		}

	}
	assert(GrSymbol_Verify(entry->e_key));
	return entry->e_value;
}


int  GrClass_AddAttr(GrClass* s,GrObject* k,GrObject* v)
{
	assert(GrSymbol_Verify(k));
	return GrHash_Map(s->c_symbols,k,v);
}


int GrClass_TemplateAdd(GrClass* s,GrObject* k,GrObject* v)
{
	assert(GrSymbol_Verify(k));
	return GrHash_Map(s->c_template,k,v);
}

int GrClass_SetInherit(GrClass* c,GrObject* g)
{
	if(!GrClass_Verify(g))
	{
		GrErr_TypeFormat("Can't Inherit '%s'",GrObject_Name(g));
		return -1;
	}
	c->c_inhert=(GrClass*)g;
	return 0;
}

	

GrInstance* GrClass_CreateInstance(GrClass* s)
{

	GrInstance* is=GrInstance_GcNew(s->c_instance_type);
	return is;
}

GrInstance* GrClass_CreateInstanceFlag(GrClass* s,long f)
{
	GrInstance* is=GrInstance_GcNewFlag(s->c_instance_type,f);
	return is;
}

static int class_set_attr(GrClass* s,GrObject* k,GrObject* v,long perm)
{
	GrHashEntry* entry=GrHash_GetEntry(s->c_symbols,k);

	if(!GrHashEntry_Valid(entry))
	{
		if(GrString_Verify(k))
		{
			GrErr_NameFormat("ClassObject Has No Symbol '%s'",
					((GrString*)k)->s_value);
			return -1;
		}
		else
		{
			GrErr_NameFormat("ClassObject Has No Such Symbol");
			return -1;
		}
	}

	assert(GrSymbol_Verify(entry->e_key));

	if(!GrUtil_CheckSetAttr((GrSymbol*)(entry->e_key),perm))
	{
		return -1;
	}

	entry->e_value=v;
	return 0;
}

static GrObject* class_get_attr(GrClass* s,GrObject* k,long perm)
{
	assert(k);
	GrHashEntry* entry=GrHash_GetEntry(s->c_symbols,k);

	if(!GrHashEntry_Valid(entry))
	{
		if(GrString_Verify(k))
		{
			GrErr_NameFormat("ClassObject Has No Symbol '%s'",
					((GrString*)k)->s_value);
			return NULL;
		}
		else
		{
			GrErr_NameFormat("ClassObject Has No Such Symbol");
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


static struct gr_type_ops class_type_ops=
{
	.t_new=(GrNewFunc)GrClass_CreateInstance,
	.t_get_attr=(GrGetAttrFunc)class_get_attr,
	.t_set_attr=(GrSetAttrFunc)class_set_attr,
};
	

GrTypeInfo Gr_Type_Class=
{
	.t_name="ClassObject",
	.t_size=sizeof(GrClass),
	.t_ops=&class_type_ops,
};

