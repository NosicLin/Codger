#include"ast_node_stmts.h"
#include<stdlib.h>
#include"ast_machine.h"
#include<vm/except.h>

static void stmts_free(AstObject* ab)
{
	AstNodeStmts* stmts=AST_TO_STMTS(ab);
	struct list_head* head=&stmts->st_head;
	AstNodeStmt* p;
	struct list_head* cur;
	while(!list_empty(head))
	{
		cur=head->next;
		list_del(cur);
		p=list_entry(cur,AstNodeStmt,s_list);
		ast_free(STMT_TO_AST(p));
	}
	free(stmts);
			
}

#ifdef AST_MACHINE 
static int stmts_execute(AstObject* ab)
{
	AstNodeStmts* stmts=AST_TO_STMTS(ab);
	struct list_head* head=&stmts->st_head;
	AstNodeStmt* p;
	int ret=0;
	list_for_each_entry(p,head,s_list)
	{
		ret=ast_execute(STMT_TO_AST(p));
		if(ret<0)
		{
			if(vm_except_happened())
			{
				vm_clear_except();
			}
//			break;
		}
	}
	return ret;
}
#endif /*AST_MACHINE*/

static struct ast_object_ops stmts_ops=
{
	.ao_free=stmts_free,
#ifdef AST_MACHINE
	.ao_execute=stmts_execute,
#endif 
};

AstNodeStmts* ast_create_stmts()
{
	AstNodeStmts* node=(AstNodeStmts*) malloc(sizeof(*node));
	INIT_LIST_HEAD(&node->st_head);
	AstObject* base=AST_BASE(node);
	ast_init(base,ATN_STMTS,"AstNodeStmts",&stmts_ops);
	return node;
}
	

	







