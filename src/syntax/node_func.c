#include"node_func.h"
#include"node_arg.h"
#include<object/func_object.h>


AstNodeType node_func=
{
	.n_type=ATN_FUNC,
	.n_name="Func",
	.n_belong=ANF_BINARY,
};

AstNodeFunc* ast_create_func(AstObject* args,AstObject* stmts)
{
	AstNodeFunc* node=ast_node_new(AstNodeFunc,&node_func);
	if(node==NULL)
	{
		return NULL;
	}
	node->f_args=args;
	node->f_stmts=stmts;
	return node;
}











