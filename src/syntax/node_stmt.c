#include"node_stmt.h"
#include"ast_machine.h"
#include<rstd/redy_std.h>
static void stmt_free_self(AstObject* ab)
{
	AstNodeStmt* stmt=AST_TO_STMT(ab);
	ry_free(stmt);
}

static void  stmt_free(AstObject* ab)
{
	AstNodeStmt* stmt=AST_TO_STMT(ab);
	ast_free(stmt->s_sub_node);
	ry_free(stmt);
}
#ifdef AST_MACHINE 
static int stmt_execute(AstObject* ab)
{
	AstNodeStmt* stmt=AST_TO_STMT(ab);
	int ret=ast_execute(stmt->s_sub_node);
	if(ret>=0)
	{
		Robject* r=get_reg0();
		robject_print(r,NULL,PRINT_FLAGS_NEWLINE);
		robject_release(r);
	}
	return ret;
}
#endif /*AST_MACHINE */

static AstNodeType node_stmt=
{
	.n_type=ATN_STMT,
	.n_name="Stmt",
	.n_free_node=stmt_free_self,
	.n_free=stmt_free,
#ifdef AST_MACHINE 
	.n_execute=stmt_execute,
#endif 
};

AstNodeStmt* ast_create_stmt(AstObject* ab)
{
	AstNodeStmt* stmt=ast_node_new(AstNodeStmt,&node_stmt);
	INIT_LIST_HEAD(&stmt->s_sibling);
	stmt->s_sub_node=ab;
	return stmt;
}
	

