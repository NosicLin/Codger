#include"node_var.h"
#include<rstd/redy_std.h>
#include<vm/except.h>
#ifdef AST_MACHINE
#include"ast_machine.h"
#include"symbol_table.h"
#endif 

static void var_free(AstObject* ab)
{
	AstNodeVar* node=AST_TO_VAR(ab);
	robject_release(S_TO_R(node->i_value));
	ry_free(node);
}

#ifdef AST_MACHINE
static int var_execute(AstObject* ab)
{
	AstNodeVar* node=AST_TO_VAR(ab);
	assert(node->i_value);
	Robject* key=S_TO_R(node->i_value);
	Robject* value=symbol_get_local(key);
	if(value==NULL)
	{
		except_name_err_format("name %s is not define",node->i_value->s_value);
		return AST_EXE_EXCEPTION;
	}
	set_reg0(value);
	robject_release(value);
	return AST_EXE_SUCCESS;
}
#endif 

static AstNodeType node_var=
{
	.n_type=ATN_VAR,
	.n_name="Var",
	.n_free=var_free,
	.n_free_node=var_free,
#ifdef AST_MACHINE
	.n_execute=var_execute,
#endif 
};

AstNodeVar* ast_create_var(BtString* value)
{
	AstNodeVar* ret=ast_node_new(AstNodeVar,&node_var);
	if(ret==NULL)
	{
		return NULL;
	}
	robject_addref(S_TO_R(value));
	ret->i_value=value;
	return ret;
}

	

