#include"node_stmt.h"
#include<memory/gc.h>
#include"node_expr.h"

static int print_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_PRINT);
	CHECK_SUB_NODE_NUM(ab,1);

	AstObject* expr_list;
	AstObject* expr;
	int ret;


	AstNode_GetSub1(ab,&expr_list);


	list_for_each_entry(expr,&expr_list->a_chirldren,a_sibling)
	{
		ret=Ast_ToOpcode(expr,m,op,0);
		if(ret<0) return -1;

		ret=GrOpcode_NeedMore(op,1);
		if(ret<0) return -1;

		GrOpcode_Push(op,OP_PRINT);
	}
	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_PRINT_LN);
	return 0;
}

AstTypeInfo Ast_Type_Print=
{
	.t_type=ATN_PRINT,
	.t_name="Print",
	.t_to_opcode=print_to_opcode,
};


static int stmts_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_STMTS);
	AstObject* stmt;
	int ret;

	list_for_each_entry(stmt,&ab->a_chirldren,a_sibling)
	{
		ret=Ast_ToOpcode(stmt,m,op,0);
		if(ret<0) return -1;
	}
	return 0;
}

AstTypeInfo Ast_Type_Stmts=
{
	.t_type=ATN_STMTS,
	.t_name="Stmts",
	.t_to_opcode=stmts_to_opcode,
};

static int expr_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_EXPR);
	CHECK_SUB_NODE_NUM(ab,1);

	AstObject* expr;
	int ret;

	AstNode_GetSub1(ab,&expr);

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,1);
	if(ret<0) return -1;
	GrOpcode_Push(op,OP_DISCARD);
	return 0;
}

AstTypeInfo Ast_Type_Expr=
{
	.t_type=ATN_EXPR,
	.t_name="Expr",
	.t_to_opcode=expr_to_opcode,
};

static int break_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_BREAK);
	CHECK_SUB_NODE_NUM(ab,0);

	int ret=GrOpcode_NeedMore(op,3);
	if(ret<0) return -1;
	GrOpcode_Push3(op,OP_BREAK,0);
	return 0;
}

AstTypeInfo  Ast_Type_Break=
{
	.t_type=ATN_BREAK,
	.t_name="Break",
	.t_to_opcode=break_to_opcode,
};

static int continue_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_CONTINUE);
	CHECK_SUB_NODE_NUM(ab,0);

	int ret=GrOpcode_NeedMore(op,3);
	if(ret<0) return -1;
	GrOpcode_Push3(op,OP_CONTINUE,0);
	return 0;
}

AstTypeInfo Ast_Type_Continue=
{
	.t_type=ATN_CONTINUE,
	.t_name="Continue",
	.t_to_opcode=continue_to_opcode,
};

static int assign_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToAssignOpcode(target,m,op,0);
	if(ret<0) return -1;

	return 0;
}

AstTypeInfo Ast_Type_Assign=
{
	.t_type=ATN_ASSIGN,
	.t_name="Assign",
	.t_to_opcode= assign_to_opcode,
};

static int mul_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_MUL_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_MUL,0);
	if(ret<0) return -1;

	return 0;
}



static int div_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_DIV_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_DIV,0);
	if(ret<0) return -1;

	return 0;
}

static int mod_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_MOD_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_MOD,0);
	if(ret<0) return -1;

	return 0;
}


static int plus_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_PLUS_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_PLUS,0);
	if(ret<0) return -1;

	return 0;
}

static int minus_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_MINUS_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_MINUS,0);
	if(ret<0) return -1;

	return 0;
}
static int lshift_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_LSHIFT_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_LSHIFT,0);
	if(ret<0) return -1;

	return 0;
}
static int rshift_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_RSHIFT_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_RSHIFT,0);
	if(ret<0) return -1;

	return 0;
}



static int and_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_AND_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_AND,0);
	if(ret<0) return -1;

	return 0;
}

static int xor_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_XOR_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_XOR,0);
	if(ret<0) return -1;

	return 0;
}
static int or_assign_to_opcode(AstObject* ab,GrModule* m,
					GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_OR_ASSIGN);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* target;
	AstObject* value;
	int ret;

	AstNode_GetSub2(ab,&target,&value);

	ret=Ast_ToOpcode(value,m,op,0);
	if(ret<0) return -1;

	ret=Ast_ToOperAssignOpcode(target,m,op,AST_ASSIGN_TYPE_OR,0);
	if(ret<0) return -1;

	return 0;
}

AstTypeInfo Ast_Type_Mul_Assign=
{
	.t_type=ATN_MUL_ASSIGN,
	.t_name="MulAssign",
	.t_to_opcode=mul_assign_to_opcode,
};

AstTypeInfo Ast_Type_Div_Assign=
{	
	.t_type=ATN_DIV_ASSIGN,
	.t_name="DivAssign",
	.t_to_opcode=div_assign_to_opcode,
};
AstTypeInfo Ast_Type_Mod_Assign=
{
	.t_type=ATN_MOD_ASSIGN,
	.t_name="ModAssign",
	.t_to_opcode=mod_assign_to_opcode,
};
AstTypeInfo Ast_Type_Plus_Assign=
{
	.t_type=ATN_PLUS_ASSIGN,
	.t_name="PlusAssign",
	.t_to_opcode=plus_assign_to_opcode,
};
AstTypeInfo Ast_Type_Minus_Assign=
{
	.t_type=ATN_MINUS_ASSIGN,
	.t_name="MinusAssign",
	.t_to_opcode=minus_assign_to_opcode,
};
AstTypeInfo Ast_Type_LShift_Assign=
{
	.t_type=ATN_LSHIFT_ASSIGN,
	.t_name="LShiftAssign",
	.t_to_opcode=lshift_assign_to_opcode,
};
AstTypeInfo Ast_Type_RShift_Assign=
{
	.t_type=ATN_RSHIFT_ASSIGN,
	.t_name="RShiftAssign",
	.t_to_opcode=rshift_assign_to_opcode,
};
AstTypeInfo Ast_Type_And_Assign=
{
	.t_type=ATN_AND_ASSIGN,
	.t_name="AndAssign",
	.t_to_opcode=and_assign_to_opcode,
};
AstTypeInfo Ast_Type_Xor_Assign=
{
	.t_type=ATN_XOR_ASSIGN,
	.t_name="XorAssign",
	.t_to_opcode=xor_assign_to_opcode,
};
AstTypeInfo Ast_Type_Or_Assign=
{
	.t_type=ATN_OR_ASSIGN,
	.t_name="OrAssign",
	.t_to_opcode=or_assign_to_opcode,
};

static int while_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_WHILE);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* expr;
	AstObject* block;

	int begin_pos;
	int cond_pos;
	int end_pos;
	int ret;

	AstNode_GetSub2(ab,&expr,&block);

	begin_pos=GrOpcode_GetSize(op);

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,4);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_BOOL);
	
	cond_pos=GrOpcode_GetSize(op);
	GrOpcode_Push3(op,OP_JUMPR_FALSE_FORWARD,0);

	ret=Ast_ToOpcode(block,m,op,0);
	if(ret<0) return -1;
	
	end_pos=GrOpcode_GetSize(op);

	ret=GrOpcode_NeedMore(op,3);
	if(ret<0) return -1;

	GrOpcode_Push3(op,OP_JUMPR_BACK,end_pos-begin_pos);

	end_pos+=3;
	

	GrOpcode_SetCode3(op,cond_pos,OP_JUMPR_FALSE_FORWARD,end_pos-cond_pos);

	int i;
	u_int8_t* codes=op->o_codes;
	u_int8_t cur;
	i=cond_pos;
	while(i<end_pos)
	{
		cur=codes[i];
		if(cur==OP_BREAK)
		{
			GrOpcode_SetCode3(op,i,OP_JUMPR_FORWARD,end_pos-i);
		}
		if(cur==OP_CONTINUE)
		{
			GrOpcode_SetCode3(op,i,OP_JUMPR_BACK,i-begin_pos);
		}

		if(cur>=OP_NEED_PARAM4)
		{
			i+=4;
		}
		else if(cur>=OP_NEED_PARAM2)
		{
			i+=2;
		}
		i++;
	}

	return 0;
}


AstTypeInfo Ast_Type_While=
{
	.t_type=ATN_WHILE,
	.t_name="While",
	.t_to_opcode=while_to_opcode,
};


static int for_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_FOR);
	CHECK_SUB_NODE_NUM(ab,3);

	AstObject* symbol;
	AstObject* expr;
	AstObject* block;

	int ret;
	int for_begin;
	int for_end;
	int jump_pos;

	AstNode_GetSub3(ab,&symbol,&expr,&block);

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_ITER);

	for_begin=GrOpcode_GetSize(op);
	GrOpcode_Push(op,OP_ITER_NEXT);

	jump_pos=GrOpcode_GetSize(op);
	GrOpcode_Push3(op,OP_JUMPR_FORWARD,0);

	ret=Ast_ToAssignOpcode(symbol,m,op,0);
	if(ret<0) return -1;
	ret=Ast_ToOpcode(block,m,op,0);
	if(ret<0) return -1;

	for_end=GrOpcode_GetSize(op);

	ret=GrOpcode_NeedMore(op,4);
	GrOpcode_Push3(op,OP_JUMPR_BACK,for_end-for_begin);
	GrOpcode_Push(op,OP_DISCARD);

	for_end+=3;

	GrOpcode_SetCode3(op,jump_pos,OP_JUMPR_FORWARD,for_end-jump_pos);
	
	int i=for_begin;
	u_int8_t* codes=op->o_codes;
	u_int8_t cur;
	while(i<for_end)
	{
		cur=codes[i];
		if(cur==OP_BREAK)
		{
			GrOpcode_SetCode3(op,i,OP_JUMPR_FORWARD,for_end-i);
		}
		if(cur==OP_CONTINUE)
		{
			GrOpcode_SetCode3(op,i,OP_JUMPR_BACK,i-for_begin);
		}
		if(cur>=OP_NEED_PARAM4)
		{
			i+=4;
		}
		else if(cur>=OP_NEED_PARAM2)
		{
			i+=2;
		}
		i++;
	}
	return 0;
}

AstTypeInfo Ast_Type_For=
{
	.t_name="For",
	.t_type=ATN_FOR,
	.t_to_opcode=for_to_opcode,
};



static int if_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_IF);

	AstObject* sub_node;
	int ret;
	int if_begin;
	int if_end;


	if_begin=GrOpcode_GetSize(op);

	list_for_each_entry(sub_node,&ab->a_chirldren,a_sibling)
	{
		ret=Ast_ToOpcode(sub_node,m,op,flags);
		if(ret<0) return -1;
	}


	if_end=GrOpcode_GetSize(op);

	u_int8_t* codes=op->o_codes;
	u_int8_t cur;
	int i=if_begin;
	while(i<if_end)
	{

		cur=codes[i];
		if(cur==OP_TEMP_IF3)
		{
			GrOpcode_SetCode3(op,i,OP_JUMPR_FORWARD,if_end-i);
		}
		if(i>=OP_NEED_PARAM4)
		{
			i+=4;
		}
		else if(i>=OP_NEED_PARAM2)
		{
			i+=2;
		}
		i++;
	}
	return 0;
}
AstTypeInfo Ast_Type_If=
{
	.t_type=ATN_IF,
	.t_name="If",
	.t_to_opcode=if_to_opcode,
};

static int if_elif_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_IF_ELIF);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* expr;
	AstObject* block;
	int ret;

	int cond_pos;
	int end_pos;

	AstNode_GetSub2(ab,&expr,&block);

	ret=Ast_ToOpcode(expr,m,op,flags);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,4);
	if(ret<0) return -1;
	GrOpcode_Push(op,OP_BOOL);

	cond_pos=GrOpcode_GetSize(op);
	GrOpcode_Push3(op,OP_JUMPR_FALSE_FORWARD,0);

	ret=Ast_ToOpcode(block,m,op,flags);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(op,3);
	GrOpcode_Push3(op,OP_TEMP_IF3,0);

	end_pos=GrOpcode_GetSize(op);

	GrOpcode_SetCode3(op,cond_pos,OP_JUMPR_FALSE_FORWARD,end_pos-cond_pos);
	return 0;
}
AstTypeInfo Ast_Type_If_Elif=
{
	.t_type=ATN_IF_ELIF,
	.t_name="If_Elif",
	.t_to_opcode=if_elif_to_opcode,
};

static  int else_to_opcode(AstObject* ab,GrModule* m,
							GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_ELSE);
	CHECK_SUB_NODE_NUM(ab,1);

	AstObject* block;
	int ret;
	AstNode_GetSub1(ab,&block);
	ret=Ast_ToOpcode(block,m,op,flags);
	if(ret<0) return -1;

	return 0;
}

AstTypeInfo Ast_Type_Else=
{
	.t_type=ATN_ELSE,
	.t_name="Else",
	.t_to_opcode=else_to_opcode,
};

static int func_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op,long f)
{
	CHECK_NODE_TYPE(ab,ATN_FUNC);
	CHECK_SUB_NODE_NUM(ab,3);
	AstObject* func_name;
	AstObject* arg_list;
	AstObject* block;

	AstObject* arg;

	AstNode_GetSub3(ab,&func_name,&arg_list,&block);

	GrOpcode* func_codes=GrOpcode_GcNewFlag(GRGC_HEAP_STATIC);
	if(func_codes==NULL) return -1;

	u_int32_t codes_id=GrModule_MapOpcode(m,func_codes);
	if(codes_id==GR_MODULE_MAP_ERR) return -1;
	assert(GrOpcode_OpdataSize16(codes_id));

	int ret;
	ret=GrOpcode_NeedMore(op,4);
	GrOpcode_Push(op,OP_FUNC_BEGIN);
	GrOpcode_Push3(op,OP_FUNC_OPCODE,codes_id);
	GrOpcode_Push(op,OP_ARRAY_BEGIN);

	
	GrArray* arg_names=GrArray_GcNewFlag(GRGC_HEAP_STATIC);
	int arg_min_nu=0;
	int arg_nu=0;
	long flags=0;

	list_for_each_entry(arg,&arg_list->a_chirldren,a_sibling)
	{
		CHECK_NODE_TYPE(arg,ATN_ARG);
		AstArg* cur=AST_TO_ARG(arg);
		AstObject* expr;
		GrString* name;

		name=cur->a_name;
		ret=GrArray_Push(arg_names,S_TO_GR(name));
		if(ret<0) return -1;

		if(cur->a_type==ARG_SIMPLY)
		{
			CHECK_SUB_NODE_NUM(arg,0);
			arg_min_nu++;
			arg_nu++;
		}
		if(cur->a_type==ARG_DEFAULT_VALUE)
		{
			flags|=GR_OPCODE_FLAGS_DEFAULT_ARG;
			arg_nu++;

			CHECK_SUB_NODE_NUM(arg,1);
			AstNode_GetSub1(arg,&expr);
			ret=Ast_ToOpcode(expr,m,op,0);
			if(ret<0) return -1;

			ret=GrOpcode_NeedMore(op,1);
			if(ret<0) return -1;
			GrOpcode_Push(op,OP_PUSH);
		}
		if(cur->a_type==ARG_MANY)
		{
			flags|=GR_OPCODE_FLAG_MANY_ARG;
		}
	}
	ret=GrOpcode_NeedMore(op,8);
	if(ret<0) return -1;
	GrOpcode_Push(op,OP_ARRAY_END);
	GrOpcode_Push(op,OP_FUNC_DEFALUT_ARGS);
	GrOpcode_Push(op,OP_DUP_DATA1);

	u_int32_t func_id=GrModule_MapSymbol(m,
					S_TO_GR(AST_TO_VAR(func_name)->v_value));
	if(func_id==GR_MODULE_MAP_ERR) return -1;
	if(GrOpcode_OpdataSize16(func_id))
	{
		GrOpcode_Push3(op,OP_STORE_SYMBOL,func_id);
	}
	else
	{
		GrOpcode_Push5(op,OP_STORE_SYMBOL2,func_id);
	}



	GrOpcode_SetName(func_codes,AST_TO_VAR(func_name)->v_value);
	GrOpcode_SetArgNu(func_codes,arg_nu);
	GrOpcode_SetArgMin(func_codes,arg_min_nu);
	GrOpcode_SetFlags(func_codes,flags);
	GrOpcode_SetArgName(func_codes,arg_names);
	GrOpcode_SetModule(func_codes,m);


	ret=Ast_ToOpcode(block,m,func_codes,0);
	if(ret<0) return -1;

	ret=GrOpcode_NeedMore(func_codes,1);
	if(ret<0) return -1;
	GrOpcode_Push(func_codes,OP_RETURN_NIL);

	return 0;
}

AstTypeInfo Ast_Type_Func=
{
	.t_name="Func",
	.t_type=ATN_FUNC,
	.t_to_opcode=func_to_opcode,
};

AstTypeInfo Ast_Type_Arg=
{
	.t_name="Arg",
	.t_type=ATN_ARG,
};
			

AstObject* AstArg_New(int type,GrString* name)
{
	AstArg* node=AstNode_NewType(AstArg,&Ast_Type_Arg);
	if(node==NULL)
	{
		return NULL;
	}
	node->a_name=name;
	node->a_type=type;
	return (AstObject*)node;
}

		























	

















