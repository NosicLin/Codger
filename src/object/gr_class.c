#include"gr_class.h"
#include<memory/gc.h>
#include<engine/except.h>
#include"gr_hash.h"
#include"gr_symbol.h"
#include"gr_util.h"
#include"gr_instance.h"
#include"gr_array.h"
#include<memory/memory.h>
#include"gr_consts.h"
#include"gr_func.h"
#include<engine/eg_thread.h>

void GrClass_Destruct(GrClass* gc)
{
	if(gc->c_instance_type)
	{
		GrMem_Free(gc->c_instance_type);
		gc->c_instance_type=NULL;
	}
}


GrClass* GrClass_GcNew()
{
	return GrClass_GcNewFlag(GRGC_HEAP_YOUNG);
}

GrClass* GrClass_GcNewFlag(long flags)
{
	GrClass* c=GrGc_Alloc(GrClass,&Gr_Type_Class,flags);
	if(c==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For ClassObject");
		return NULL;
	}
	
	GrHash* s=GrHash_GcNew();
	if(s==NULL)
	{
		return NULL;
	}
	c->c_symbols=s;

	GrHash* t=GrHash_GcNew();
	if(t==NULL) return NULL;

	GrTypeInfo* i_type=GrMem_Alloc(sizeof(*i_type));
	if(i_type==NULL)
	{
		c->c_instance_type=NULL;
		return NULL;
	}

	i_type->t_class=c;
	i_type->t_name="InstanceObject";
	i_type->t_ops=&instance_type_ops;
	i_type->t_size=sizeof(GrInstance);

	c->c_instance_type=i_type;
	c->c_template=t;
	c->c_inhert=NULL;
	c->c_name=(GrString*)Gr_Const_String_unkown;

	GrGc_MarkRefLow(c);
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
	GrGc_Intercept(s->c_symbols,v);
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
	int ret;
	ret=GrHash_Map(s->c_symbols,k,v);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}


int GrClass_TemplateAdd(GrClass* s,GrObject* k,GrObject* v)
{
	assert(GrSymbol_Verify(k));
	int ret;
	ret=GrHash_Map(s->c_template,k,v);
	if(ret<0) return -1;
	return 0;
}

int GrClass_SetInherit(GrClass* c,GrObject* g)
{
	if(!GrClass_Verify(g))
	{
		GrErr_TypeFormat("Can't Inherit '%s'",GrObject_Name(g));
		return -1;
	}
	c->c_inhert=(GrClass*)g;
	GrGc_Intercept(c,g);
	return 0;
}

	

GrInstance* GrClass_Call(GrClass* s,GrObject* host,GrArray* args)
{

	size_t arg_nu=GrArray_Size(args);

	GrInstance* is=GrInstance_GcNew(s->c_instance_type);
	GrHashEntry* entry=GrHash_GetEntry(s->c_template,Gr_Const_String_init);

	/* class has no construct, so arg_nu will be 0*/
	if(!GrHashEntry_Valid(entry))
	{
		if(arg_nu!=0)
		{
			GrErr_ArgsFormat("%s Construct Take 0 Args,But %d Gived",
					s->c_name->s_value,arg_nu);
			return NULL;
		}

		return is;
	}

	assert(entry->e_value);

	GrObject* init=entry->e_value;

	if(!GrFunc_Verify(init))
	{
		return is;
	}

	if(GrFunc_CallWithRetVal((GrFunc*)init,
			(GrObject*)is,args,(GrObject*)is)==NULL)
	{
		return NULL;
	}
	return is;
}

int GrClass_GcUpdate(GrClass* c)
{
	if(c->c_inhert!=NULL)
	{
		c->c_inhert=GrGc_Update(c->c_inhert);
	}
	c->c_symbols=GrGc_Update(c->c_symbols);
	c->c_template=GrGc_Update(c->c_template);
	c->c_name=GrGc_Update(c->c_name);
	c->c_instance_type->t_class=GrGc_Update(c->c_instance_type->t_class);

	return 0;
}


static int class_set_attr(GrClass* s,GrObject* k,GrObject* v,long perm)
{
	assert(GrString_Verify(k));
	GrHashEntry* entry=GrHash_GetEntry(s->c_symbols,k);

	if(!GrHashEntry_Valid(entry))
	{
		GrErr_NameFormat("ClassObject '%s' Has No Symbol '%s'",
				s->c_name->s_value,((GrString*)k)->s_value);
		return -1;
	}

	assert(GrSymbol_Verify(entry->e_key));

	if(!GrUtil_CheckSetAttr((GrSymbol*)(entry->e_key),perm))
	{
		GrErr_PermFormat("'%s' Symbol In ClassObject '%s' Is %s",
					((GrString*)k)->s_value,s->c_name->s_value,
					GrSymbol_PermName((GrSymbol*)entry->e_key));

		return -1;
	}

	entry->e_value=v;
	GrGc_Intercept(s->c_symbols,v);
	return 0;
}

static GrObject* class_get_attr(GrClass* s,GrObject* k,long perm)
{
	assert(k);
	assert(GrString_Verify(k));
	GrHashEntry* entry=GrHash_GetEntry(s->c_symbols,k);

	if(!GrHashEntry_Valid(entry))
	{
		assert(GrString_Verify(k));
		GrErr_NameFormat("ClassObject '%s' Has No Symbol '%s'",
				s->c_name->s_value,((GrString*)k)->s_value);
		return NULL;
	}

	assert(GrSymbol_Verify(entry->e_key));

	if(!GrUtil_CheckGetAttr((GrSymbol*)(entry->e_key),perm))
	{
		GrErr_PermFormat("'%s' Symbol In ClassObject '%s' Is %s",
					((GrString*)k)->s_value,s->c_name->s_value,
					GrSymbol_PermName((GrSymbol*)entry->e_key));

		return NULL;
	}
	return entry->e_value;
}


static struct gr_type_ops class_type_ops=
{
	.t_call=(GrCallFunc)GrClass_Call,
	.t_get_attr=(GrGetAttrFunc)class_get_attr,
	.t_set_attr=(GrSetAttrFunc)class_set_attr,
	.t_gc_update=(GrGcUpdateFunc)GrClass_GcUpdate,
	.t_destruct=(GrDestructFunc)GrClass_Destruct,
};


GrTypeInfo Gr_Type_Class=
{
	.t_name="ClassObject",
	.t_size=sizeof(GrClass),
	.t_ops=&class_type_ops,
};

