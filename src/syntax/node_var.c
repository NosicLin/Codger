#include"node_var.h"
#include<vm/except.h>
#include<object/robject.h>
#ifdef AST_MACHINE
#include"ast_machine.h"
#include"symbol_table.h"
#endif 

static void var_destruct(AstObject* ab)
{
	AstNodeVar* node=AST_TO_VAR(ab);
	robject_release(node->v_value);
}

#ifdef AST_MACHINE
static int var_execute(AstObject* ab)
{
	AstNodeVar* node=AST_TO_VAR(ab);
	assert(node->v_value);
	Robject* key=node->v_value;

	Robject* value=symbol_get_local(key);
	if(value==NULL)
	{
		except_name_err_format("name %s is not define",R_TO_S(node->v_value)->s_value);
		return AST_EXE_EXCEPTION;
	}
	set_reg0(value);
	robject_release(value);
	return AST_EXE_SUCCESS;
}
static int var_set_value(AstObject* ab,Robject* value)
{
	AstNodeVar* node=AST_TO_VAR(ab);
	Robject* key=node->v_value;
	int ret=symbol_set_local(key,value);
	if(ret<0)
	{
		return AST_EXE_EXCEPTION;
	}
	return AST_EXE_SUCCESS;
}
#endif 

static AstNodeType node_var=
{
	.n_type=ATN_VAR,
	.n_name="Var",
	.n_belong=ANF_LITERAL,
	.n_destruct=var_destruct,
#ifdef AST_MACHINE
	.n_execute=var_execute,
	.n_set_value=var_set_value,
#endif 
};

AstNodeVar* ast_create_var(Robject* value)
{
	AstNodeVar* ret=ast_node_new(AstNodeVar,&node_var);
	if(ret==NULL)
	{
		return NULL;
	}
	robject_addref(value);
	ret->v_value=value;
	return ret;
}

	

