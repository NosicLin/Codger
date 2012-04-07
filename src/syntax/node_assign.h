#ifndef _CODGER_SYNTAX_NODE_ASSIGN_H_
#define _CODGER_SYNTAX_NODE_ASSIGN_H_
#include"ast_object.h"
#include"node_var.h"
struct ast_node_assign
{
	INHERIT_AST_OBJECT;
	AstObject* a_left;
	AstObject*  a_right;
};
typedef struct ast_node_assign AstNodeAssign;
AstNodeAssign* ast_create_assign(AstObject* left,AstObject* right);

char* ast_check_can_assign(AstObject* ab);

AST_TYPE_CAST(ASSIGN,Assign,ATN_ASSIGN);



#endif 
