#include "node_expr.h"
#include<rstd/redy_std.h>
#include"ast_object.h"


static int literal_to_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_LITERAL);
	AstNodeLiteral* node=AST_TO_LITERAL(ab);
	int ret=op_code_enlarge_more(op,5);
	if(ret<0)
	{
		return ret;
	}

	Robject* value=node->l_value;
	u_int32_t id=module_map_const(md,value);
	if(id<0)
	{
		return -1;
	}
	if(id>((u_int32_t)0x1<<16))
	{
		op_code_push5(op,OP_LOAD_CONST2,id);
	}
	else
	{
		op_code_push3(op,OP_LOAD_CONST,id);
	}
	return 0;
}

static void literal_destruct(AstObject* ab)
{
	AstNodeLiteral* node=AST_TO_LITERAL(ab);
	robject_release(node->l_value);
}
static AstNodeType node_literal=
{
	.t_type=ATN_LITERAL,
	.t_name="Literal",
	.t_destruct=literal_destruct,
	.t_to_opcode=literal_to_opcode,

};

AstObject* ast_create_literal(Robject* value)
{
	AstNodeLiteral* node=ast_node_new_type(AstNodeLiteral,&node_literal);
	if(node==NULL)
	{
		return NULL;
	}
	node->l_value=value;
	return LITERAL_TO_AST(node);
}
static  int var_to_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstNodeVar* node=AST_TO_VAR(ab);

	int ret=op_code_enlarge_more(op,5);
	if(ret<0)
	{
		return ret;
	}

	Robject* symbol=S_TO_R(node->v_symbol);
	int32_t id=module_map_symbol(md,symbol);
	if(id<0)
	{
		return -1;
	}
	/*FIXME When id >(0x1<<16) OP_LOAD_SYMBOL can't work correct*/

	op_code_push3(op,OP_LOAD_SYMBOL,(u_int16_t)id);
	return 0;
}
static int var_to_assign_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstNodeVar* node=AST_TO_VAR(ab);
	int ret=op_code_enlarge_more(op,5);
	if(ret<0)
	{
		return ret;
	}
	Robject* symbol=S_TO_R(node->v_symbol);
	int32_t id=module_map_symbol(md,symbol);
	if(id<0)
	{
		return -1;
	}
	/*FIXME When id >(0x1<<16) OP_LOAD_SYMBOL can't work correct*/
	op_code_push3(op,OP_STORE_SYMBOL,(u_int16_t)id);
	return 0;
}


static void var_destruct(AstObject* ab)
{
	AstNodeVar* node=AST_TO_VAR(ab);
	robject_release(S_TO_R(node->v_symbol));
}

static AstNodeType node_var=
{
	.t_type=ATN_VAR,
	.t_name="Var",
	.t_destruct=var_destruct,
	.t_to_opcode=var_to_opcode,
	.t_to_assign_opcode=var_to_assign_opcode,
};


	


AstObject* ast_create_var(BtString* symbol)
{
	AstNodeVar* node=ast_node_new_type(AstNodeVar,&node_var);
	if(node==NULL)
	{
		return NULL;
	}
	node->v_symbol=symbol;
	return (AstObject*)node;
}


static int array_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_ARRAY);

	AstObject* expr_list;
	int ret;
	AstObject* expr;

	ast_node_getsub1(ab,&expr_list);

	ret=op_code_enlarge_more(op,1);
	if(ret<0) return ret;
	op_code_push(op,OP_ARRAY_BEGIN);

	list_for_each_entry(expr,&expr_list->a_chirldren,a_sibling)
	{
		ret=ast_to_opcode(expr,m,op);
		if(ret<0)  return ret; 
		ret=op_code_enlarge_more(op,1);
		if(ret<0) return ret;
		op_code_push(op,OP_ARRAY_PUSH);
	}
	ret=op_code_enlarge_more(op,1);
	if(ret<0) return ret;
	op_code_push(op,OP_ARRAY_END);
	return 0;
}

AstNodeType node_array=
{
	.t_name="Array",
	.t_type=ATN_ARRAY,
	.t_to_opcode=array_to_opcode,
};

static int square_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_SQUARE);
	AstObject* expr;
	AstObject* index;
	int ret;

	ast_node_getsub2(ab,&expr,&index);

	ret=ast_to_opcode(expr,m,op);
	if(ret<0) return ret;

	ret=ast_to_opcode(index,m,op);
	if(ret<0) return ret;

	ret=op_code_enlarge_more(op,1);
	if(ret<0) return ret;

	op_code_push(op,OP_GET_ITEM);

	return 0;
}

static int square_to_assign_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_SQUARE);
	AstObject* expr;
	AstObject* index;
	int ret;

	ast_node_getsub2(ab,&expr,&index);

	ret=ast_to_opcode(expr,m,op);
	if(ret<0) return ret;

	ret=ast_to_opcode(index,m,op);
	if(ret<0) return ret;

	ret=op_code_enlarge_more(op,1);
	if(ret<0) return ret;

	op_code_push(op,OP_SET_ITEM);

	return 0;
}

AstNodeType node_square=
{
	.t_name="Square",
	.t_type=ATN_SQUARE,
	.t_to_opcode=square_to_opcode,
	.t_to_assign_opcode=square_to_assign_opcode,
};


	









static int binary_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op,unsigned char code)
{
	CHECK_SUB_NODE_NUM(ab,2);
	AstObject* left;
	AstObject* right;
	ast_node_getsub2(ab,&left,&right);
	int ret;
	ret=ast_to_opcode(left,m,op);
	if(ret<0)
	{
		return ret;
	}
	ret=ast_to_opcode(right,m,op);
	if(ret<0)
	{
		return ret;
	}
	ret=op_code_enlarge_more(op,1);
	if(ret<0)
	{
		return ret;
	}
	op_code_push(op,code);
	return 0;
}
static int unary_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op,unsigned char code)
{
	CHECK_SUB_NODE_NUM(ab,1);
	AstObject* sub_node;
	ast_node_getsub1(ab,&sub_node);
	int ret;
	ret=ast_to_opcode(sub_node,m,op);
	if(ret<0)
	{
		return ret;
	}
	ret=op_code_enlarge_more(op,1);
	if(ret<0)
	{
		return ret;
	}
	op_code_push(op,code);
	return 0;
}

/* unary expr */
static int positive_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_POSITIVE);
	return unary_to_opcode(ab,m,op,OP_POSITIVE);
}
static int negative_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_NEGATIVE);
	return unary_to_opcode(ab,m,op,OP_NEGATIVE);
}

/* multiply_expr */
static int mul_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_MUL);
	return binary_to_opcode(ab,m,op,OP_MUL);
}
static int div_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_DIV);
	return binary_to_opcode(ab,m,op,OP_DIV);
}
static int mod_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_MOD);
	return binary_to_opcode(ab,m,op,OP_MOD);
}

/* additive expr */
static int plus_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_PLUS);
	return binary_to_opcode(ab,m,op,OP_PLUS);
}
static int minus_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_MINUS);
	return binary_to_opcode(ab,m,op,OP_MINUS);
}

/* shift expr */
static int lshift_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_LSHIFT);
	return binary_to_opcode(ab,m,op,OP_LSHIFT);
}
static int rshift_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_RSHIFT);
	return binary_to_opcode(ab,m,op,OP_RSHIFT);
}

/* bitwise expr */
static int and_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_AND);
	return binary_to_opcode(ab,m,op,OP_AND);
}
static int xor_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_XOR);
	return binary_to_opcode(ab,m,op,OP_XOR);
}
static int or_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_OR);
	return binary_to_opcode(ab,m,op,OP_OR);
}
static int negated_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_NEGATED);
	return unary_to_opcode(ab,m,op,OP_NEGATED);
}

/* compare expr */
static int lt_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_LT);
	return binary_to_opcode(ab,m,op,OP_LT);
}
static int le_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_LE);
	return binary_to_opcode(ab,m,op,OP_LE);
}
static int gt_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_GT);
	return binary_to_opcode(ab,m,op,OP_GT);
}
static int ge_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_GE);
	return binary_to_opcode(ab,m,op,OP_GE);
}
static int eq_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_EQ);
	return binary_to_opcode(ab,m,op,OP_EQ);
}
static int ne_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_NE);
	return binary_to_opcode(ab,m,op,OP_NE);
}

/* logic expr */
static int logic_not_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_LOGIC_NOT);
	AstObject* sub_node=0;
	ast_node_getsub1(ab,&sub_node);
	int ret;
	ret=ast_to_opcode(sub_node,m,op);
	if(ret<0)
	{
		return ret;
	}
	
	ret=op_code_enlarge_more(op,1);
	if(ret<0)
	{
		return ret;
	}
	op_code_push(op,OP_LOGIC_NOT);
	return 0;
}

static int logic_and_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LOGIC_AND);
	AstObject* left;
	AstObject* right;
	ast_node_getsub2(ab,&left,&right);
	int ret;
	int jump_instruct;
	int jump_pos;
	ret=ast_to_opcode(left,m,op);
	if(ret<0)
	{
		return ret;
	}
	ret=op_code_enlarge_more(op,5);
	if(ret<0)
	{
		return ret;
	}
	
	op_code_push(op,OP_BOOL_NOTAKE);

	/* update jump_pos later */
	jump_instruct=op_code_size(op);
	op_code_push3(op,OP_JUMP_FALSE,0);
	op_code_push(op,OP_DISCARD);

	ret=ast_to_opcode(right,m,op);
	if(ret<0)
	{
		return ret;
	}
	jump_pos=op_code_size(op);

	op_code_set3(op,jump_instruct,OP_JUMP_FALSE,jump_pos);

	return 0;
}
static int logic_or_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LOGIC_OR);
	AstObject* left;
	AstObject* right;
	ast_node_getsub2(ab,&left,&right);
	int ret;
	int jump_instruct;
	int jump_pos;
	ret=ast_to_opcode(left,m,op);
	if(ret<0)
	{
		return ret;
	}
	ret=op_code_enlarge_more(op,5);
	if(ret<0)
	{
		return ret;
	}

	op_code_push(op,OP_BOOL_NOTAKE);

	/* update jump pos later */
	jump_instruct=op_code_size(op);
	op_code_push3(op,OP_JUMP_TRUE,0);
	op_code_push(op,OP_DISCARD);

	ret=ast_to_opcode(right,m,op);
	if(ret<0)
	{
		return ret;
	}
	jump_pos=op_code_size(op);
	op_code_set3(op,jump_instruct,OP_JUMP_TRUE,jump_pos);
	return 0;
}








/* unary expr */
AstNodeType node_positive=
{
	.t_name="Positive",
	.t_type=ATN_POSITIVE,
	.t_to_opcode=positive_to_opcode,
};

AstNodeType node_negative=
{
	.t_name="Negative",
	.t_type=ATN_NEGATIVE,
	.t_to_opcode=negative_to_opcode,
};


/* multiply_expr */
AstNodeType node_mul=
{
	.t_name="Mul",
	.t_type=ATN_MUL,
	.t_to_opcode=mul_to_opcode,
};
AstNodeType node_div=
{
	.t_name="Div",
	.t_type=ATN_DIV,
	.t_to_opcode=div_to_opcode,
};
AstNodeType node_mod=
{
	.t_name="Mod",
	.t_type=ATN_MOD,
	.t_to_opcode=mod_to_opcode,
};


/* additive expr */
AstNodeType node_plus=
{
	.t_name="Plus",
	.t_type=ATN_PLUS,
	.t_to_opcode=plus_to_opcode,
};
AstNodeType node_minus=
{
	.t_name="Minus",
	.t_type=ATN_MINUS,
	.t_to_opcode=minus_to_opcode,
};

/* shift expr*/
AstNodeType node_lshift=
{
	.t_name="LShift",
	.t_type=ATN_LSHIFT,
	.t_to_opcode=lshift_to_opcode,
};
AstNodeType node_rshift=
{
	.t_name="RShift",
	.t_type=ATN_RSHIFT,
	.t_to_opcode=rshift_to_opcode,
};

/* bitwise expr */
AstNodeType node_and=
{
	.t_name="And",
	.t_type=ATN_AND,
	.t_to_opcode=and_to_opcode,
};
AstNodeType node_or=
{
	.t_name="Or",
	.t_type=ATN_OR,
	.t_to_opcode=or_to_opcode,
};
AstNodeType node_xor=
{
	.t_name="Xor",
	.t_type=ATN_XOR,
	.t_to_opcode=xor_to_opcode,
};
AstNodeType node_negated=
{
	.t_name="Negated",
	.t_type=ATN_NEGATED,
	.t_to_opcode=negated_to_opcode,
};

/* compare expr */
AstNodeType node_lt=
{
	.t_name="Lt",
	.t_type=ATN_LT,
	.t_to_opcode=lt_to_opcode,
};
AstNodeType node_le=
{
	.t_name="Le",
	.t_type=ATN_LE,
	.t_to_opcode=le_to_opcode,
};
AstNodeType node_ge=
{
	.t_name="Ge",
	.t_type=ATN_GE,
	.t_to_opcode=ge_to_opcode,
};
AstNodeType node_gt=
{
	.t_name="Gt",
	.t_type=ATN_GT,
	.t_to_opcode=gt_to_opcode,
};
AstNodeType node_eq=
{
	.t_name="Eq",
	.t_type=ATN_EQ,
	.t_to_opcode=eq_to_opcode,
};
AstNodeType node_ne=
{
	.t_name="Ne",
	.t_type=ATN_NE,
	.t_to_opcode=ne_to_opcode,
};

/* logic expr */
AstNodeType node_logic_not=
{
	.t_name="LogicNot",
	.t_type=ATN_LOGIC_NOT,
	.t_to_opcode=logic_not_to_opcode,
};
AstNodeType node_logic_or=
{
	.t_name="LogicOr",
	.t_type=ATN_LOGIC_OR,
	.t_to_opcode=logic_or_to_opcode,
};
AstNodeType node_logic_and=
{
	.t_name="LogicAnd",
	.t_type=ATN_LOGIC_AND,
	.t_to_opcode=logic_and_to_opcode,
};




