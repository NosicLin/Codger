#ifndef _REDY_SYNTAX_NODE_GET_ITEM_H_
#define _REDY_SYNTAX_NODE_GET_ITEM_H_

#include"ast_object.h"
struct ast_node_get_item
{
	INHERIT_AST_OBJECT;
	AstObject* i_host;
	AstObject* i_index;
};
typedef struct ast_node_get_item AstNodeGetItem;

AST_TYPE_CAST(GET_ITEM,GetItem,ATN_GET_ITEM);

AstNodeGetItem* ast_create_get_item(AstObject* host,AstObject* index);



#endif 

