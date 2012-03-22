#include"ast_nodes.h"
#include"ast_machine.h"
#include<vm/except.h>
#include<stdlib.h>

static void binary_expr_free(AstObject* ab)
{
	AstBinaryExpr* bexpr=(AstBinaryExpr*) ab;

	ast_free(bexpr->b_left);
	ast_free(bexpr->b_right);
	free(bexpr);
}
static void binary_expr_free_self(AstObject* ab)
{
	AstBinaryExpr* bexpr=(AstBinaryExpr*) ab;
	free(bexpr);
}

#ifdef AST_MACHINE
#define BINARY_EXPR_EXECUTE(Hl,Ml,Ll)  \
static int Ll##_execute(AstObject* ab) \
{ \
	AstNode##Ml* node=AST_TO_##Hl(ab); \
	Robject* left_value=0; \
	Robject* right_value=0; \
	Robject* ret_value=0; \
	int ret=AST_EXE_SUCCESS; \
	int exe_info; \
	exe_info=ast_execute(node->b_left); \
	if(exe_info<0) \
	{ \
		ret=exe_info; \
		goto error; \
	} \
	left_value=get_reg0(); \
	exe_info=ast_execute(node->b_right); \
	if(exe_info<0) \
	{ \
		ret=exe_info; \
		goto error; \
	} \
	right_value=get_reg0(); \
	ret_value=robject_##Ll(left_value,right_value); \
	if(vm_except_happened()) \
	{ \
		ret=AST_EXE_EXCEPTION; \
		goto error; \
	} \
	set_reg0(ret_value); \
error: \
	if(left_value) robject_release(left_value); \
	if(right_value) robject_release(right_value); \
	if(ret_value) robject_release(ret_value); \
	return ret; \
} 
#else 
#define BINARY_EXPR_EXECUTE(name)
#endif  /*AST_MACHINE*/

#ifdef AST_MACHINE 
#define AST_BEXPR_OPS(Ll) \
static struct ast_object_ops Ll##_ops= \
{ \
	.ao_free_self=&binary_expr_free_self, \
	.ao_free=& binary_expr_free, \
	.ao_execute=& Ll##_execute, \
};
#else 
#define AST_BEXPR_OPS(Ll) \
static struct ast_object_ops Ll##_ops= \
{ \
	.ao_free_self=&binary_expr_free_self, \
	.ao_free=binary_expr_free, \
};
#endif /*AST_MACHINE*/


#define BEXPR_METHOD(Hl,Ml,Ll) \
	BINARY_EXPR_EXECUTE(Hl,Ml,Ll) \
AST_BEXPR_OPS(Ll) \
AstNode##Ml* ast_create_##Ll(AstObject* l,AstObject* r) \
{ \
	AstNode##Ml* node=(AstNode##Ml*) malloc(sizeof(*node)); \
	node->b_left=l; \
	node->b_right=r; \
	AstObject* base=AST_BASE(node); \
	ast_init(base,ATN_##Hl,"AstNode"#Ml ,& Ll##_ops); \
	return node; \
} 

/* multiply_expr */
BEXPR_METHOD(MUL,Mul,mul); 
BEXPR_METHOD(DIV,Div,div); 
BEXPR_METHOD(MOD,Mod,mod); 

/* additive_expr*/
BEXPR_METHOD(PLUS,Plus,plus); 
BEXPR_METHOD(MINUS,Minus,minus); 

/* shift expr */ 
BEXPR_METHOD(LSHIFT,LShift,lshift); 
BEXPR_METHOD(RSHIFT,RShift,rshift); 

