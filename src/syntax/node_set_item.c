#include"node_set_item.h"
#include"symbol_table.h"
#include<rtype/bt_string.h>
#include<object/robject.h>
#include"node_var.h"

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif

#ifdef AST_MACHINE
static int set_item_execute(AstObject* ab)
{
	AstNodeSetItem* node=AST_TO_SET_ITEM(ab);
	
	BtString* symbol=AST_TO_VAR(node->s_symbol)->i_value;
	Robject* key=S_TO_R(symbol);

	Robject* index=0;
	Robject* value=0;
	Robject* item=0;

	int ret=AST_EXE_SUCCESS;
	int ret_info=0;

	/* exe value */
	ret_info=ast_execute(node->s_value);
	if(ret_info<0)
	{
		ret=ret_info;
		goto error;
	}
	value=get_reg0();

	/* exe index */
	ret_info=ast_execute(node->s_index);
	if(ret_info<0)
	{
		ret=ret_info;
		goto error;
	}
	index=get_reg0();

	item=symbol_get_local(key);

	if(item==NULL)
	{
		except_name_err_format("name %s is not define", symbol->s_value);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	ret_info=robject_set_item(item,index,value);
	if(ret_info<0)
	{
		assert(vm_except_happened());
		ret=AST_EXE_EXCEPTION;
		goto error;
	}

error:
	if(item) robject_release(item);
	if(index) robject_release(index);
	if(value) robject_release(value);
	return ret;
}
#endif 


static AstNodeType node_set_item=
{
	.n_type=ATN_SET_ITEM,
	.n_name="SetItem",
	.n_belong=ANF_TRIPLE,
#ifdef AST_MACHINE
	.n_execute=set_item_execute,
#endif
};

AstNodeSetItem* ast_create_set_item(AstObject* symbol,AstObject* index,AstObject* value)
{
	AstNodeSetItem* node=ast_node_new(AstNodeSetItem,&node_set_item);
	if(node==NULL)
	{
		return NULL;
	}
	node->s_symbol=symbol;
	node->s_index=index;
	node->s_value=value;
	return node;
}



	



