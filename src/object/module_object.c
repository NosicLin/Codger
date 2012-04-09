#include"module_object.h"
#include<vm/op_code.h>
#include<rtype/bt_array.h>
#include<rtype/bt_string.h>
#include<rstd/gr_std.h>
#include<rtype/bt_bool.h>
#include"null_object.h"



void md_free(Robject* r)
{
	ModuleObject* md=R_TO_M(r);
	if(md->m_belong) robject_release(M_TO_R(md->m_belong));
	if(md->m_consts) robject_release(A_TO_R(md->m_consts));
	if(md->m_symbols) robject_release(A_TO_R(md->m_symbols));
	if(md->m_name) robject_release(S_TO_R(md->m_name));
	if(md->m_codes) op_code_free(md->m_codes);


	gr_free(md);
}
struct object_ops module_object_ops=
{
	.ro_free=md_free,
};

static TypeObject type_module=
{
	.t_name="Module",
	.t_type=TYPE_MODULE,
	.t_object_funcs=&module_object_ops,
};
struct module_object* module_new()
{

	BtArray* consts=btarray_create();
	BtArray* symbols=btarray_create();

	if(consts==NULL||symbols==NULL)
	{
		goto error;
	}

	btarray_push_back(consts,B_TO_R(ObjectFalse));
	btarray_push_back(consts,B_TO_R(ObjectTrue));
	btarray_push_back(consts,ObjectNull);

	ModuleObject* md=robject_new(ModuleObject,&type_module);
	if(md==NULL)
	{
		goto error;
	}
	md->m_consts=consts;
	md->m_symbols=symbols;
	md->m_belong=0;
	md->m_codes=0;
	md->m_name=0;
	return md;
error:
	if(consts) robject_release(A_TO_R(consts));
	if(symbols) robject_release(A_TO_R(symbols));

	return NULL;
}

unsigned long module_map_const(ModuleObject* m,Robject* value)
{

	assert(value);
	if(value==ObjectNull)
	{
		return 2;
	}
	if(value==B_TO_R(ObjectTrue))
	{
		return 1;
	}
	if(value==B_TO_R(ObjectFalse))
	{
		return 0;
	}
	int ret;

	ret=btarray_push_back(m->m_consts,value);
	if(ret<0)
	{
		return -1;
	}
	return btarray_size(m->m_consts)-1;
}
unsigned long module_map_symbol(ModuleObject* m,Robject* symbol)
{
	assert(symbol);
	int ret;
	ret=btarray_push_back(m->m_symbols,symbol);
	if(ret<0)
	{
		return -1;
	}
	return btarray_size(m->m_symbols)-1;
}




