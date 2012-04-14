#include"func_object.h"
#include<rstd/gr_std.h>

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
	return func;
}
void func_free(FuncObject* f)
{
	if(f->f_name) robject_release(S_TO_R(f->f_name));
	if(f->f_args_name) robject_release(A_TO_R(f->f_args_name));
	if(f->f_module) robject_release(M_TO_R(f->f_module));
	if(f->f_codes) op_code_free(f->f_codes);
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

static TypeObject type_func=
{
	.t_name="FuncObject",
	.t_type=TYPE_FUNC,
	.t_object_funcs=&func_object_ops,
};
