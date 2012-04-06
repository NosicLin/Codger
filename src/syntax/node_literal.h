#ifndef _CODGER_SYNTAX_AST_NODE_LITERAL_H_
#define _CODGER_SYNTAX_AST_NODE_LITERAL_H_
#include"node_type.h"
#include"ast_object.h"
#include<object/robject.h>
/* literal */
struct ast_node_literal
{
	INHERIT_AST_OBJECT;
	struct robject* l_value;
};

typedef struct ast_node_literal AstNodeLiteral;

AstNodeLiteral* ast_create_literal(Robject*);

/*getter and setter */
static inline Robject* ast_literal_get_value(AstNodeLiteral* node)
{
	robject_addref(node->l_value);
	return node->l_value;
}

AST_TYPE_CAST(LITERAL,Literal,ATN_LITERAL);

#endif 
