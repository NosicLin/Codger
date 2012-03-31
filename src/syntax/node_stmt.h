#ifndef _REDY_SYNTAX_AST_NODE_STMT_H_
#define _REDY_SYNTAX_AST_NODE_STMT_H_
#include"node_type.h"
#include<utility_c/list_head.h>
#include"ast_object.h"
struct ast_node_stmt
{
	INHERIT_AST_OBJECT;
	struct list_head s_sibling;
	AstObject* s_sub_node;
};
typedef struct ast_node_stmt AstNodeStmt;
AST_TYPE_CAST(STMT,Stmt,ATN_STMT);


/*getter and setter */
static inline AstObject* ast_stmt_get_value(AstNodeStmt* stmt)
{
	return stmt->s_sub_node;
}
AstNodeStmt* ast_create_stmt(AstObject* ab);

#endif 
