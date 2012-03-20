#ifndef _REDY_SYNTAX_AST_NODE_STMT_H_
#define _REDY_SYNTAX_AST_NODE_STMT_H_
#include"node_type.h"
#include<utility_c/list_head.h>
struct ast_node_stmt
{
	BASE_AST_OBJECT;
	struct list_head s_list;
	AstObject* s_value;
};
typedef struct ast_node_stmt AstNodeStmt;
AST_TYPE_CAST(STMT,Stmt,ATN_STMT);


/*getter and setter */
static inline void ast_stmt_set_value(AstNodeStmt* stmt,AstObject* ab)
{
	stmt->s_value=ab;
}
static inline AstObject* ast_stmt_get_value(AstNodeStmt* stmt)
{
	return stmt->s_value;
}
AstNodeStmt* ast_create_stmt();

#endif 
