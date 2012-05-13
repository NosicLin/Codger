#include"gr_func.h"
#include<memory/gc.h>
#include<engine/except.h>
#include<engine/eg_thread.h>
#include<engine/eg_sframe.h>
#include"gr_opcode.h"
#include"gr_consts.h"

static inline void gf_init(GrFunc* f)
{
	f->f_livein=0;
	f->f_default_args=0;
	f->f_codes=0;
}
GrFunc* GrFunc_GcNew()
{
	GrFunc* func=GrGc_New(GrFunc,&Gr_Type_Func);
	if(func==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Func Object");
		return NULL;
	}
	gf_init(func);
	return func;
}


GrFunc* GrFunc_GcNewFlag(long flags)
{
	GrFunc* func=GrGc_Alloc(GrFunc,&Gr_Type_Func,flags);
	if(func==NULL)
	{
		GrErr_MemFormat("can't Alloc Memory For Func Object");
		return NULL;
	}
	gf_init(func);
	return func;
}


GrObject* GrFunc_Call(GrFunc* gf,GrObject* host,GrArray* args)
{
	assert(host);
	int args_nu=GrArray_Size(args);

	GrOpcode* op=gf->f_codes;

	EgSframe* ef=0;
	GrScope* scope=0;
	GrArray* many_args=0;

	int i;
	int ret;
	if(args_nu<op->o_args_min)
	{
		GrErr_ArgsFormat("FuncObject '%s' Need At Least %d Param,But Only %d Give",
				op->o_name->s_value,op->o_args_min,args_nu);
		return NULL;
	}
	if(args_nu>op->o_args_nu)
	{
		if(!(op->o_flags&GR_OPCODE_FLAG_MANY_ARG))
		{
			GrErr_ArgsFormat("FuncObject '%s' Need At Most %d Param,But %d Give",
					op->o_name->s_value,op->o_args_nu,args_nu);
			return NULL;
		}
	}
	if((op->o_flags&GR_OPCODE_FLAG_DEFAULT_ARG)&&args_nu<=op->o_args_nu)
	{
		for(i=args_nu;i<op->o_args_nu;i++)
		{
			GrObject* def_arg=GrArray_Get(gf->f_default_args,i-op->o_args_min);
			assert(def_arg);
			ret=GrArray_Push(args,def_arg);
			if(ret<0) return NULL;
		}
	}

	if(op->o_flags&GR_OPCODE_FLAG_MANY_ARG)
	{
		many_args=GrArray_GcNew();
		if(many_args==NULL) return NULL;

		for(i=op->o_args_nu;i<args_nu;i++)
		{
			GrObject* m_arg=GrArray_Get(args,i);
			assert(m_arg);
			ret=GrArray_Push(many_args,m_arg);
			if(ret<0) return NULL;
		}
	}

	ef=EgSframe_NewFromFunc(gf);
	if(ef==NULL) return NULL;

	scope=ef->f_scope;

	for(i=0;i<op->o_args_nu;i++)
	{
		GrObject* name=GrArray_Get(op->o_args_name,i);
		assert(name);
		GrObject* value=GrArray_Get(args,i);
		assert(value);

		ret=GrHash_Map(scope->s_table,name,value);
		if(ret<0) goto error;
	}
	if(op->o_flags&GR_OPCODE_FLAG_MANY_ARG)
	{
		GrObject* name=GrArray_Get(op->o_args_name,op->o_args_nu);
		assert(name);
		assert(many_args);
		ret=GrHash_Map(scope->s_table,name,(GrObject*)many_args);
		if(ret<0) goto error;
	}
	ret=GrHash_Map(scope->s_table,Gr_Const_String_this,host);
	if(ret<0) goto error;

	ef->f_host=host;
	EgThread* t=EgThread_GetSelf();
	EgThread_PushSframe(t,ef);

	return Gr_Object_Nil;
error:
	EgSframe_Free(ef);
	return NULL;
}

int GrFunc_GcUpdate(GrFunc* f)
{
	f->f_livein=GrGc_Update(f->f_livein);
	f->f_default_args=GrGc_Update(f->f_default_args);
	return 0;
}



static struct gr_type_ops func_type_ops=
{
	.t_call=(GrCallFunc)GrFunc_Call,
	.t_gc_update=(GrGcUpdateFunc)GrFunc_GcUpdate,
};
struct gr_type_info Gr_Type_Func =
{
	.t_name="FuncObject",
	.t_size=sizeof(GrFunc),
	.t_ops=&func_type_ops,
};



