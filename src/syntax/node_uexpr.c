#include"node_uexpr.h"
#include<vm/except.h>
#include<rtype/bt_bool.h>
#ifdef AST_MACHINE 
#include"ast_machine.h"
#endif /*AST_MACHINE*/
#include"object/robject.h"
static void unary_expr_free(AstObject* ab)
{
	AstNodeUExpr* uexpr=(AstNodeUExpr*)ab;
	ast_free(uexpr->u_value);
	ry_free(uexpr);
}
static void unary_expr_free_self(AstObject* ab)
{
	AstNodeUExpr* uexpr=(AstNodeUExpr*)ab;
	ry_free(uexpr);
}

typedef Robject* (*unary_func)(Robject*);
#ifdef AST_MACHINE

static int unary_execute(AstNodeUExpr* unode,unary_func ufunc)
{
	Robject* sub_value=0;
	Robject* ret_value=0;
	int ret=AST_EXE_SUCCESS;
	int exe_info=0;
	exe_info=ast_execute(unode->u_value);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	sub_value=get_reg0();
	ret_value=ufunc(sub_value);
	robject_release(sub_value);
	if(vm_except_happened())
	{
		assert(ret_value==NULL);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	assert(ret_value!=NULL);
	set_reg0(ret_value);
	robject_release(ret_value);
error:
	return ret;
}

static int positive_execute(AstObject* ab)
{
	unary_func func=robject_positive;
	AstNodePositive*  node=AST_TO_POSITIVE(ab);
	int ret=unary_execute((AstNodeUExpr*)node,func);
	return ret;
}
static int negative_execute(AstObject* ab)
{
	unary_func func=robject_negative;
	AstNodeNegative* node=AST_TO_NEGATIVE(ab); 
	int ret=unary_execute((AstNodeUExpr*)node,func);
	return ret;
}
static int negated_execute(AstObject* ab)
{
	unary_func func=robject_negated;
	AstNodeNegative* node=AST_TO_NEGATED(ab); 
	int ret=unary_execute((AstNodeUExpr*)node,func);
	return ret;
}
#endif 
static AstNodeType node_positive=
{
	.n_type=ATN_POSITIVE,
	.n_name="Positive",
	.n_free=unary_expr_free,
	.n_free_node=unary_expr_free_self,
#ifdef AST_MACHINE
	.n_execute=positive_execute,
#endif 
};	
static AstNodeType node_negative=
{
	.n_type=ATN_NEGATIVE,
	.n_name="Negative",
	.n_free=unary_expr_free,
	.n_free_node=unary_expr_free_self,
#ifdef AST_MACHINE
	.n_execute=negative_execute,
#endif
};
static AstNodeType node_negated=
{
	.n_type=ATN_NEGATED,
	.n_name="Negated",
	.n_free=unary_expr_free,
	.n_free_node=unary_expr_free_self,
#ifdef AST_MACHINE
	.n_execute=negated_execute,
#endif
};

AstNodePositive* ast_create_positive(AstObject* sub_node)
{
	AstNodePositive* node=ast_node_new(AstNodePositive,&node_positive);
	if(node==NULL) return NULL;
	node->u_value=sub_node;
	return node;
}

AstNodeNegative* ast_create_negative(AstObject* sub_node)
{
	AstNodeNegative* node=ast_node_new(AstNodeNegative,&node_negative);
	if(node==NULL) return NULL;
	node->u_value=sub_node;
	return node;
}
AstNodeNegative* ast_create_negated(AstObject* sub_node)
{
	AstNodeNegated* node=ast_node_new(AstNodeNegated,&node_negated);
	if(node==NULL) return NULL;
	node->u_value=sub_node;
	return node;
}



#ifdef AST_MACHINE
static int logic_not_execute(AstObject* ao)
{
	AstNodeLogicNot* node=AST_TO_LOGIC_NOT(ao);
	Robject* sub_value=0;
	Robject* ret_value=0;
	int bool_flags=0;
	int exe_info;
	int ret=AST_EXE_SUCCESS;
	exe_info=ast_execute(node->u_value);
	if(exe_info<0)
	{
		ret=exe_info;
		goto error;
	}
	sub_value=get_reg0();
	bool_flags=robject_bool(sub_value);
	robject_release(sub_value);


	if(vm_except_happened())
	{
		assert(bool_flags<0);
		ret=AST_EXE_EXCEPTION;
		goto error;
	}
	assert(bool_flags>=0);
	ret_value=B_TO_R(btbool_create(!bool_flags));
	set_reg0(ret_value);
	robject_release(ret_value);
error:
	return ret;
}
#endif  /*AST_MACHINE*/

static AstNodeType node_logic_not=
{
	.n_name="LogicNot",
	.n_type=ATN_LOGIC_NOT,
	.n_free=unary_expr_free,
	.n_free_node=unary_expr_free_self,
#ifdef AST_MACHINE
	.n_execute=logic_not_execute,
#endif 
};


AstNodeLogicNot* ast_create_logic_not(AstObject* sub_node)
{
	AstNodeLogicNot* node=ast_node_new(AstNodeLogicNot,&node_logic_not);
	if(node==NULL) return NULL;
	node->u_value=sub_node;
	return node; 
}

