#ifndef _CODGER_SYNTAX_NODE_FOR_H_
#define _CODGER_SYNTAX_NODE_FOR_H_
#include"ast_object.h"
struct ast_node_for
{
	INHERIT_AST_OBJECT;
	int f_id;
	AstObject* f_symbols;
	AstObject* f_expr;
	AstObject* f_stmts;
};

typedef struct ast_node_for AstNodeFor;
AST_TYPE_CAST(FOR,For,ATN_FOR);
AstNodeFor* ast_create_for(AstObject* symbols,AstObject* expr,AstObject* stmts);
#endif 

