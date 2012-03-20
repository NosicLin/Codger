#ifndef _REDY_SYNTAX_AST_NODE_LITERAL_H_
#define _REDY_SYNTAX_AST_NODE_LITERAL_H_
#include"node_type.h"
#include<rtype/robject.h>
/* literal */
struct ast_node_literal
{
	struct ast_object l_base;
	struct robject* l_value;
};

typedef struct ast_node_literal AstNodeLiteral;
AstNodeLiteral* ast_create_literal();

/*getter and setter */
static inline Robject* ast_literal_get_value(AstNodeLiteral* node)
{
	robject_addref(node->l_value);
	return node->l_value;
}

AST_TYPE_CAST(LITERAL,Literal,ATN_LITERAL);

#endif 
