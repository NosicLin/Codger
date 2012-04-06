#ifndef _CODGER_SYNTAX_AST_NODE_STMTS_H_
#define _CODGER_SYNTAX_AST_NODE_STMTS_H_
#include"node_type.h"
#include"ast_object.h"
#include<utility_c/list_head.h>

typedef struct ast_object AstNodeStmts;

AST_TYPE_CAST(STMTS,Stmts,ATN_STMTS);

AstNodeStmts* ast_create_stmts();

static inline void ast_stmts_add(AstNodeStmts* father,AstObject* chirld)
{
	ast_node_add(STMTS_TO_AST(father),chirld);
}
static inline void ast_stmts_remove(AstNodeStmts* father,AstObject* chirld)
{
	ast_node_del(STMTS_TO_AST(father),chirld);
}

#endif  /*_CODGER_SYNTAX_AST_NODE_STMTS_H_*/

