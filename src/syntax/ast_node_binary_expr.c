#include"ast_nodes.h"
#include"ast_machine.h"
#include<vm/except.h>

static void binary_expr_free(AstObject* ab)
{
	AstBinaryExpr* bexpr=(AstBinaryExpr*) ab;

	ast_object_free(bexpr->b_left);
	ast_object_free(bexpr->b_right);
	free(bexpr);
}
#ifdef AST_MACHINE
static int mul_execute(AstObject* ab)
{
	AstNodeMul* node=AST_TO_MUL(ab);
	Robject* left_value=0;
	Robject* right_value=0;
	Robject* mul_value=0;
	int ret=AST_EXE_SUCCESS;
	int exe_info;
	exe_info=ast_execute(node->b_left);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	Robject* left_value=get_reg0();
	exe_info=ast_execute(node->b_right);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	Robject* right_value=get_reg0();
	mul_value=robject_mul(left_value,right_value);
	if(vm_except_happened())
	{
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	set_reg0(mul_value);
error:
	if(left_value) robject_release(left_value);
	if(right_value) robject_release(right_value);
	if(mul_value) robject_release(mul_value);
	return ret;
}
#endif 


static struct ast_object_ops mul_ops=
{

	.ao_free=binary_expr_free,
#ifdef AST_MACHINE
	.ao_execute=mul_execute,
#endif 
};

AstNodeMul* ast_create_mul()
{
	AstNodeMul* node=(AstNodeMul*) malloc(sizeof(*node));
	AstObject* base=&node->b_base;
	ast_init(base,ATN_MUL,"AstNodeMul",&mul_ops);
	return node;
}




