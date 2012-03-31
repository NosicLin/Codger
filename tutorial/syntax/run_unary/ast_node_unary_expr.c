#include"ast_node_unary_expr.h"
#ifdef AST_MACHINE 
#include"ast_machine.h"
#endif /*AST_MACHINE*/
#include<stdlib.h>
#include<vm/except.h>

static void unary_expr_free(AstObject* ab)
{
	AstNodeUExpr* uexpr=(AstNodeUExpr*)ab;
	ast_free(uexpr->u_value);
	free(uexpr);
}
static void unary_expr_free_self(AstObject* ab)
{
	AstNodeUExpr* uexpr=(AstNodeUExpr*)ab;
	free(uexpr);
}

#ifdef AST_MACHINE
#define UNARY_EXPR_EXECUTE(Hl,Ml,Ll)  \
static int Ll##_execute(AstObject* ab) \
{ \
	AstNode##Ml* node=AST_TO_##Hl(ab); \
	Robject* sub_value=0; \
	Robject* ret_value=0; \
	int ret=AST_EXE_SUCCESS; \
	int exe_info; \
	exe_info=ast_execute(node->u_value); \
	if(exe_info<0) \
	{ \
		ret=exe_info; \
		goto error; \
	} \
	sub_value=get_reg0(); \
	ret_value=robject_##Ll(sub_value); \
	if(vm_except_happened()) \
	{ \
		ret=AST_EXE_EXCEPTION; \
		goto error; \
	} \
	set_reg0(ret_value); \
error: \
	if(sub_value) robject_release(sub_value); \
	if(ret_value) robject_release(ret_value); \
	return ret; \
} 
#else 
#define UNARY_EXPR_EXECUTE(name)
#endif  /*AST_MACHINE*/

#ifdef AST_MACHINE 
#define AST_UEXPR_OPS(Ll) \
static struct ast_object_ops Ll##_ops= \
{ \
	.ao_free_self=&unary_expr_free_self, \
	.ao_free=&unary_expr_free, \
	.ao_execute=& Ll##_execute, \
};
#else 
#define AST_UEXPR_OPS(Ll) \
static struct ast_object_ops Ll##_ops= \
{ \
	.ao_free_self=&unary_expr_free_self, \
	.ao_free=&unary_expr_free, \
};
#endif /*AST_MACHINE*/


#define UEXPR_METHOD(Hl,Ml,Ll) \
	UNARY_EXPR_EXECUTE(Hl,Ml,Ll) \
AST_UEXPR_OPS(Ll) \
AstNode##Ml* ast_create_##Ll(AstObject* sub_node) \
{ \
	AstNode##Ml* node=(AstNode##Ml*) malloc(sizeof(*node)); \
	node->u_value=sub_node; \
	AstObject* base=AST_BASE(node); \
	ast_init(base,ATN_##Hl,"AstNode"#Ml ,& Ll##_ops); \
	return node; \
} 

UEXPR_METHOD(POSITIVE,Positive,positive);
UEXPR_METHOD(NEGATIVE,Negative,negative);
UEXPR_METHOD(NEGATED,Negated,negated);

