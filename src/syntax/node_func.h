#ifdef _CODGER_SYNTAX_NODE_FUNC
#define _CODGER_SYNTAX_NODE_FUNC
#include"ast_object.h"

struct ast_node_func
{
	INHERIT_AST_OBJECT;
	AstObject* f_args;
	AstObject* f_stmts;
};
typedef struct ast_node_func AstNodeFunc;
AST_TYPE_CAST(FUNC,Func,ATN_FUNC);
AstNodeFunc* ast_create_func(AstObject* args,AstObject* stmts);

#ifdef AST_MACHINE
int ast_func_call(AstNodeFunc* f);
#endif /*AST_MACHINE*/

#endif /*_CODGER_SYNTAX_NODE_FUNC*/



