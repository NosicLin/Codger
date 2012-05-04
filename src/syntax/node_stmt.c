#include"node_stmt.h"

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




