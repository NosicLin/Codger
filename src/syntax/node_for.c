#include"node_for.h"
#include"symbol_table.h"
#include<vm/except.h>

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 


#ifdef AST_MACHINE
static int for_execute(AstObject* ab)
{
	AstNodeFor* node=AST_TO_FOR(ab);

	Robject* iter=0;
	Robject* expr=0;
	Robject* next=0;

	int ret=AST_EXE_SUCCESS;
	int ret_info=0;
	
	
	ret_info=ast_execute(node->f_expr);
	if(ret_info<0)
	{
		ret=ret_info;
		goto error;
	}

	expr=get_reg0();

	iter=robject_iter(expr);
	if(iter==NULL)
	{
		assert(vm_except_happened());
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	while(1)
	{
		next=robject_next(iter);
		if(next==NULL)
		{
			if(vm_except_type()==E_ITER_STOP)
			{
				vm_clear_except();
				break;
			}
			ret=AST_EXE_EXCEPTION;
			goto error;
		}
		ret_info=ast_set_value(node->f_symbols,next);
		robject_release(next);
		next=0;
		if(ret_info<0)
		{
			assert(vm_except_happened());
			ret=ret_info;
			goto error;
		}
		ret_info=ast_execute(node->f_stmts);
		if(ret_info<0)
		{
			assert(vm_except_happened());
			ret=ret_info;
			goto error;
		}
		if(ret_info==AST_EXE_BREAK)
		{
			break;
		}
		if(ret_info==AST_EXE_CONTINUE)
		{
			continue;
		}
	}
error:
	if(expr) robject_release(expr);
	if(next) robject_release(next);
	if(iter) robject_release(iter);
	return ret;
}
#endif 

static AstNodeType node_for=
{
	.n_name="For",
	.n_type=ATN_FOR,
	.n_belong=ANF_FOR,
#ifdef AST_MACHINE
	.n_execute=for_execute,
#endif 
};

AstNodeFor* ast_create_for(AstObject* symbols,AstObject* expr,
							AstObject* stmts)
{
	static int id=0;
	AstNodeFor* node=ast_node_new(AstNodeFor,&node_for);
	if(node==NULL)
	{
		return NULL;
	}
	node->f_symbols=symbols;
	node->f_expr=expr;
	node->f_stmts=stmts;
	node->f_id=id++;
	return node;
}








