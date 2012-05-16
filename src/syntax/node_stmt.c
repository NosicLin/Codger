#include"node_stmt.h"
#include<memory/gc.h>
#include"node_expr.h"
#include<object/gr_class.h>

static int import_to_opcode(AstObject* ab ,GrModule* m,
					GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_IMPORT);
	CHECK_SUB_NODE_NUM(ab,1);
	int ret;

	AstObject* identifier;
	AstNode_GetSub1(ab,&identifier);

	GrString* name=AST_TO_VAR(identifier)->v_value;
	assert(name);
	u_int32_t id=GrModule_MapSymbol(m,(GrObject*)name);
	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=GrOpcode_NeedMore(op,10);
	if(ret<0) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_IMPORT,id);
		GrOpcode_Push3(op,OP_STORE_SYMBOL,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_IMPORT2,id);
		GrOpcode_Push5(op,OP_STORE_SYMBOL2,id);
	}
	return 0;
}

AstTypeInfo Ast_Type_Import=
{
	.t_type=ATN_IMPORT,
	.t_name="Import",
	.t_to_opcode=import_to_opcode,
};

static int export_to_opcode(AstObject* ab,GrModule* m,
		GrOpcode* op,long  flags)
{
	CHECK_NODE_TYPE(ab,ATN_EXPORT);
	CHECK_SUB_NODE_NUM(ab,1);
	int ret;

	AstObject* identifier;
	AstNode_GetSub1(ab,&identifier);

	GrString* name=AST_TO_VAR(identifier)->v_value;
	assert(name);
	u_int32_t id=GrModule_MapSymbol(m,(GrObject*)name);
	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=GrOpcode_NeedMore(op,10);
	if(ret<0) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_LOAD_SYMBOL,id);
		GrOpcode_Push3(op,OP_EXPORT,id);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_SYMBOL,id);
		GrOpcode_Push5(op,OP_EXPORT,id);
	}
	return 0;
}
static int export_as_to_opcode(AstObject* ab,GrModule* m,
		GrOpcode* op,long  flags)
{
	CHECK_NODE_TYPE(ab,ATN_EXPORT_AS);
	CHECK_SUB_NODE_NUM(ab,2);
	int ret;

	AstObject* value_name;
	AstObject* export_name;
	AstNode_GetSub2(ab,&value_name,&export_name);

	GrString* s_value=AST_TO_VAR(value_name)->v_value;
	assert(s_value);

	GrString* s_export=AST_TO_VAR(export_name)->v_value;
	assert(s_export);


	u_int32_t id_value=GrModule_MapSymbol(m,(GrObject*)s_value);
	if(id_value==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	u_int32_t id_export=GrModule_MapSymbol(m,(GrObject*)s_export);
	if(id_export==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=GrOpcode_NeedMore(op,10);
	if(ret<0) return -1;

	if(GrOpcode_OpdataSize16(id_value))
	{
		GrOpcode_Push3(op,OP_LOAD_SYMBOL,id_value);
	}
	else
	{
		GrOpcode_Push5(op,OP_LOAD_SYMBOL,id_value);
	}
	if(GrOpcode_OpdataSize16(id_export))
	{
		GrOpcode_Push3(op,OP_EXPORT,id_export);
	}
	else
	{
		GrOpcode_Push5(op,OP_EXPORT2,id_export);
	}
	return 0;

}

AstTypeInfo Ast_Type_Export =
{
	.t_type=ATN_EXPORT,
	.t_name="Export",
	.t_to_opcode=export_to_opcode,
};
AstTypeInfo Ast_Type_Export_As=
{
	.t_type=ATN_EXPORT_AS,
	.t_name="Export As",
	.t_to_opcode=export_as_to_opcode,
};
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
			flags|=GR_OPCODE_FLAG_DEFAULT_ARG;
			arg_nu++;

			CHECK_SUB_NODE_NUM(arg,1);
			AstNode_GetSub1(arg,&expr);
			ret=Ast_ToOpcode(expr,m,op,0);
			if(ret<0) return -1;

			ret=GrOpcode_NeedMore(op,1);
			if(ret<0) return -1;
			GrOpcode_Push(op,OP_ARRAY_PUSH);
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


static int return_to_opcode(AstObject* ab,GrModule* m,
						GrOpcode* op, long flags)
{

	CHECK_NODE_TYPE(ab,ATN_RETURN);

	AstObject* expr;
	int ret;

	if(ab->a_chirldren.next!=&ab->a_chirldren)
	{
		CHECK_SUB_NODE_NUM(ab,1);
		AstNode_GetSub1(ab,&expr);
		ret=Ast_ToOpcode(expr,m,op,flags);
		if(ret<0) return -1;
		
		ret=GrOpcode_NeedMore(op,1);
		if(ret<0) return -1;

		GrOpcode_Push(op,OP_RETURN);
	}
	else 
	{
		CHECK_SUB_NODE_NUM(ab,0);
		ret=GrOpcode_NeedMore(op,1);
		if(ret<0) return -1;
		GrOpcode_Push(op,OP_RETURN_NIL);
	}
	return 0;
}

AstTypeInfo Ast_Type_Return=
{
	.t_type=ATN_RETURN,
	.t_name="Return",
	.t_to_opcode=return_to_opcode,
};
		

static int class_to_opcode(AstObject* ab,GrModule* m,
			GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_CLASS);
	CHECK_SUB_NODE_NUM(ab,2);

	AstClass* a_c=AST_TO_CLASS(ab);
	AstObject* inhert=a_c->c_inherit;

	AstObject* name;
	AstObject* block;

	int ret;

	AstNode_GetSub2(ab,&name,&block);


	u_int32_t id=GrModule_MapSymbol(m,
				(GrObject*)((AST_TO_VAR(name)->v_value)));

	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=GrOpcode_NeedMore(op,11);
	if(ret<0) return -1;

	if(GrOpcode_OpdataSize16(id))
	{
		GrOpcode_Push3(op,OP_CLASS_BEGIN,id);
	}
	else 
	{
		GrOpcode_Push5(op,OP_CLASS_BEGIN2,id);
	}

	if(inhert!=NULL)
	{
		u_int32_t inhert_id=GrModule_MapSymbol(m,
				(GrObject*)(AST_TO_VAR(inhert)->v_value));
		if(inhert_id==GR_MODULE_MAP_ERR)
		{
			return -1;
		}
		if(GrOpcode_OpdataSize16(inhert_id))
		{
			GrOpcode_Push3(op,OP_LOAD_SYMBOL,inhert_id);
		}
		else
		{
			GrOpcode_Push5(op,OP_LOAD_SYMBOL,inhert_id);
		}
		GrOpcode_Push(op,OP_CLASS_INHERIT);
	}

	ret=Ast_ToOpcode(block,m,op,0);
	if(ret<0) return -1;
	
	ret=GrOpcode_NeedMore(op,5);
	if(ret<0) return -1;

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

AstTypeInfo Ast_Type_Class=
{
	.t_name="Class",
	.t_type=ATN_CLASS,
	.t_to_opcode=class_to_opcode,
};

AstObject* AstClass_New(AstObject* inhert)
{
	AstClass* node=AstNode_NewType(AstClass,&Ast_Type_Class);
	if(node==NULL) return NULL;

	node->c_inherit=inhert;

	return (AstObject*)node;
}


static int attr_to_opcode(AstObject* ab,GrModule* m,
			GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_ATTR);
	CHECK_SUB_NODE_NUM(ab,1);

	AstObject* name;
	AstNode_GetSub1(ab,&name);

	int ret;

	u_int32_t id=GrModule_MapAttr(m, AST_TO_VAR(name)->v_value,
							flags&GR_CLASS_PERM_MASK);

	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=GrOpcode_NeedMore(op,6);
	if(ret<0) return -1;

	GrOpcode_Push(op,OP_LOAD_NIL);

	if(flags&GR_CLASS_STATIC)
	{
		if(GrOpcode_OpdataSize16(id))
		{
			GrOpcode_Push3(op,OP_CLASS_ATTR,id);
		}
		else
		{
			GrOpcode_Push5(op,OP_CLASS_ATTR2,id);
		}
	}
	else 
	{
		if(GrOpcode_OpdataSize16(id))
		{
			GrOpcode_Push3(op,OP_CLASS_TEMPLATE,id);
		}
		else
		{
			GrOpcode_Push5(op,OP_CLASS_TEMPLATE2,id);
		}
	}
	return 0;
}

AstTypeInfo Ast_Type_Attr=
{
	.t_name="Attr",
	.t_type=ATN_ATTR,
	.t_to_opcode=attr_to_opcode,
};


static int attr_default_to_opcode(AstObject* ab,GrModule* m,
				GrOpcode* op,long flags)
{

	CHECK_NODE_TYPE(ab,ATN_ATTR_DEFAULT);
	CHECK_SUB_NODE_NUM(ab,2);

	AstObject* name;
	AstObject* expr;
	AstNode_GetSub2(ab,&name,&expr);

	int ret;

	u_int32_t id=GrModule_MapAttr(m,
							AST_TO_VAR(name)->v_value,
							flags&GR_CLASS_PERM_MASK);


	if(id==GR_MODULE_MAP_ERR)
	{
		return -1;
	}

	ret=GrOpcode_NeedMore(op,6);
	if(ret<0) return -1;

	ret=Ast_ToOpcode(expr,m,op,0);
	if(ret<0) return ret;


	if(flags&GR_CLASS_STATIC)
	{
		if(GrOpcode_OpdataSize16(id))
		{
			GrOpcode_Push3(op,OP_CLASS_ATTR,id);
		}
		else
		{
			GrOpcode_Push5(op,OP_CLASS_ATTR2,id);
		}
	}
	else 
	{
		if(GrOpcode_OpdataSize16(id))
		{
			GrOpcode_Push3(op,OP_CLASS_TEMPLATE,id);
		}
		else
		{
			GrOpcode_Push5(op,OP_CLASS_TEMPLATE2,id);
		}
	}
	return 0;
}


AstTypeInfo Ast_Type_Attr_Default=
{
	.t_type=ATN_ATTR_DEFAULT,
	.t_name="AttrDefault",
	.t_to_opcode=attr_default_to_opcode,
};


static int method_to_opcode(AstObject* ab,GrModule* m,
				GrOpcode* op,long f)
{
	CHECK_NODE_TYPE(ab,ATN_METHOD);
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
			flags|=GR_OPCODE_FLAG_DEFAULT_ARG;
			arg_nu++;

			CHECK_SUB_NODE_NUM(arg,1);
			AstNode_GetSub1(arg,&expr);
			ret=Ast_ToOpcode(expr,m,op,0);
			if(ret<0) return -1;

			ret=GrOpcode_NeedMore(op,1);
			if(ret<0) return -1;
			GrOpcode_Push(op,OP_ARRAY_PUSH);
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

	u_int32_t func_id=GrModule_MapAttr(m,
					AST_TO_VAR(func_name)->v_value,
			 		 f&GR_CLASS_PERM_MASK);

	if(func_id==GR_MODULE_MAP_ERR) return -1;

	if(f&GR_CLASS_STATIC)
	{
		if(GrOpcode_OpdataSize16(func_id))
		{
			GrOpcode_Push3(op,OP_CLASS_ATTR,func_id);
		}
		else
		{
			GrOpcode_Push5(op,OP_CLASS_ATTR2,func_id);
		}
	}
	else 
	{
		if(GrOpcode_OpdataSize16(func_id))
		{
			GrOpcode_Push3(op,OP_CLASS_TEMPLATE,func_id);
		}
		else
		{
			GrOpcode_Push5(op,OP_CLASS_TEMPLATE2,func_id);
		}
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

AstTypeInfo Ast_Type_Method=
{
	.t_type=ATN_METHOD,
	.t_name="Method",
	.t_to_opcode=method_to_opcode,
};



static int class_stmt_to_opcode(AstObject* ab, GrModule* m,
					GrOpcode* op,long flags)
{
	CHECK_NODE_TYPE(ab,ATN_CLASS_STMT);
	CHECK_SUB_NODE_NUM(ab,1);

	AstObject* stmt;
	int ret;

	AstNode_GetSub1(ab,&stmt);

	AstClassStmt* c_stmt=AST_TO_CLASS_STMT(ab);


	ret=Ast_ToOpcode(stmt,m,op,c_stmt->c_flags);
	if(ret<0) return -1;
	return 0;
}

AstTypeInfo Ast_Type_Class_Stmt=
{
	.t_type=ATN_CLASS_STMT,
	.t_name="ClassStmt",
	.t_to_opcode=class_stmt_to_opcode,
};

AstObject* AstClassStmt_New()
{
	AstClassStmt* node=AstNode_NewType(AstClassStmt,&Ast_Type_Class_Stmt);
	if(node==NULL) return NULL;

	node->c_flags=0;

	return (AstObject*)node;
}

void AstClassStmt_SetFlag(AstClassStmt* s ,long f)
{
	s->c_flags=f;
}








	

