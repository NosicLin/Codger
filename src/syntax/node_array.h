#ifndef _CODGER_SYNTAX_NODE_ARRAY_H_
#define _CODGER_SYNTAX_NODE_ARRAY_H_
#include "ast_object.h"
#include "node_type.h"
struct ast_node_array
{
	INHERIT_AST_OBJECT;
	struct ast_object* a_exprs;
};
typedef struct ast_node_array AstNodeArray;

AstNodeArray* ast_create_array(AstObject* exprs);
AST_TYPE_CAST(ARRAY,Array,ATN_ARRAY);

#endif 


