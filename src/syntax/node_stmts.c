#include"node_stmts.h"
#include"ast_machine.h"
#include"vm/except.h"
#include<rstd/redy_std.h>

static void stmts_free(AstObject* ab)
{
	AstNodeStmts* stmts=AST_TO_STMTS(ab);
	struct list_head* head=&stmts->s_chirldren;
	AstNodeStmt* p;
	struct list_head* cur;
	while(!list_empty(head))
	{
		cur=head->next;
		list_del(cur);
		p=list_entry(cur,AstNodeStmt,s_sibling);
		ast_free(STMT_TO_AST(p));
	}
	ry_free(stmts);
			
}
static void stmts_free_self(AstObject* ab)
{
	AstNodeStmts* stmts=AST_TO_STMTS(ab);
	ry_free(stmts);
}

#ifdef AST_MACHINE 
static int stmts_execute(AstObject* ab)
{
	AstNodeStmts* stmts=AST_TO_STMTS(ab);
	struct list_head* head=&stmts->s_chirldren;
	AstNodeStmt* p;
	int ret=0;
	list_for_each_entry(p,head,s_sibling)
	{
		ret=ast_execute(STMT_TO_AST(p));
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
	.n_free=stmts_free,
	.n_free_node=stmts_free_self,
#ifdef AST_MACHINE
	.n_execute=stmts_execute,
#endif 
};

AstNodeStmts* ast_create_stmts()
{
	AstNodeStmts* node=ast_node_new(AstNodeStmts,&node_stmts);
	INIT_LIST_HEAD(&node->s_chirldren);
	return node;
}
	

	







