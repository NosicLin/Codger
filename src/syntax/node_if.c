#include"node_if.h"
#include<rstd/redy_std.h>
#include<vm/except.h>


#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

static void if_free_self(AstObject* ab)
{
	AstNodeIf* node=AST_TO_IF(ab);
	ry_free(node);
}
static void if_free(AstObject* ab)
{
	AstNodeIf* node=AST_TO_IF(ab);
	struct list_head* head=&node->i_chirdren;
	AstNodeIfSub* p;
	struct list_head* cur;
	while(!list_empty(head))
	{
		cur=head->next;
		list_del(cur);
		p=list_entry(cur,AstNodeIfSub,s_sibling);
		ast_free(IF_SUB_TO_AST(p));
	}
	ry_free(node);
}

static void if_sub_free_self(AstObject* ab)
{
	AstNodeIfSub* node=AST_TO_IF_SUB(ab);
	ry_free(node);
}
static void  if_sub_free(AstObject* ab)
{
	AstNodeIfSub* node=AST_TO_IF_SUB(ab);
	ast_free(node->s_stmts);
	if(node->s_expr)
	{
		ast_free(node->s_expr);
	}
	ry_free(node);
}
#ifdef AST_MACHINE
static int if_execute(AstObject* ab)
{
	AstNodeIf* node=AST_TO_IF(ab);
	struct list_head* head=&node->i_chirdren;
	AstNodeIfSub* p;
	int ret=AST_EXE_SUCCESS;
	list_for_each_entry(p,head,s_sibling)
	{
		ret=ast_execute(IF_SUB_TO_AST(p));
		if(ret<0)
		{
			break;
		}
		if(ret==AST_EXE_CONDITION_TRUE)
		{
			ret=AST_EXE_SUCCESS;
			break;
		}
		if(ret==AST_EXE_BREAK)
		{
			except_syntax_err_format("break stmt can't in if");
			ret=AST_EXE_EXCEPTION;
			break;
		}
		if(ret==AST_EXE_CONTINUE)
		{
			except_syntax_err_format("continue stmt can't in if");
			ret=AST_EXE_EXCEPTION;
			break;
		}
		if(ret==AST_EXE_RETURN)
		{
			break;
		}
	}
	return ret;
}

static int if_sub_execute(AstObject* ab)
{
	AstNodeIfSub* node=AST_TO_IF_SUB(ab);
	Robject* expr_value=0;
	AstObject* expr=node->s_expr;
	AstObject* stmts=node->s_stmts;
	int ret;
	int bool_flags;
	int exe_info;
	
	if(expr==NULL)
	{
		bool_flags=1;
	}
	else
	{
		exe_info=ast_execute(expr);
		if(exe_info<0)
		{
			ret=exe_info;
			goto error;
		}
		expr_value=get_reg0();
		bool_flags=robject_bool(expr_value);
		robject_release(expr_value);
		expr_value=0;
		if(vm_except_happened())
		{
			assert(bool_flags<0);
			ret=AST_EXE_EXCEPTION;
			goto error;
		}
	}
	if(bool_flags)
	{
		exe_info=ast_execute(stmts);
		if(exe_info<0)
		{
			ret=exe_info;
			goto error;
		}
		if(exe_info!=AST_EXE_SUCCESS)
		{
			ret=exe_info;
			goto over;
		}
		ret=AST_EXE_CONDITION_TRUE;
	}
	else
	{
		ret=AST_EXE_SUCCESS;
	}
over:
error:
	return ret;
}

#endif 
static AstNodeType node_if=
{
	.n_name="If",
	.n_type=ATN_IF,
	.n_free=if_free,
	.n_free_node=if_free_self,
#ifdef AST_MACHINE
	.n_execute=if_execute,
#endif 
};
static AstNodeType node_if_sub=
{
	.n_name="IfSub",
	.n_type=ATN_IF_SUB,
	.n_free=if_sub_free,
	.n_free_node=if_sub_free_self,
#ifdef AST_MACHINE
	.n_execute=if_sub_execute,
#endif
};

AstNodeIf* ast_create_if()
{
	AstNodeIf* node=ast_node_new(AstNodeIf,&node_if);
	if(node==NULL)
	{
		return NULL;
	}
	INIT_LIST_HEAD(&node->i_chirdren);
	return node;
}

AstNodeIfSub* ast_create_if_sub(AstObject* expr,AstObject* stmts)
{
	AstNodeIfSub* node=ast_node_new(AstNodeIfSub,&node_if_sub);
	if(node==NULL)
	{
		return NULL;
	}
	node->s_expr=expr;
	node->s_stmts=stmts;
	return node;
}
	


		

	



