#include "ast_node_literal.h"
#include<stdlib.h>

#ifdef AST_MACHINE 
#include "ast_machine.h"
#endif /* AST_MACHINE */

static void literal_free(AstObject* ab)
{
	AstNodeLiteral* node=AST_TO_LITERAL(ab);
	robject_release(node->l_value);
	free(node);
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

	


static struct ast_object_ops literal_ops=
{
	.ao_free=literal_free,
#ifdef AST_MACHINE 
	.ao_execute=literal_execute,
#endif /*AST_MACHINE*/
};

AstNodeLiteral* ast_create_literal(Robject* r)
{
	AstNodeLiteral* node=(AstNodeLiteral*) malloc(sizeof(*node));
	AstObject* base=AST_BASE(node);
	ast_init(base,ATN_LITERAL,"AstNodeLiteral",&literal_ops);
	robject_addref(r);
	node->l_value=r;
	return node;
}









