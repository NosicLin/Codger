#include"ast_node_stmt.h"
#include"ast_machine.h"
#include<stdlib.h>
static void  stmt_free(AstObject* ab)
{
	AstNodeStmt* stmt=AST_TO_STMT(ab);
	ast_free(stmt->s_value);
	free(stmt);
}
#ifdef AST_MACHINE 
static int stmt_execute(AstObject* ab)
{
	AstNodeStmt* stmt=AST_TO_STMT(ab);
	int ret=ast_execute(stmt->s_value);
	if(ret>=0)
	{
		Robject* r=get_reg0();
		robject_print(r);
		robject_release(r);
	}
	return ret;
}
#endif /*AST_MACHINE */

static struct ast_object_ops stmt_ops=
{
	.ao_free=stmt_free,
#ifdef AST_MACHINE 
	.ao_execute=stmt_execute,
#endif 
};

AstNodeStmt* ast_create_stmt(AstObject* ab)
{
	AstNodeStmt* stmt=(AstNodeStmt*)malloc(sizeof(*stmt));
	INIT_LIST_HEAD(&stmt->s_list);
	stmt->s_value=ab;
	AstObject* base=AST_BASE(stmt);
	ast_init(base,ATN_STMT,"AstNodeStmt",&stmt_ops);
	return stmt;
}
	

