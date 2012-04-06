#include"node_array.h"
#include<rtype/bt_array.h>
#include<rstd/redy_std.h>
#include<vm/except.h>

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

#ifdef AST_MACHINE
static int array_execute(AstObject* ab)
{
	AstNodeArray* node=AST_TO_ARRAY(ab);
	struct list_head* head=&node->a_exprs->a_chirldren;
	AstObject* p;
	int ret=AST_EXE_SUCCESS;
	int ret_info;
	Robject* val=0;
	BtArray* array=btarray_create();
	if(array==NULL)
	{
		assert(vm_except_happened());
		return AST_EXE_EXCEPTION;
	}
	list_for_each_entry(p,head,a_sibling)
	{
		ret_info=ast_execute(p);
		if(ret_info<0)
		{
			ret=ret_info;
			goto error;
		}
		val=get_reg0();
		ret_info=btarray_push_back(array,val);
		robject_release(val);

		if(ret_info<0)
		{
			assert(vm_except_happened());
			ret=AST_EXE_EXCEPTION;
			goto error;
		}
	}
	set_reg0(A_TO_R(array));

error:
	if(array) robject_release(A_TO_R(array));
	return ret;
}	
#endif 
static AstNodeType node_array=
{
	.n_name="Array",
	.n_type=ATN_ARRAY,
	.n_belong=ANF_UNARY,
#ifdef AST_MACHINE
	.n_execute=array_execute,
#endif 
};

AstNodeArray* ast_create_array(AstObject* exprs)
{
	AstNodeArray* node=ast_node_new(AstNodeArray,&node_array);
	if(node==NULL)
	{
		return NULL;
	}
	node->a_exprs=exprs;
	return node;
}

