#include"node_while.h"
#include<assert.h>
#include<rstd/redy_std.h>
#include<vm/except.h>
#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

static void  while_free(AstObject* ab)
{
	AstNodeWhile* node=AST_TO_WHILE(ab);
	ast_free(node->w_expr);
	ast_free(node->w_stmts);
	ast_destroy(ab);
	ry_free(ab);
}
static void while_free_self(AstObject* ab)
{
	AstNodeWhile* node=AST_TO_WHILE(ab);
	ast_destroy(ab);
	ry_free(node);
}

#ifdef AST_MACHINE
static int while_execute(AstObject* ab)
{
	Robject* expr_value=0;
	AstNodeWhile* node=AST_TO_WHILE(ab);
	AstObject* expr=node->w_expr;
	AstObject* stmts=node->w_stmts;
	assert(expr);
	assert(stmts);
	int ret=AST_EXE_SUCCESS;

	int bool_flags=1;
	while(1)
	{
		int exe_info=ast_execute(expr);
		if(exe_info<0)
		{
			ret=exe_info;
			break;
		}
		expr_value=get_reg0();

		bool_flags=robject_bool(expr_value);
		robject_release(expr_value);
		expr_value=0;
		if(vm_except_happened())
		{
			assert(bool_flags<0);
			ret=AST_EXE_EXCEPTION;
			break;
		}
		assert(bool_flags>=0);
		if(!bool_flags)
		{
			break;
		}
		exe_info=ast_execute(stmts);
		if(exe_info<0)
		{
			ret=exe_info;
			break;
		}
		if(exe_info==AST_EXE_BREAK)
		{
			ret=AST_EXE_SUCCESS;
			break;
		}
		if(exe_info==AST_EXE_CONTINUE)
		{
			continue;
		}
		if(exe_info==AST_EXE_RETURN)
		{
			ret=AST_EXE_RETURN;
			break;
		}
	}
	return ret;
}
#endif 

static  AstNodeType node_while=
{
	.n_name="While",
	.n_type=ATN_WHILE,
	.n_free=while_free,
	.n_free_node=while_free_self,
#ifdef AST_MACHINE
	.n_execute=while_execute,
#endif 
};

AstNodeWhile* ast_create_while(AstObject* expr,AstObject* stmts)
{
	AstNodeWhile* node=ast_node_new(AstNodeWhile,&node_while);
	if(node==NULL)
	{
		return NULL;
	}
	node->w_expr=expr;
	node->w_stmts=stmts;
	return node;
}








