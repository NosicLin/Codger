#ifndef _REYD_SYNTAX_NODE_IF_H_
#define _REYD_SYNTAX_NODE_IF_H_
#include"ast_object.h"
#include<utility_c/list_head.h>
struct  ast_node_if
{
	INHERIT_AST_OBJECT;
	struct list_head i_chirdren;
};
typedef struct ast_node_if AstNodeIf;
struct ast_node_if_sub
{
	INHERIT_AST_OBJECT;
	struct list_head s_sibling;
	AstObject* s_expr;
	AstObject* s_stmts;
};
typedef struct ast_node_if_sub AstNodeIfSub;

AST_TYPE_CAST(IF,If,ATN_IF);
AST_TYPE_CAST(IF_SUB,IfSub,ATN_IF_SUB);

AstNodeIf* ast_create_if();
static inline void ast_if_add(AstNodeIf* n,AstNodeIfSub* s_n)
{
	list_add_tail(&s_n->s_sibling,&n->i_chirdren);
}

AstNodeIfSub* ast_create_if_sub(AstObject* expr,AstObject* stmts);



	
#endif /*_REYD_SYNTAX_NODE_IF_H_*/
