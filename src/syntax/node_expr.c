#include"node_expr.h"
#define GR_UINT32_MAX 0xffffffff

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


