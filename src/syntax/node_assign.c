#include"node_assign.h"
#include"symbol_table.h"
#include<rtype/bt_string.h>

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

void assign_free(AstObject* ab)
{
	AstNodeAssign* node=AST_TO_ASSIGN(ab);
	ast_free((AstObject*)node->a_var);
	ast_free(node->a_expr);
	ast_destroy(ab);
	ry_free(node);
}
void assign_free_self(AstObject* ab)
{
	AstNodeAssign* node=AST_TO_ASSIGN(ab);
	ast_destroy(ab);
	ry_free(node);
}
#ifdef AST_MACHINE
static int assign_execute(AstObject* ab)
{
	AstNodeAssign* node=AST_TO_ASSIGN(ab);
	assert(node->a_var);
	BtString* var=node->a_var->i_value;
	Robject* key=S_TO_R(var);
	int exe_info=ast_execute(node->a_expr);
	if(exe_info<0)
	{
		return exe_info;
	}
	Robject* value=get_reg0();
	
	int ret=symbol_set_local(key,value);
	if(ret<0)
	{
		robject_release(value);
		return AST_EXE_EXCEPTION;
	}
	robject_release(value);
	return AST_EXE_SUCCESS;
}
#endif 

static AstNodeType node_assign=
{
	.n_type=ATN_ASSIGN,
	.n_name="Assign",
	.n_free=assign_free,
	.n_free_node=assign_free_self,
#ifdef AST_MACHINE
	.n_execute=assign_execute,
#endif 
};

AstNodeAssign* ast_create_assign(AstNodeVar* var,AstObject* expr)
{
	AstNodeAssign* ret=ast_node_new(AstNodeAssign,&node_assign);
	if(ret==NULL)
	{
		return ret;
	}
	ret->a_var=var;
	ret->a_expr=expr;
	return ret;
}

















