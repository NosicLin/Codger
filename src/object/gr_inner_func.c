#include"gr_inner_func.h"
#include<memory/gc.h>
#include<engine/except.h>

GrInnerFunc* GrInnerFunc_GcNew(GrCFunc c_f,long arg_nu)
{
	GrInnerFunc* i_func=GrGc_New(GrInnerFunc,&Gr_Type_Inner_Func);
	if(i_func==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For InnerFuncObject");
		return NULL;
	}
	i_func->i_as_exe=0;
	i_func->i_args_nu=arg_nu;
	i_func->i_func=c_f;
	return i_func;
}
GrInnerFunc* GrInnerFunc_GcNewFlag(GrCFunc c_f,long arg_nu,long flags)
{
	GrInnerFunc* i_func=GrGc_Alloc(GrInnerFunc,&Gr_Type_Inner_Func,flags);
	if(i_func==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For InnerFuncObject");
		return NULL;
	}
	i_func->i_as_exe=0;
	i_func->i_args_nu=arg_nu;
	i_func->i_func=c_f;
	return i_func;
}

GrObject* GrInnerFunc_Call(GrInnerFunc* f,GrObject* host,GrArray* arg)
{
	size_t arg_nu=GrArray_Size(arg);
	if(f->i_args_nu<0)
	{
		return f->i_func(host,arg);
	}

	if(f->i_args_nu!=arg_nu)
	{
		GrErr_ArgsFormat("InnerFuncObject Take %d Args,But %d Give",
				f->i_args_nu,arg_nu);
		return NULL;
	}

	return f->i_func(host,arg);
}



static struct gr_type_ops inner_func_type_ops=
{
	.t_call=(GrCallFunc)GrInnerFunc_Call,
};

GrTypeInfo Gr_Type_Inner_Func=
{
	.t_name="InnerFuncObject",
	.t_size=sizeof(GrInnerFunc),
	.t_ops=&inner_func_type_ops,
};

