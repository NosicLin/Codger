#include"module_object.h"
#include<vm/op_code.h>
#include<rtype/bt_array.h>
#include<rtype/bt_string.h>
#include<rstd/gr_std.h>
#include<rtype/bt_bool.h>
#include"null_object.h"
#include"symbol_table.h"
#include"func_object.h"

static void md_free(Robject* r)
{
	return module_free(R_TO_M(r));
}

void module_free(ModuleObject* md)
{
	if(md->m_belong) robject_release(M_TO_R(md->m_belong));
	if(md->m_consts) robject_release(A_TO_R(md->m_consts));
	if(md->m_symbols) robject_release(A_TO_R(md->m_symbols));
	if(md->m_name) robject_release(S_TO_R(md->m_name));
	if(md->m_codes) op_code_free(md->m_codes);
	if(md->m_attrs) robject_release(SY_TO_R(md->m_attrs));
	if(md->m_funcs) robject_release(A_TO_R(md->m_funcs));

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
	BtArray* funcs=btarray_create();
	SymbolTable* attrs=sy_table_new();


	if(consts==NULL||symbols==NULL||attrs==NULL||funcs==NULL)
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
	md->m_attrs=attrs;
	md->m_funcs=funcs;
	return md;
error:
	if(consts) robject_release(A_TO_R(consts));
	if(symbols) robject_release(A_TO_R(symbols));
	if(attrs) robject_release(SY_TO_R(attrs));
	if(funcs) robject_release(A_TO_R(funcs));

	return NULL;
}

int32_t module_map_const(ModuleObject* m,Robject* value)
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
int32_t module_map_symbol(ModuleObject* m,Robject* symbol)
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

int module_add_func(ModuleObject* m,FuncObject* f)
{
	int ret=btarray_push_back(m->m_funcs,FUNC_TO_R(f));
	return ret;
}

void module_write(ModuleObject* m,FILE* f)
{
	fprintf(f,"@ModuleName %s\n",m->m_name->s_value);
	fprintf(f,"@ConstNum %d \n{\n",btarray_size(m->m_consts));
	int i;
	int size=btarray_size(m->m_consts);
	int type;
	Robject* cur;
	FuncObject* func;

	for(i=0;i<size;i++)
	{
		cur=btarray_get_item(m->m_consts,i);
		type=robject_typeid(cur);
		if(type==TYPE_FUNC)
		{
			fprintf(f,"FuncObject(%s)",R_TO_FUNC(cur)->f_name->s_value);
		}
		else
		{
			robject_print(cur,f,0);
		}
		fprintf(f," ");
		robject_release(cur);
	}

	fprintf(f,"\n}\n");
	size=btarray_size(m->m_symbols);
	fprintf(f,"@SymbolsNum %d \n{\n",size);

	for(i=0;i<size;i++)
	{
		cur=btarray_get_item(m->m_symbols,i);
		robject_print(cur,f,0);
		robject_release(cur);
		fprintf(f," ");
	}
	fprintf(f,"\n}\n");

	size=btarray_size(m->m_funcs);

	for(i=0;i<size;i++)
	{
		cur=btarray_get_item(m->m_funcs,i);
		func=R_TO_FUNC(cur);
		fprintf(f,"@FuncObject(%s) \n{\n",func->f_name->s_value);
		fprintf(f,"\tArgNu:%d\n",func->f_args_nu);
		fprintf(f,"\tArgMin:%d\n",func->f_args_min);
		
		fprintf(f,"\tFlags:");
		if(func->f_flags&FUNC_FLAGS_DEFALUT_ARGS) 
		{
			fprintf(f," DEFAULT_ARGS");
		}
		if(func->f_flags&FUNC_FLAGS_MANY_ARGS)
		{
			fprintf(f," MANY_ARGS");
		}
		if(func->f_flags==0)
		{
			fprintf(f,"NORMAL_FUNC");
		}

		fprintf(f,"\n");
		fprintf(f,"\tArgName: ");

		int j;
		for(j=0;j<btarray_size(func->f_args_name);j++)
		{
			Robject* arg_name=btarray_get_item(func->f_args_name,j);
			fprintf(f," %s",R_TO_S(arg_name)->s_value);
			robject_release(arg_name);
		}
		fprintf(f,"\n");

		fprintf(f,"\tOpCode: \n\t{\n");
		op_code_print(func->f_codes,f,2);
		robject_release(cur);
		fprintf(f,"\t}\n");
		fprintf(f,"}\n");
	}

	fprintf(f,"@OpCode Module(%s) \n{\n",m->m_name->s_value);
	op_code_print(m->m_codes,f,1);
	fprintf(f,"}\n");
}

















