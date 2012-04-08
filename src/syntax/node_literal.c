#include "node_literal.h"
#include<rstd/redy_std.h>
#ifdef AST_MACHINE 
#include "ast_machine.h"
#endif /* AST_MACHINE */
#include"ast_object.h"

static int literal_to_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	AstNodeLiteral* node=AST_TO_LITERAL(ab);
	int ret=op_code_enlarge_more(op,5);
	if(ret<0)
	{
		return ret;
	}
	unsigned long id=node->l_id;
	if(id>(0x1<<16))
	{
		op_code_push5(op,OP_CONST2,id);
	}
	else
	{
		op_code_push3(op,OP_CONST,id);
	}
	return 0;
}

static AstNodeType node_literal=
{
	.n_type=ATN_LITERAL,
	.n_name="Literal",
	.n_to_opcode=literal_to_opcode,
};

AstNodeLiteral* ast_create_literal(id)
{
	AstNodeLiteral* node=ast_node_new(AstNodeLiteral,&node_literal);
	if(node==NULL)
	{
		return NULL;
	}
	node->l_id=id;
	return node;
}









