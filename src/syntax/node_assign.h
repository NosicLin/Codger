#ifndef _REDY_SYNTAX_NODE_ASSIGN_H_
#define _REDY_SYNTAX_NODE_ASSIGN_H_
#include"ast_object.h"
#include"node_var.h"
struct ast_node_assign
{
	INHERIT_AST_OBJECT;
	AstNodeVar* a_var;
	AstObject*  a_expr;
};
typedef struct ast_node_assign AstNodeAssign;
AstNodeAssign* ast_create_assign(AstNodeVar* var,AstObject* expr);

AST_TYPE_CAST(ASSIGN,Assign,ATN_ASSIGN);



#endif 
