#include"node_print.h"
#include"node_type.h"
#include"object/robject.h"
#include<rstd/redy_std.h>

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

static void print_free(AstObject* ab)
{
	AstNodePrint* node=AST_TO_PRINT(ab);
	ast_free(node->p_expr);
	ast_destroy(ab);
	ry_free(node);
}
static void print_free_self(AstObject* ab)
{
	AstNodePrint* node=AST_TO_PRINT(ab); /* type check*/

	ast_destroy(ab);
	ry_free(node);
}
#ifdef AST_MACHINE
static int print_execute(AstObject* ab)
{
	AstNodePrint* node=AST_TO_PRINT(ab);
	struct list_head* head=&node->p_expr->a_chirldren;
	AstObject* p;
	list_for_each_entry(p,head,a_sibling)
	{

		int exe_info=ast_execute(p);
		if(exe_info<0)
		{
			return exe_info;
		}

		Robject* value=get_reg0();
		robject_print(value,NULL,0);
		printf(" ");
		robject_release(value);
	}
	printf("\n");

	return AST_EXE_SUCCESS;
}
#endif 

static AstNodeType node_print=
{
	.n_type=ATN_PRINT,
	.n_name="Print",
	.n_free=print_free,
	.n_free_node=print_free_self,
#ifdef AST_MACHINE
	.n_execute=print_execute,
#endif 
};

AstNodePrint* ast_create_print(AstObject* expr)
{
	AstNodePrint* node=ast_node_new(AstNodePrint,&node_print);
	if(node==NULL)
	{
		return NULL;
	}
	node->p_expr=expr;
	return node;
}



