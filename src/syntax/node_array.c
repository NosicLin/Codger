#include"node_array.h"
#include<rtype/bt_array.h>
#include<rstd/redy_std.h>

#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

static void array_free(AstObject* ab)
{
	AstNodeArray* node=AST_TO_ARRAY(ab);
	ast_free(node->a_exprs);
	ry_free(node);
}
static void array_free_self(AstObject* ab)
{
	AstNodeArray* node=AST_TO_ARRAY(ab);
	ry_free(node);
}
#ifdef AST_MACHINE
static int array_execute(AstObject* ab)
{
	//AstNodeArray* node=AST_TO_ARRAY(ab);
	return 1;
}	
static AstNodeType node_array=
{
	.n_name="Array",
	.n_type=ATN_ARRAY,
	.n_free=array_free,
	.n_free_node=array_free_self,
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
}

