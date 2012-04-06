#include"node_get_item.h"
#include<object/robject.h>
#include<vm/except.h>
#include<rtype/bt_string.h>
#include"node_var.h"

#ifdef AST_MACHINE 
#include"ast_machine.h"
#endif 


#ifdef AST_MACHINE
static int get_item_execute(AstObject* ab)
{
	AstNodeGetItem* node=AST_TO_GET_ITEM(ab);

	Robject* host=0;
	Robject* index=0;
	Robject* value=0;

	int exe_info=0;
	int ret=AST_EXE_SUCCESS;

	exe_info=ast_execute(node->i_host);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	host=get_reg0();

	exe_info=ast_execute(node->i_index);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	index=get_reg0();

	value=robject_get_item(host,index);
	if(value==NULL)
	{
		assert(vm_except_happened());
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	set_reg0(value);
error:
	if(host) robject_release(host);
	if(index) robject_release(index);
	if(value) robject_release(value);
	return ret;
}
#endif 

static AstNodeType  node_get_item=
{
	.n_type=ATN_GET_ITEM,
	.n_name="GetItem",
	.n_belong=ANF_BINARY,
#ifdef AST_MACHINE
	.n_execute=get_item_execute,
#endif
};

AstNodeGetItem* ast_create_get_item(AstObject* host,AstObject* expr)
{
	AstNodeGetItem* node=ast_node_new(AstNodeGetItem,&node_get_item);
	if(node==NULL)
	{
		return NULL;
	}
	node->i_host=host;
	node->i_index=expr;
	return node;
}










