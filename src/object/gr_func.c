#include"gr_func.h"
#include<memory/gc.h>
#include<engine/except.h>

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




static struct gr_type_ops func_type_ops=
{
};
struct gr_type_info Gr_Type_Func =
{
	.t_name="FuncObject",
	.t_size=sizeof(GrFunc),
	.t_ops=&func_type_ops,
};



