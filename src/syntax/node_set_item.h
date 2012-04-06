#ifndef _CODGER_SYNTAX_NODE_SET_ITEM_H_
#define _CODGER_SYNTAX_NODE_SET_ITEM_H_
#include"ast_object.h"
struct ast_node_set_item
{
	INHERIT_AST_OBJECT;
	AstObject* s_symbol;
	AstObject* s_index;
	AstObject* s_value;
};

typedef struct ast_node_set_item AstNodeSetItem;
AstNodeSetItem* ast_create_set_item(AstObject* symobl,
									AstObject* index,AstObject* value);
AST_TYPE_CAST(SET_ITEM,SetItem,ATN_SET_ITEM);

#endif  /*_CODGER_SYNTAX_NODE_SET_ITEM_H_*/

