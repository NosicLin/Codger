#ifndef _CODGER_SYNTAX_NODE_VAR_H_
#define _CODGER_SYNTAX_NODE_VAR_H_
#include<rtype/bt_string.h>
#include"ast_object.h"
#include"node_type.h"
#include<object/robject.h>

struct ast_node_var
{
	INHERIT_AST_OBJECT;
	Robject* v_value;
};
typedef struct ast_node_var AstNodeVar;
AstNodeVar* ast_create_var(Robject* );

AST_TYPE_CAST(VAR,Var,ATN_VAR);
#endif /*_CODGER_SYNTAX_NODE_VAR_H_*/


