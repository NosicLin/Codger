#include"node_stmts.h"
#include"ast_machine.h"
#include"vm/except.h"
#include<rstd/redy_std.h>


#ifdef AST_MACHINE 
static int stmts_execute(AstObject* ab)
{
	AstNodeStmts* stmts=AST_TO_STMTS(ab);
	struct list_head* head=&stmts->a_chirldren;
	AstObject* p;
	int ret=0;
	list_for_each_entry(p,head,a_sibling)
	{
		ret=ast_execute(p);
		if(ret!=AST_EXE_SUCCESS)
		{
			break;
		}
	}
	return ret;
}
#endif /*AST_MACHINE*/

static AstNodeType node_stmts=
{
	.n_type=ATN_STMTS,
	.n_name="Stmts",
	.n_free=ast_node_free,
	.n_free_node=ast_node_free_self,
#ifdef AST_MACHINE
	.n_execute=stmts_execute,
#endif 
};

AstNodeStmts* ast_create_stmts()
{
	AstNodeStmts* node=ast_node_new(AstNodeStmts,&node_stmts);
	return node;
}
	

	







