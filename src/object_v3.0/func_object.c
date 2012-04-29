#include"func_object.h"
#include<rstd/gr_std.h>
#include<object/symbol_table.h>
#include<vm/stack_frame.h>
#include<vm/except.h>
#include<vm/engine.h>
#include"robject.h"

static TypeObject type_func;
FuncObject* func_new()
{
	FuncObject* func=robject_new(FuncObject,&type_func);
	if(func==NULL)
	{
		return NULL;
	}
	func->f_flags=0;
	func->f_args_min=0;
	func->f_args_nu=0;
	func->f_name=0;
	func->f_args_name=0;
	func->f_module=0;
	func->f_codes=0;
	func->f_defargs=0;
	return func;
}
void func_free(FuncObject* f)
{
	if(f->f_name) robject_release(S_TO_R(f->f_name));
	if(f->f_args_name) robject_release(A_TO_R(f->f_args_name));
	if(f->f_module) robject_release(M_TO_R(f->f_module));
	if(f->f_codes) op_code_free(f->f_codes);
	if(f->f_defargs) robject_release(A_TO_R(f->f_defargs));
	gr_free(f);
}
static void f_free(Robject* r)
{
	FuncObject*  f=R_TO_FUNC(r);
	func_free(f);
}
static struct object_ops func_object_ops=
{
	.ro_free=f_free,
};

static Robject*  func_call(Robject* r,BtArray* args)
{
	FuncObject* func=R_TO_FUNC(r);
	ssize_t args_nu=btarray_size(args);

	SymbolTable* sy=0;
	BtArray* many_args=0;
	StackFrame* sf=0;

	int i;
	int ret=0;
	if(args_nu<func->f_args_min)
	{
		except_args_err_format("FuncObject.%s need at least %d param,but %d give",
							func->f_name->s_value,func->f_args_min,
							args_nu);
		return NULL;
	}
	if((args_nu>func->f_args_nu ))
	{
		if(!(func->f_flags&FUNC_FLAGS_MANY_ARGS))
		{
			except_args_err_format("FuncObject.%s need at most %d param,but %d give",
							func->f_name->s_value,func->f_args_nu,args_nu);
			return NULL;
		}
	}

	if((func->f_flags&FUNC_FLAGS_DEFALUT_ARGS)&&args_nu<=func->f_args_nu)
	{
		for(i=args_nu;i<func->f_args_nu;i++)
		{
			Robject* def_arg=btarray_get_item(func->f_defargs,i-func->f_args_min);
			assert(def_arg);
			int ret=btarray_push_back(args,def_arg);
			robject_release(def_arg);
			if(ret<0)
			{
				goto error;
			}
		}
	}
	if(func->f_flags&FUNC_FLAGS_MANY_ARGS)
	{
		many_args=btarray_create();
		if(many_args==NULL)
		{
			goto error;
		}
		for(i=func->f_args_nu;i<args_nu;i++)
		{
			Robject* g=btarray_get_item(args,i);
			ret=btarray_push_back(many_args,g);
			robject_release(g);
			if(ret<0)
			{
				goto error;
			}
		}
	}
	sf=sframe_from_func(func);
	if(sf==NULL) goto error;
	sy=sframe_get_sytable(sf);

	for(i=0;i<func->f_args_nu;i++)
	{
		Robject* g_name=btarray_get_item(func->f_args_name,i);
		assert(g_name);
		Robject* value=btarray_get_item(args,i);
		assert(value);

		ret=sy_table_map(sy,g_name,value);
		robject_release(g_name);
		robject_release(value);
		if(ret<0)
		{
			goto error;
		}
	}
	if(func->f_flags&FUNC_FLAGS_MANY_ARGS)
	{
		Robject* g_name=btarray_get_item(func->f_args_name,func->f_args_nu);
		assert(g_name);
		assert(many_args);
		ret=sy_table_map(sy,g_name,A_TO_R(many_args));
		robject_release(g_name);
		if(ret<0) goto error;
	}

	if(func->f_flags&FUNC_FLAGS_MANY_ARGS)
	{
		robject_release(A_TO_R(many_args));

	}
	robject_release(SY_TO_R(sy));
	ret=engine_push(sf);
	if(ret<0) goto error;
	return ObjectDummy;
error:
	if(sf) sframe_free(sf);
	robject_release(A_TO_R(many_args));
	robject_release(SY_TO_R(sy));
	return NULL;
}
static struct expr_ops func_ops=
{
	.ro_call=func_call,
};


static TypeObject type_func=
{
	.t_name="FuncObject",
	.t_type=TYPE_FUNC,
	.t_object_funcs=&func_object_ops,
	.t_expr_funcs=&func_ops,
};
