#include"node_square.h"
#include<object/robject.h>
#include<vm/except.h>
#include<rtype/bt_string.h>
#include"node_var.h"

#ifdef AST_MACHINE 
#include"ast_machine.h"
#endif 


#ifdef AST_MACHINE
static int square_execute(AstObject* ab)
{
	AstNodeSquare* node=AST_TO_SQUARE(ab);

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
static int square_set_value(AstObject* ab,Robject* value)
{
	AstNodeSquare* node=AST_TO_SQUARE(ab);

	Robject* host=0;
	Robject* index=0;

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

	exe_info=robject_set_item(host,index,value);
	if(exe_info<0)
	{
		assert(vm_except_happened());
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	set_reg0(value);
error:
	if(host) robject_release(host);
	if(index) robject_release(index);
	return ret;
}

#endif 

static AstNodeType  node_square=
{
	.n_type=ATN_SQUARE,
	.n_name="Square",
	.n_belong=ANF_BINARY,
#ifdef AST_MACHINE
	.n_execute=square_execute,
	.n_set_value=square_set_value,
#endif
};

AstNodeSquare* ast_create_square(AstObject* host,AstObject* expr)
{
	AstNodeSquare* node=ast_node_new(AstNodeSquare,&node_square);
	if(node==NULL)
	{
		return NULL;
	}
	node->i_host=host;
	node->i_index=expr;
	return node;
}










