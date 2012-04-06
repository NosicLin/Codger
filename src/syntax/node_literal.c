#include "node_literal.h"
#include<rstd/redy_std.h>
#ifdef AST_MACHINE 
#include "ast_machine.h"
#endif /* AST_MACHINE */
#include"ast_object.h"

static void literal_destruct(AstObject* ab)
{
	AstNodeLiteral* node=AST_TO_LITERAL(ab);
	robject_release(node->l_value);
}
#ifdef AST_MACHINE 
static int literal_execute(AstObject* ab)
{
	AstNodeLiteral* node=AST_TO_LITERAL(ab);
	Robject* value=node->l_value;
	set_reg0(value);
	return AST_EXE_SUCCESS;
}
#endif /*AST_MACHINE*/

	


static AstNodeType node_literal=
{
	.n_type=ATN_LITERAL,
	.n_name="Literal",
	.n_belong=ANF_LITERAL,
	.n_destruct=literal_destruct,
#ifdef AST_MACHINE 
	.n_execute=literal_execute,
#endif /*AST_MACHINE*/
};

AstNodeLiteral* ast_create_literal(Robject* r)
{
	AstNodeLiteral* node=ast_node_new(AstNodeLiteral,&node_literal);
	if(node==NULL)
	{
		return NULL;
	}
	robject_addref(r);
	node->l_value=r;
	return node;
}









