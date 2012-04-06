#ifndef _CODGER_SYNTAX_NODE_VAR_H_
#define _CODGER_SYNTAX_NODE_VAR_H_
#include<rtype/bt_string.h>
#include"ast_object.h"
#include"node_type.h"

struct ast_node_var
{
	INHERIT_AST_OBJECT;
	BtString* i_value;
};
typedef struct ast_node_var AstNodeVar;
AstNodeVar* ast_create_var(BtString* );

AST_TYPE_CAST(VAR,Var,ATN_VAR);
#endif /*_CODGER_SYNTAX_NODE_VAR_H_*/


