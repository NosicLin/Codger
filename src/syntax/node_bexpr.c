#include<vm/except.h>
#include<rtype/bt_bool.h>
#include<rstd/redy_std.h>
#include"node_bexpr.h"
#include"object/robject.h"
#include"ast_machine.h"

static void binary_expr_free(AstObject* ab)
{
	AstNodeBExpr* bexpr=(AstNodeBExpr*) ab;
	ast_free(bexpr->b_left);
	ast_free(bexpr->b_right);
	ry_free(bexpr);
}
static void binary_expr_free_self(AstObject* ab)
{
	AstNodeBExpr* bexpr=(AstNodeBExpr*) ab;
	ry_free(bexpr);
}


typedef Robject* (*binary_func)(Robject*,Robject*);
#ifdef AST_MACHINE
static int  binary_execute(AstNodeBExpr* node,binary_func func)
{
	Robject* left_value=0;
	Robject* right_value=0;
	Robject* ret_value=0;
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
	ret_value=func(left_value,right_value);
	if(vm_except_happened())
	{
		assert(ret_value==NULL);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	assert(ret_value!=NULL);
	set_reg0(ret_value);
error:
	if(left_value) robject_release(left_value);
	if(right_value) robject_release(right_value);
	if(ret_value) robject_release(ret_value);
	return ret;
}
#endif 

#define BINARY_EXECUTE(H,M,L) \
int L##_execute(AstObject* ab) \
{ \
	AstNode##M* node=AST_TO_##H(ab); \
	return binary_execute((AstNodeBExpr*)node,robject_##L);  \
} \
AstNode##M* ast_create_##L(AstObject* l,AstObject* r) \
{ \
	AstNode##M* node=ast_node_new(AstNode##M,&node_##L); \
	if(node==NULL) return NULL; \
	node->b_left=l; \
	node->b_right=r; \
	return node; \
}

#ifdef AST_MACHINE  

#define BINARY_METHOD(H,M,L) \
int L##_execute(AstObject*); \
static AstNodeType node_##L= \
{ \
	.n_type=ATN_##H, \
	.n_name=#M, \
	.n_free=binary_expr_free, \
	.n_free_node=binary_expr_free_self, \
	.n_execute=L##_execute, \
}; \
BINARY_EXECUTE(H,M,L)

#else 

#define BINARY_METHOD(H,M,L) \
int L##_execute(AstObject*); \
static AstNodeType node_##L= \
{ \
	.n_type=ATN_##H, \
	.n_name=#M, \
	.n_free=binary_expr_free, \
	.n_free_node=binary_expr_free_self, \
}; \
BINARY_EXECUTE(H,M,L)
#endif 

BINARY_METHOD(MUL,Mul,mul);
BINARY_METHOD(DIV,Div,div);
BINARY_METHOD(MOD,Mod,mod);
BINARY_METHOD(PLUS,Plus,plus);
BINARY_METHOD(MINUS,Minus,minus);
BINARY_METHOD(LSHIFT,LShift,lshift);
BINARY_METHOD(RSHIFT,RShift,rshift);
BINARY_METHOD(AND,And,and);
BINARY_METHOD(OR,Or,or);
BINARY_METHOD(XOR,Xor,xor);

typedef int (*cmp_func)(Robject* ,Robject*);
#ifdef AST_MACHINE
static int cmp_execute(AstNodeBExpr* node,cmp_func func)
{
	Robject* left_value=0;
	Robject* right_value=0;
	int ret_value=0;
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
	ret_value=func(left_value,right_value);
	if(vm_except_happened())
	{
		assert(ret_value<0);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	assert(ret>=0);
	Robject* real_ret=B_TO_R(btbool_create(ret_value));
	set_reg0(real_ret);
	robject_release(real_ret);
error:
	if(left_value) robject_release(left_value);
	if(right_value) robject_release(right_value);
	return ret;
}
#endif 


#define CMP_EXECUTE(H,M,L) \
int L##_execute(AstObject* ab) \
{ \
	AstNode##M* node=AST_TO_##H(ab); \
	return cmp_execute((AstNodeBExpr*)node,robject_##L);  \
} \
AstNode##M* ast_create_##L(AstObject* l,AstObject* r) \
{ \
	AstNode##M* node=ast_node_new(AstNode##M,&node_##L); \
	if(node==NULL) return NULL; \
	node->b_left=l; \
	node->b_right=r; \
	return node; \
}

#ifdef AST_MACHINE  

#define CMP_METHOD(H,M,L) \
int L##_execute(AstObject*); \
static AstNodeType node_##L= \
{ \
	.n_type=ATN_##H, \
	.n_name=#M, \
	.n_free=binary_expr_free, \
	.n_free_node=binary_expr_free_self, \
	.n_execute=L##_execute, \
}; \
CMP_EXECUTE(H,M,L)

#else 

#define CMP_METHOD(H,M,L) \
int L##_execute(AstObject*); \
static AstNodeType node_##L= \
{ \
	.n_type=ATN_##H, \
	.n_name=#M, \
	.n_free=binary_expr_free, \
	.n_free_node=binary_expr_free_self, \
}; \
CMP_EXECUTE(H,M,L)
#endif 

CMP_METHOD(LT,Lt,lt);
CMP_METHOD(LE,Le,le);
CMP_METHOD(GE,Ge,ge);
CMP_METHOD(GT,Gt,gt);
CMP_METHOD(EQ,Eq,eq);
CMP_METHOD(NE,Ne,ne);


static int logic_and_execute(AstObject* ab)
{
	AstNodeLogicAnd* node=AST_TO_LOGIC_AND(ab);
	Robject* left_value=0;
	Robject* right_value=0;
	int bool_flags=0;
	int ret=AST_EXE_SUCCESS;
	int exe_info;
	exe_info=ast_execute(node->b_left);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	left_value=get_reg0();
	bool_flags=robject_bool(left_value);
	if(vm_except_happened())
	{
		assert(bool_flags<0);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	if(!bool_flags)
	{
		set_reg0(left_value);
		goto over;
	}
	exe_info=ast_execute(node->b_right);
	if(exe_info<0)
	{
		ret=exe_info;
		goto  error;
	}
	right_value=get_reg0();
	bool_flags=robject_bool(right_value);
	if(vm_except_happened())
	{
		assert(bool_flags<0);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	set_reg0(right_value);
over:
error:
	if(left_value) robject_release(left_value);
	if(right_value) robject_release(right_value);
	return ret;
}

static int logic_or_execute(AstObject* ab)
{
	AstNodeLogicOr* node=AST_TO_LOGIC_OR(ab);
	Robject* left_value=0;
	Robject* right_value=0;
	int bool_flags=0;
	int ret=AST_EXE_SUCCESS;
	int exe_info;
	exe_info=ast_execute(node->b_left);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	left_value=get_reg0();
	bool_flags=robject_bool(left_value);
	if(vm_except_happened())
	{
		assert(bool_flags<0);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	if(bool_flags)
	{
		set_reg0(left_value);
		goto over;
	}
	exe_info=ast_execute(node->b_right);
	if(exe_info<0)
	{
		ret=exe_info;
		goto  error;
	}
	right_value=get_reg0();
	bool_flags=robject_bool(right_value);
	if(vm_except_happened())
	{
		assert(bool_flags<0);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	set_reg0(right_value);
over:
error:
	if(left_value) robject_release(left_value);
	if(right_value) robject_release(right_value);
	return ret;
}

static AstNodeType node_logic_or=
{
	.n_name="LogicOr",
	.n_type=ATN_LOGIC_OR,
	.n_free=binary_expr_free,
	.n_free_node=binary_expr_free_self,
#ifdef AST_MACHINE
	.n_execute=logic_or_execute,
#endif 
};
static AstNodeType node_logic_and=
{
	.n_name="LogicAnd",
	.n_type=ATN_LOGIC_AND,
	.n_free=binary_expr_free,
	.n_free_node=binary_expr_free_self,
#ifdef AST_MACHINE
	.n_execute=logic_and_execute,
#endif 
};

AstNodeLogicAnd* ast_create_logic_and(AstObject* l,AstObject* r)
{
	AstNodeLogicAnd* node=ast_node_new(AstNodeLogicAnd,&node_logic_and);
	if(node==NULL) return NULL;
	node->b_left=l;
	node->b_right=r;
	return node;
}
AstNodeLogicOr* ast_create_logic_or(AstObject* l,AstObject* r)
{

	AstNodeLogicOr* node=ast_node_new(AstNodeLogicOr,&node_logic_or);
	if(node==NULL) return NULL;
	node->b_left=l;
	node->b_right=r;
	return node;
}












