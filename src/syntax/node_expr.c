#include"node_expr.h"
#include<utility_c/marocs.h>
#define GR_UINT32_MAX 0xffffffff
#define AST_OPCODE_FLAG_CALL 0x1
static int literal_to_opcode(AstObject* ab,GrModule* md,GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_LITERAL);

	AstLiteral* node=AST_TO_LITERAL(ab);

	int ret=GrOpcode_NeedMore(op,5);
	if(ret<0)
	{
		return -1;
	}
	GrObject* val=node->l_value;
	assert(val);

	u_int32_t id=GrModule_MapConst(md,val);
	if(id==GR_UINT32_MAX)
	{
		return -1;
	}

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_LOAD_CONST,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_CONST2,id);
	}
	return 0;
}

AstTypeInfo Ast_Type_Literal=
{
	.t_type=ATN_LITERAL,
	.t_name="Literal",
	.t_to_opcode=literal_to_opcode,
};

AstObject* AstLiteral_New(GrObject* val)
{
	AstLiteral* node=AstNode_NewType(AstLiteral,&Ast_Type_Literal);
	if(node==NULL)
	{
		return NULL;
	}
	node->l_value=val;
	return LITERAL_TO_AST(node);
}

static int var_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstVar* node=AST_TO_VAR(ab);
	int ret;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrString* symbol=node->v_value;
	assert(symbol);
	u_int32_t id=GrModule_MapSymbol(m,S_TO_GR(symbol));
	if(id==GR_UINT32_MAX) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_LOAD_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_SYMBOL2,id);
	}
	return 0;
}
static int var_to_assign_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstVar* node=AST_TO_VAR(ab);
	int ret;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrString* symbol=node->v_value;
	assert(symbol);
	u_int32_t id=GrModule_MapSymbol(m,S_TO_GR(symbol));
	if(id==GR_UINT32_MAX) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_STORE_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_STORE_SYMBOL2,id);
	}
	return 0;
}


static int upper_var_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstVar* node=AST_TO_VAR(ab);
	int ret;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrString* symbol=node->v_value;
	assert(symbol);
	u_int32_t id=GrModule_MapSymbol(m,S_TO_GR(symbol));
	if(id==GR_UINT32_MAX) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_LOAD_U_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_U_SYMBOL2,id);
	}
	return 0;
}

static int upper_var_to_assign_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstVar* node=AST_TO_VAR(ab);
	int ret;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrString* symbol=node->v_value;
	assert(symbol);
	u_int32_t id=GrModule_MapSymbol(m,S_TO_GR(symbol));
	if(id==GR_UINT32_MAX) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_STORE_U_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_STORE_U_SYMBOL2,id);
	}
	return 0;
}
static int var_to_oper_and_assign_opcode(
		AstObject* ab,GrModule* m,GrOpcode* op,int  type,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstVar* node=AST_TO_VAR(ab);
	int ret;

	ret=GrOpcode_NeedMore(op,12);
	if(ret<0) return -1;

	GrString* symbol=node->v_value;
	assert(symbol);
	u_int32_t id=GrModule_MapSymbol(m,S_TO_GR(symbol));
	if(id==GR_UINT32_MAX) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_LOAD_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_SYMBOL2,id);
	}
	GrOpcode_Push(op,OP_DATA_SWAP0_1);

	switch(type)
	{
		case AST_ASSIGN_TYPE_MUL:
			GrOpcode_Push(op,OP_MUL);
			break;
		case AST_ASSIGN_TYPE_DIV:
			GrOpcode_Push(op,OP_DIV);
			break;
		case AST_ASSIGN_TYPE_MOD:
			GrOpcode_Push(op,OP_MOD);
			break;
		case AST_ASSIGN_TYPE_PLUS:
			GrOpcode_Push(op,OP_PLUS);
			break;
		case AST_ASSIGN_TYPE_MINUS:
			GrOpcode_Push(op,OP_MINUS);
			break;
		case AST_ASSIGN_TYPE_LSHIFT:
			GrOpcode_Push(op,OP_LSHIFT);
			break;
		case AST_ASSIGN_TYPE_RSHIFT:
			GrOpcode_Push(op,OP_RSHIFT);
			break;
		case AST_ASSIGN_TYPE_AND:
			GrOpcode_Push(op,OP_AND);
			break;
		case AST_ASSIGN_TYPE_XOR:
			GrOpcode_Push(op,OP_XOR);
			break;
		case AST_ASSIGN_TYPE_OR:
			GrOpcode_Push(op,OP_OR);
			break;
		default:
			BUG("Unkown Assgin Type");
			return -1;
	}


	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_STORE_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_STORE_SYMBOL2,id);
	}
	return 0;
}
static int upper_var_to_oper_and_assign_opcode(
		AstObject* ab,GrModule* m,GrOpcode* op,int  type,long flags)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_VAR);

	AstVar* node=AST_TO_VAR(ab);
	int ret;

	ret=GrOpcode_NeedMore(op,12);
	if(ret<0) return -1;

	GrString* symbol=node->v_value;
	assert(symbol);
	u_int32_t id=GrModule_MapSymbol(m,S_TO_GR(symbol));
	if(id==GR_UINT32_MAX) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_LOAD_U_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_U_SYMBOL2,id);
	}

	GrOpcode_Push(op,OP_DATA_SWAP0_1);
	switch(type)
	{
		case AST_ASSIGN_TYPE_MUL:
			GrOpcode_Push(op,OP_MUL);
			break;
		case AST_ASSIGN_TYPE_DIV:
			GrOpcode_Push(op,OP_DIV);
			break;
		case AST_ASSIGN_TYPE_MOD:
			GrOpcode_Push(op,OP_MOD);
			break;
		case AST_ASSIGN_TYPE_PLUS:
			GrOpcode_Push(op,OP_PLUS);
			break;
		case AST_ASSIGN_TYPE_MINUS:
			GrOpcode_Push(op,OP_MINUS);
			break;
		case AST_ASSIGN_TYPE_LSHIFT:
			GrOpcode_Push(op,OP_LSHIFT);
			break;
		case AST_ASSIGN_TYPE_RSHIFT:
			GrOpcode_Push(op,OP_RSHIFT);
			break;
		case AST_ASSIGN_TYPE_AND:
			GrOpcode_Push(op,OP_AND);
			break;
		case AST_ASSIGN_TYPE_XOR:
			GrOpcode_Push(op,OP_XOR);
			break;
		case AST_ASSIGN_TYPE_OR:
			GrOpcode_Push(op,OP_OR);
			break;
		default:
			BUG("Unkown Assgin Type");
			return -1;
	}


	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_STORE_U_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_STORE_U_SYMBOL2,id);
	}
	return 0;

}

AstTypeInfo Ast_Type_Var=
{
	.t_type=ATN_VAR,
	.t_name="Var",
	.t_to_opcode=var_to_opcode,
	.t_to_assign_opcode=var_to_assign_opcode,
	.t_to_oper_and_assign_opcode=var_to_oper_and_assign_opcode,
};
AstTypeInfo Ast_Type_Upper_Var=
{
	.t_type=ATN_VAR,
	.t_name="UpperVar",
	.t_to_opcode=upper_var_to_opcode,
	.t_to_assign_opcode=upper_var_to_assign_opcode,
	.t_to_oper_and_assign_opcode=upper_var_to_oper_and_assign_opcode,
};

AstObject* AstVar_New(GrString* val)
{
	AstVar* node=AstNode_NewType(AstVar,&Ast_Type_Var);
	if(node==NULL) 
	{
		return NULL;
	}
	node->v_value=val;
	return (AstObject*) node;
}
AstObject* AstUpperVar_New(GrString* val)
{
	AstVar* node=AstNode_NewType(AstVar,&Ast_Type_Upper_Var);
	if(node==NULL) 
	{
		return NULL;
	}
	node->v_value=val;
	return (AstObject*) node;
}



static int positive_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_POSITIVE);

	AstObject* sub_expr;
	int ret;

	AstNode_GetSub1(ab,&sub_expr);

	Ast_ToOpcode(sub_expr,m,op,0);

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_POSITIVE);
	return 0;
}

AstTypeInfo Ast_Type_Positive=
{
	.t_type=ATN_POSITIVE,
	.t_name="Positive",
	.t_to_opcode=positive_to_opcode,
};


static int negative_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_NEGATIVE);

	AstObject* sub_expr;
	int ret;

	AstNode_GetSub1(ab,&sub_expr);

	Ast_ToOpcode(sub_expr,m,op,0);

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_NEGATIVE);
	return 0;
}

AstTypeInfo Ast_Type_Negative=
{
	.t_type=ATN_NEGATIVE,
	.t_name="Negative",
	.t_to_opcode=negative_to_opcode,
};

static int negated_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_NEGATED);

	AstObject* sub_expr;
	int ret;

	AstNode_GetSub1(ab,&sub_expr);

	Ast_ToOpcode(sub_expr,m,op,flags);

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_NEGATED);
	return 0;
}
AstTypeInfo Ast_Type_Negated=
{
	.t_type=ATN_NEGATED,
	.t_name="Negated",
	.t_to_opcode=negated_to_opcode,
};


static int mul_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_MUL);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_MUL);
	return 0;
}

AstTypeInfo Ast_Type_Mul=
{
	.t_type=ATN_MUL,
	.t_name="Mul",
	.t_to_opcode=mul_to_opcode,
};

static int div_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_DIV);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_DIV);
	return 0;
}

AstTypeInfo Ast_Type_Div=
{
	.t_type=ATN_DIV,
	.t_name="Div",
	.t_to_opcode=div_to_opcode,
};

static int mod_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_MOD);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_MOD);
	return 0;
}

AstTypeInfo Ast_Type_Mod=
{
	.t_type=ATN_MOD,
	.t_name="Mod",
	.t_to_opcode=mod_to_opcode,
};



static int plus_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_PLUS);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_PLUS);
	return 0;
}

AstTypeInfo Ast_Type_Plus=
{
	.t_type=ATN_PLUS,
	.t_name="Plus",
	.t_to_opcode=plus_to_opcode,
};

static int minus_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_MINUS);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_MINUS);
	return 0;
}

AstTypeInfo Ast_Type_Minus=
{
	.t_type=ATN_MINUS,
	.t_name="Minus",
	.t_to_opcode=minus_to_opcode,
};



static int lshift_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LSHIFT);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_LSHIFT);
	return 0;
}

AstTypeInfo Ast_Type_LShift=
{
	.t_type=ATN_LSHIFT,
	.t_name="LShift",
	.t_to_opcode=lshift_to_opcode,
};


static int rshift_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_RSHIFT);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_RSHIFT);
	return 0;
}

AstTypeInfo Ast_Type_RShift=
{
	.t_type=ATN_RSHIFT,
	.t_name="RShift",
	.t_to_opcode=rshift_to_opcode,
};


static int and_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_AND);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_AND);
	return 0;
}

AstTypeInfo Ast_Type_And=
{
	.t_type=ATN_AND,
	.t_name="And",
	.t_to_opcode=and_to_opcode,
};

static int xor_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_XOR);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_XOR);
	return 0;
}

AstTypeInfo Ast_Type_Xor=
{
	.t_type=ATN_XOR,
	.t_name="Xor",
	.t_to_opcode=xor_to_opcode,
};



static int or_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_OR);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_OR);
	return 0;
}

AstTypeInfo Ast_Type_Or=
{
	.t_type=ATN_OR,
	.t_name="Or",
	.t_to_opcode=or_to_opcode,
};

static int lt_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LT);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_LT);
	return 0;
}

AstTypeInfo Ast_Type_Lt=
{
	.t_type=ATN_LT,
	.t_name="Lt",
	.t_to_opcode=lt_to_opcode,
};

static int le_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LE);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_LE);
	return 0;
}

AstTypeInfo Ast_Type_Le=
{
	.t_type=ATN_LE,
	.t_name="Le",
	.t_to_opcode=le_to_opcode,
};


static int ge_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_GE);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_GE);
	return 0;
}

AstTypeInfo Ast_Type_Ge=
{
	.t_type=ATN_GE,
	.t_name="Ge",
	.t_to_opcode=ge_to_opcode,
};


static int gt_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_GT);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_GT);
	return 0;
}

AstTypeInfo Ast_Type_Gt=
{
	.t_type=ATN_GT,
	.t_name="Gt",
	.t_to_opcode=gt_to_opcode,
};


static int eq_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_EQ);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_EQ);
	return 0;
}

AstTypeInfo Ast_Type_Eq=
{
	.t_type=ATN_EQ,
	.t_name="Eq",
	.t_to_opcode=eq_to_opcode,
};


static int ne_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_NE);

	AstObject* left;
	AstObject* right;
	int ret;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_NE);
	return 0;
}

AstTypeInfo Ast_Type_Ne=
{
	.t_type=ATN_NE,
	.t_name="Ne",
	.t_to_opcode=ne_to_opcode,
};


static int logic_not_to_opcode(AstObject* ab,GrModule* m,
								GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_LOGIC_NOT);

	AstObject* sub_expr=0;
	int ret;

	AstNode_GetSub1(ab,&sub_expr);

	ret=Ast_ToOpcode(sub_expr,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_LOGIC_NOT);
	return 0;
}

AstTypeInfo Ast_Type_Logic_Not=
{
	.t_type=ATN_LOGIC_NOT,
	.t_name="Not",
	.t_to_opcode=logic_not_to_opcode,
};

static int logic_and_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LOGIC_AND);

	AstObject* left;
	AstObject* right;

	int ret;
	int jump_instruct;
	int jump_pos;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_BOOL_NOTAKE);

	jump_instruct=GrOpcode_GetSize(op);
	GrOpcode_Push3(op,OP_JUMPR_FALSE_FORWARD,0);
	GrOpcode_Push(op,OP_DISCARD);

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	jump_pos=GrOpcode_GetSize(op);

	GrOpcode_SetCode3(op,jump_instruct,OP_JUMPR_FALSE_FORWARD,jump_pos-jump_instruct);

	return 0;
}

AstTypeInfo Ast_Type_Logic_And=
{
	.t_type=ATN_LOGIC_AND,
	.t_name="LogicAnd",
	.t_to_opcode=logic_and_to_opcode,
};

static int logic_or_to_opcode(AstObject* ab,GrModule* m,	
								GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_LOGIC_OR);

	AstObject* left;
	AstObject* right;
	int ret;
	int jump_instruct;
	int jump_pos;

	AstNode_GetSub2(ab,&left,&right);

	ret=Ast_ToOpcode(left,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_BOOL_NOTAKE);
	
	jump_instruct=GrOpcode_GetSize(op);
	GrOpcode_Push3(op,OP_JUMPR_TRUE_FORWARD,0);
	GrOpcode_Push(op,OP_DISCARD);

	ret=Ast_ToOpcode(right,m,op,0);
	if(ret<0) return -1;

	jump_pos=GrOpcode_GetSize(op);

	GrOpcode_SetCode3(op,jump_instruct,OP_JUMPR_TRUE_FORWARD,jump_pos-jump_instruct);
	return 0;
}

AstTypeInfo Ast_Type_Logic_Or=
{
	.t_type=ATN_LOGIC_OR,
	.t_name="LogicOr",
	.t_to_opcode=logic_or_to_opcode,
};


static int array_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_ARRAY);

	AstObject* expr_list;
	AstObject* expr;
	int ret;

	AstNode_GetSub1(ab,&expr_list);


	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_ARRAY_BEGIN);

	list_for_each_entry(expr,&expr_list->a_chirldren,a_sibling)
	{
		ret=Ast_ToOpcode(expr,m,op,flags);
		if(ret<0) return -1;

		ret=GrOpcode_NeedMore(op,1);
		if(ret<0) return -1;
		GrOpcode_Push(op,OP_ARRAY_PUSH);
	}

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_ARRAY_END);

	return 0;
}

AstTypeInfo Ast_Type_Array=
{
	.t_type=ATN_ARRAY,
	.t_name="Array",
	.t_to_opcode=array_to_opcode,
};
	

static int call_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_CALL);

	AstObject* expr;
	AstObject* arg_list;
	int ret;

	AstObject* arg;

	AstNode_GetSub2(ab,&expr,&arg_list);

	ret=Ast_ToOpcode(expr,m,op,AST_OPCODE_FLAG_CALL);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_ARRAY_BEGIN);

	list_for_each_entry(arg,&arg_list->a_chirldren,a_sibling)
	{
		ret=Ast_ToOpcode(arg,m,op,0);
		if(ret<0) return -1;

		ret=GrOpcode_NeedMore(op,1);
		if(ret<0) return -1;

		GrOpcode_Push(op,OP_ARRAY_PUSH);
	}
	ret=GrOpcode_NeedMore(op,2);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_ARRAY_END);
	GrOpcode_Push(op,OP_CALL);
	return 0;
}

AstTypeInfo Ast_Type_Call=
{
	.t_type=ATN_CALL,
	.t_name="Call",
	.t_to_opcode=call_to_opcode,
};


static int square_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_SQUARE);

	AstObject* expr;
	AstObject* index;

	int ret;

	AstNode_GetSub2(ab,&expr,&index);

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(index,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_GET_ITEM);
	return 0;
}

static int square_to_assign_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_SQUARE);

	AstObject* expr;
	AstObject* index;

	int ret;

	AstNode_GetSub2(ab,&expr,&index);

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(index,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_SET_ITEM);
	return 0;
}

static int square_to_oper_and_assign_opcode(
		AstObject* ab,GrModule* m,GrOpcode* op,int type,long flags)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_SQUARE);

	AstObject* expr;
	AstObject* index;

	int ret;

	AstNode_GetSub2(ab,&expr,&index);

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(index,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,7);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_DUP_DATA3);
	GrOpcode_Push(op,OP_GET_ITEM);
	GrOpcode_Push(op,OP_DATA_SWAP0_1);

	switch(type)
	{
		case AST_ASSIGN_TYPE_MUL:
			GrOpcode_Push(op,OP_MUL);
			break;
		case AST_ASSIGN_TYPE_DIV:
			GrOpcode_Push(op,OP_DIV);
			break;
		case AST_ASSIGN_TYPE_MOD:
			GrOpcode_Push(op,OP_MOD);
			break;
		case AST_ASSIGN_TYPE_PLUS:
			GrOpcode_Push(op,OP_PLUS);
			break;
		case AST_ASSIGN_TYPE_MINUS:
			GrOpcode_Push(op,OP_MINUS);
			break;
		case AST_ASSIGN_TYPE_LSHIFT:
			GrOpcode_Push(op,OP_LSHIFT);
			break;
		case AST_ASSIGN_TYPE_RSHIFT:
			GrOpcode_Push(op,OP_RSHIFT);
			break;
		case AST_ASSIGN_TYPE_AND:
			GrOpcode_Push(op,OP_AND);
			break;
		case AST_ASSIGN_TYPE_XOR:
			GrOpcode_Push(op,OP_XOR);
			break;
		case AST_ASSIGN_TYPE_OR:
			GrOpcode_Push(op,OP_OR);
			break;
		default:
			BUG("Unkown Assgin Type");
			return -1;
	}
	GrOpcode_Push(op,OP_DATA_SWAP0_3);
	GrOpcode_Push(op,OP_DISCARD);
	GrOpcode_Push(op,OP_SET_ITEM);
	return 0;
}




AstTypeInfo Ast_Type_Square=
{
	.t_type=ATN_SQUARE,
	.t_name="GetItem",
	.t_to_opcode=square_to_opcode,
	.t_to_assign_opcode=square_to_assign_opcode,
	.t_to_oper_and_assign_opcode=square_to_oper_and_assign_opcode,
};



static int period_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_PERIOD);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* expr;
	AstObject* identifer;

	int ret;

	AstNode_GetSub2(ab,&expr,&identifer);


	GrString* attr_name=AST_TO_VAR(identifer)->v_value;

	assert(attr_name);

	u_int32_t id=GrModule_MapSymbol(m,(GrObject*)attr_name);
	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,7);
	if(ret<0) return -1;


	if(flags&AST_OPCODE_FLAG_CALL)
	{
		GrOpcode_Push(op,OP_DUP_DATA1);
		GrOpcode_Push(op,OP_SET_HOST);
	}

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_GET_ATTR,id);
	}
	else 
	{
		GrOpcode_Push5(op,OP_GET_ATTR2,id);
	}
	return 0;
}

static int  period_to_assign_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_PERIOD);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* expr;
	AstObject* identifer;

	int ret;

	AstNode_GetSub2(ab,&expr,&identifer);


	GrString* attr_name=AST_TO_VAR(identifer)->v_value;

	assert(attr_name);


	u_int32_t id=GrModule_MapSymbol(m,(GrObject*)attr_name);
	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=Ast_ToOpcode(expr,m,op,5);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,5);

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_SET_ATTR,id);
	}
	else 
	{
		GrOpcode_Push5(op,OP_SET_ATTR2,id);
	}

	return 0;
}


static int  period_to_oper_and_assign_code(AstObject* ab,
		GrModule* m,GrOpcode* op,int type,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_PERIOD);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* expr;
	AstObject* identifer;

	int ret;

	AstNode_GetSub2(ab,&expr,&identifer);


	GrString* attr_name=AST_TO_VAR(identifer)->v_value;

	assert(attr_name);


	u_int32_t id=GrModule_MapSymbol(m,(GrObject*)attr_name);
	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=Ast_ToOpcode(expr,m,op,5);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,14);
	if(ret<0) return -1;


	GrOpcode_Push(op,OP_DUP_DATA2);

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_GET_ATTR,id);
	}
	else 
	{
		GrOpcode_Push5(op,OP_GET_ATTR2,id);
	}

	switch(type)
	{
		case AST_ASSIGN_TYPE_MUL:
			GrOpcode_Push(op,OP_MUL);
			break;
		case AST_ASSIGN_TYPE_DIV:
			GrOpcode_Push(op,OP_DIV);
			break;
		case AST_ASSIGN_TYPE_MOD:
			GrOpcode_Push(op,OP_MOD);
			break;
		case AST_ASSIGN_TYPE_PLUS:
			GrOpcode_Push(op,OP_PLUS);
			break;
		case AST_ASSIGN_TYPE_MINUS:
			GrOpcode_Push(op,OP_MINUS);
			break;
		case AST_ASSIGN_TYPE_LSHIFT:
			GrOpcode_Push(op,OP_LSHIFT);
			break;
		case AST_ASSIGN_TYPE_RSHIFT:
			GrOpcode_Push(op,OP_RSHIFT);
			break;
		case AST_ASSIGN_TYPE_AND:
			GrOpcode_Push(op,OP_AND);
			break;
		case AST_ASSIGN_TYPE_XOR:
			GrOpcode_Push(op,OP_XOR);
			break;
		case AST_ASSIGN_TYPE_OR:
			GrOpcode_Push(op,OP_OR);
			break;
		default:
			BUG("Unkown Assgin Type");
			return -1;
	}

	GrOpcode_Push(op,OP_DATA_SWAP0_2);
	GrOpcode_Push(op,OP_DISCARD);

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_SET_ATTR,id);
	}
	else 
	{
		GrOpcode_Push5(op,OP_SET_ATTR2,id);
	}
	return 0;
}


AstTypeInfo Ast_Type_Period=
{
	.t_type=ATN_PERIOD,
	.t_name="Period",
	.t_to_opcode=period_to_opcode,
	.t_to_assign_opcode=period_to_assign_opcode,
	.t_to_oper_and_assign_opcode=period_to_oper_and_assign_code,
};
	

/*
static int new_to_opcode(AstObject* ab,GrModule* m,
				GrOpcode* op,long flags)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_NEW);

	AstObject* sub_expr;
	int ret;

	AstNode_GetSub1(ab,&sub_expr);

	Ast_ToOpcode(sub_expr,m,op,0);

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_NEW);
	return 0;
}

AstTypeInfo Ast_Type_New=
{
	.t_type=ATN_NEW,
	.t_name="New",
	.t_to_opcode=new_to_opcode,
};




*/



























