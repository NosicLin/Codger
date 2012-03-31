#include"ast_nodes.h"
#include"ast_machine.h"
#include<vm/except.h>
#include<stdlib.h>
#include<rtype/bt_bool.h>

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
#define BINARY_CMP_EXECUTE(Hl,Ml,Ll)  \
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

/*bitwise_expr*/
BEXPR_METHOD(AND,And,and);
BEXPR_METHOD(XOR,Xor,xor);
BEXPR_METHOD(OR,Or,or);

#define BEXPR_CMP(Hl,Ml,Ll) \
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
static int cmp_execute(AstNodeBinary* node,int (*func)(Robject* x,Robject* y)) 
{ 
	assert(func);
	Robject* left_value=0; 
	Robject* right_value=0; 
	Robject* ret_value=0; 
	int cmp_value=0;
	int ret=AST_EXE_SUCCESS; 
	int exe_info; 
	exe_info=ast_execute(node->b_left); 
	if(exe_info<0) 
	{ 
		ret=exe_info; 
		goto error; 
	} 
	left_value=get_reg0(); 
	exe_info=ast_execute(node->b_right); 
	if(exe_info<0) 
	{ 
		ret=exe_info; 
		goto error; 
	} 
	right_value=get_reg0(); 
	cmp_value=(*func)(left_value,right_value); 
	if(vm_except_happened()) 
	{ 
		ret=AST_EXE_EXCEPTION;
		goto error; 
	} 
	if(ret_value==-1)
	{
		except_unkown_err_format("BUG Internal");
		goto error;
	}
	ret_value=btbool_create(cmp_value)
		set_reg0(ret_value);
	robject_release(ret_value);
	return ret;
error: 
	if(left_value) robject_release(left_value); 
	if(right_value) robject_release(right_value); 
	return ret; 
} 
static int lt_execute(AstObject* ab)
{
	AstNodeLt* node=AST_TO_LT(ab);
	return cmp_execute((AstNodeBinary*)node,ab->a_ops->ao_execute);
}

static int le_execute(AstObject* ab)
{
	AstNodeLe* node=AST_TO_LE(ab);
	return cmp_execute((AstNodeBinary*)node,ab->a_ops->ao_execute);
}
static int gt_execute(AstObject* ab)
{
	AstNodeGt* node=AST_TO_GT(ab);
	return cmp_execute((AstNodeBinary*)node,ab->a_ops->ao_execute);
}
static int ge_execute(AstObject* ab)
{
	AstNodeGe* node=AST_TO_GE(ab);
	return cmp_execute((AstNodeBinary*)node,ab->a_ops->ao_execute);
}
static int eq_execute(AstObject* ab)
{
	AstNodeEq* node=AST_TO_EQ(ab);
	return cmp_execute((AstNodeBinary*)node,ab->a_ops->ao_execute);
}
static int ne_execute(AstObject* ab)
{
	AstNodeNe* node=AST_TO_NE(ab);
	return cmp_execute((AstNodeBinary*)node,ab->a_ops->ao_execute);
}


/*logic expr*/

#ifdef AST_MACHINE 
static int logic_and_execute(AstObject* ab)
{
	AstNodeLogicAnd* node=AST_TO_LOGIC_AND(ab);
	Robject* logic_value=0;  
	int bool_flags=0;
	int  exe_info=0;
	int ret=AST_EXE_SUCCESS;

	/* left parts*/
	exe_info=ast_execute(node->b_left);
	if(exe_info<0)
	{
		ret=exe_info;
		goto  error;
	}
	logic_value=get_reg0();
	bool_flags=robject_bool(logic_value);
	if(vm_except_happened())
	{
		ret=AST_EXE_EXCEPTION;
		robject_release(logic_value);
		logic_value=0;
		goto error;
	}
	if(!bool_flags) /*if left==false ;return*/
	{
		robject_release(logic_value); /*ret_value already in reg0*/
		logic_value=0;
		goto over;
	}
	robject_release(logic_value);
	logic_value=0;

	/*right parts*/
	exe_info=ast_execute(node->b_right);  
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}

over:
	return ret;
error:
	return ret;
}

static int logic_or_execute(AstObject* ab)
{
	AstNodeLogicOr* node=AST_TO_LOGIC_OR(ab);
	Robject* logic_value=0;  
	int bool_flags=0;
	int  exe_info=0;
	int ret=AST_EXE_SUCCESS;

	/* left parts*/
	exe_info=ast_execute(node->b_left);
	if(exe_info<0)
	{
		ret=exe_info;
		goto  error;
	}
	logic_value=get_reg0();
	bool_flags=robject_bool(logic_value);
	if(vm_except_happened())
	{
		ret=AST_EXE_EXCEPTION;
		robject_release(logic_value);
		logic_value=0;
		goto error;
	}
	if(!bool_flags) /*if left==false ;return*/
	{
		robject_release(logic_value); /*ret_value already in reg0*/
		logic_value=0;
		goto over;
	}
	robject_release(logic_value);
	logic_value=0;

	/*right parts*/
	exe_info=ast_execute(node->b_right);  
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}

over:
	return ret;
error:
	return ret;
}
#endif /*AST_MACHINE*/

static struct ast_object_ops  logic_and_ops=
{
	.ao_free_self=binary_expr_free_self,
	.ao_free=binary_expr_free,
#ifdef AST_MACHINE 
	.ao_execute=logic_and_execute,
#endif /*AST_MACHINE*/
};

static struct ast_object_ops  logic_or_ops=
{
	.ao_free_self=binary_expr_free_self,
	.ao_free=binary_expr_free,
#ifdef AST_MACHINE 
	.ao_execute=logic_or_execute,
#endif /*AST_MACHINE*/
};

AstNodeLogicAnd* ast_create_logic_and(AstObject* l,AstObject* r) 
{ 
	AstNodeLogicAnd* node=(AstNodeLogicAnd*) malloc(sizeof(*node)); 
	node->b_left=l; 
	node->b_right=r; 
	AstObject* base=AST_BASE(node); 
	ast_init(base,ATN_LOGIC_AND,"AstNodeLogicAnd",& logic_and_ops);
	return node; 
} 

AstNodeLogicOr* ast_create_logic_or(AstObject* l,AstObject* r) 
{ 
	AstNodeLogicOr* node=(AstNodeLogicOr*) malloc(sizeof(*node)); 
	node->b_left=l; 
	node->b_right=r; 
	AstObject* base=AST_BASE(node); 
	ast_init(base,ATN_LOGIC_OR,"AstNodeLogicOr",& logic_or_ops);
	return node; 
} 

