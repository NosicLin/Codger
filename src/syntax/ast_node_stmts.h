#ifndef _REDY_SYNTAX_AST_NODE_STMTS_H_
#define _REDY_SYNTAX_AST_NODE_STMTS_H_
#include"node_type.h"
#include"ast_node_stmt.h"
#include<utility_c/list_head.h>

struct ast_node_stmts
{
	BASE_AST_OBJECT;
	struct list_head st_head;
};
typedef struct ast_node_stmts AstNodeStmts;
AST_TYPE_CAST(STMTS,stmts,ATN_STMTS);

static inline void ast_stmts_add(AstNodeStmts* stmts,AstNodeStmt* node)
{
	list_head_add_tail(&stmts->st_head,&node->s_list);
}
static inline void ast_stmts_remove(AstNodeStmt* node)
{
	list_head_del(&node->s_list);
}

#endif  /*_REDY_SYNTAX_AST_NODE_STMTS_H_*/

