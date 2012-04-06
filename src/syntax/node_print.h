#ifndef _CODGER_SYNTAX_AST_PRINT_H_
#define _CODGER_SYNTAX_AST_PRINT_H_
#include"ast_object.h"
struct ast_node_print
{
	INHERIT_AST_OBJECT;
	struct ast_object* p_expr;
};
typedef struct ast_node_print AstNodePrint;

AstNodePrint* ast_create_print(AstObject* expr);

AST_TYPE_CAST(PRINT,Print,ATN_PRINT);
#endif /*_CODGER_SYNTAX_AST_PRINT_H_*/

