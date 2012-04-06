#ifndef _CODGER_SYNTAX_NODE_IF_H_
#define _CODGER_SYNTAX_NODE_IF_H_
#include"ast_object.h"
#include<utility_c/list_head.h>

typedef struct ast_object AstNodeIf;

struct ast_node_if_sub
{
	INHERIT_AST_OBJECT;
	AstObject* s_expr;
	AstObject* s_stmts;
};
typedef struct ast_node_if_sub AstNodeIfSub;

AST_TYPE_CAST(IF,If,ATN_IF);
AST_TYPE_CAST(IF_SUB,IfSub,ATN_IF_SUB);

AstNodeIf* ast_create_if();
static inline void ast_if_add(AstNodeIf* n,AstNodeIfSub* s_n)
{
	ast_node_add(IF_TO_AST(n),IF_SUB_TO_AST(s_n));
}

AstNodeIfSub* ast_create_if_sub(AstObject* expr,AstObject* stmts);



	
#endif /*_CODGER_SYNTAX_NODE_IF_H_*/
