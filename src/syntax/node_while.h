#ifndef _REDY_SYNTAX_NODE_WHILE_H_
#define _REDY_SYNTAX_NODE_WHILE_H_
#include"ast_object.h"
struct ast_node_while
{
	INHERIT_AST_OBJECT;
	struct ast_object* w_expr;
	struct ast_object* w_stmts;
};
typedef struct ast_node_while AstNodeWhile;

AST_TYPE_CAST(WHILE,While,ATN_WHILE);

AstNodeWhile* ast_create_while(AstObject* expr,AstObject* stmts);

#endif 

