#ifndef _REDY_SYNTAX_AST_NODE_STMTS_H_
#define _REDY_SYNTAX_AST_NODE_STMTS_H_
#include"node_type.h"
#include"ast_node_stmt.h"
#include<utility_c/list_head.h>

struct ast_node_stmts
{
	BASE_AST_OBJECT;
	struct list_head s_chirldren;
};
typedef struct ast_node_stmts AstNodeStmts;
AST_TYPE_CAST(STMTS,Stmts,ATN_STMTS);

AstNodeStmts* ast_create_stmts();

static inline void ast_stmts_add(AstNodeStmts* stmts,AstNodeStmt* node)
{
	list_add_tail(&node->s_sibling,&stmts->s_chirldren);
}
static inline void ast_stmts_remove(AstNodeStmt* node)
{
	list_del(&node->s_sibling);
}

#endif  /*_REDY_SYNTAX_AST_NODE_STMTS_H_*/

