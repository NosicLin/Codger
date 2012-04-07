#ifndef _CODGER_SYNTAX_NODE_ARG_H_
#define _CODGER_SYNTAX_NODE_ARG_H_
#include"ast_object.h"
#include<object/robject.h>
struct  ast_node_arg
{
	INHERIT_AST_OBJECT;
	Robject* a_name;
	AstObject* a_expr;
};

typedef struct ast_node_arg AstNodeArg;
AST_TYPE_CAST(ARG,Arg,ATN_ARG);
AstNodeArg* ast_create_arg(Robject* name,AstObject* expr);

#endif /*_CODGER_SYNTAX_NODE_ARG_H_*/



