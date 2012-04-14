#ifndef _CODGER_SYNTAX_AST_NODE_STMTS_H_
#define _CODGER_SYNTAX_AST_NODE_STMTS_H_
#include"node_type.h"
#include"ast_object.h"
#include<utility_c/list_head.h>
#include<rtype/bt_string.h>

AstNodeType node_stmts;
AstNodeType node_print;
AstNodeType node_for;
AstNodeType node_if;
AstNodeType node_if_elif;
AstNodeType node_else;
AstNodeType node_while;
AstNodeType node_expr;
AstNodeType node_assign;
AstNodeType node_break;
AstNodeType node_continue;
AstNodeType node_func;

enum ARG_TYPE
{
	ARG_UNKOWN=0,
	ARG_SIMPLY,
	ARG_DEFALUT_VALUE,
	ARG_MANY,
};
struct ast_node_arg
{
	INHERIT_AST_OBJECT;
	int a_type;
	BtString* a_name;
};
typedef struct ast_node_arg AstNodeArg;
AstObject* ast_create_arg(int type)
AST_TYPE_CAST(ARG,Arg,ATN_ARG);

#endif  /*_CODGER_SYNTAX_AST_NODE_STMTS_H_*/

