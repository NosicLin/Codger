#ifndef _CODGER_SYNTAX_NODE_GET_ITEM_H_
#define _CODGER_SYNTAX_NODE_GET_ITEM_H_

#include"ast_object.h"
struct ast_node_square
{
	INHERIT_AST_OBJECT;
	AstObject* i_host;
	AstObject* i_index;
};
typedef struct ast_node_square AstNodeSquare;

AST_TYPE_CAST(SQUARE,Square,ATN_SQUARE);

AstNodeSquare* ast_create_square(AstObject* host,AstObject* index);



#endif 

