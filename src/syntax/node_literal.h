#ifndef _CODGER_SYNTAX_AST_NODE_LITERAL_H_
#define _CODGER_SYNTAX_AST_NODE_LITERAL_H_
#include"node_type.h"
#include"ast_object.h"
#include<object/robject.h>
/* literal */
struct ast_node_literal
{
	INHERIT_AST_OBJECT;
	unsigned long l_id;
};

typedef struct ast_node_literal AstNodeLiteral;

AstNodeLiteral* ast_create_literal(int id);

/*getter and setter */
static inline unsigned long ast_literal_id(AstNodeLiteral* node)
{
	return node->l_id;
}

AST_TYPE_CAST(LITERAL,Literal,ATN_LITERAL);

#endif 
