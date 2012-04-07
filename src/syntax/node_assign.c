#include"node_assign.h"
#include"symbol_table.h"
#include<rtype/bt_string.h>

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

#ifdef AST_MACHINE
static int assign_execute(AstObject* ab)
{
	AstNodeAssign* node=AST_TO_ASSIGN(ab);
	assert(node->a_left);
	int ret=AST_EXE_SUCCESS;

	int exe_info=ast_execute(node->a_right);
	if(exe_info<0)
	{
		return exe_info;
	}
	Robject* value=get_reg0();
	
	int ret_info=ast_set_value(node->a_left,value);
	robject_release(value);

	if(ret_info<0)
	{
		ret=ret_info;
	}
	return AST_EXE_SUCCESS;
}
#endif 

static AstNodeType node_assign=
{
	.n_type=ATN_ASSIGN,
	.n_name="Assign",
	.n_belong=ANF_BINARY,
#ifdef AST_MACHINE
	.n_execute=assign_execute,

#endif 
};

AstNodeAssign* ast_create_assign(AstObject* var,AstObject* expr)
{
	AstNodeAssign* ret=ast_node_new(AstNodeAssign,&node_assign);
	if(ret==NULL)
	{
		return ret;
	}
	ret->a_left=var;
	ret->a_right=expr;
	return ret;
}


static char s_msg_buf[128];
char* ast_check_can_assign(AstObject* var)
{
	AstNodeType* t=var->a_type;
	int type_id=t->n_type;
	if(type_id==ATN_SQUARE)
	{
		return NULL;
	}
	if(type_id==ATN_VAR)
	{
		return NULL;
	}

	const char* node_name=t->n_name;
	
	snprintf(s_msg_buf,128,"SyntaxError:can't assign to '%s'",node_name);
	return s_msg_buf;
}















