#include"node_stmts.h"
#include"vm/except.h"
#include<rstd/redy_std.h>
#include<utility_c/marocs.h>




static int stmts_to_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	
	struct list_head* chirldren=&ab->a_chirldren;
	AstObject* p;

	int ret=0;
	list_for_each_entry(p,chirldren,a_sibling)
	{
		ret=ast_to_opcode(p,md,op);
		if(ret<0)
		{
			return 0;
		}
	}
	return 0;
}

static int print_to_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_PRINT);

	struct list_head* l_args=(&ab->a_chirldren)->next;

	AstObject* args=list_entry(l_args,AstObject,a_sibling);

	//printf("%s\n",ast_name(args));

	AstObject* p=0;
	int ret=0;

	list_for_each_entry(p,&args->a_chirldren,a_sibling)
	{
		ret=ast_to_opcode(p,md,op);
		if(ret<0)
		{
			return -1;
		}
		ret=op_code_enlarge_more(op,1);
		if(ret<0)
		{
			return -1;
		}
		op_code_push(op,OP_PRINT);
	}
	ret=op_code_enlarge_more(op,1);
	if(ret<0)
	{
		return -1;
	}
	op_code_push(op,OP_PRINT_LN);
	return 0;
}



AstNodeType node_stmts=
{
	.t_type=ATN_STMTS,
	.t_name="Stmts",
	.t_to_opcode=stmts_to_opcode,
};

AstNodeType node_print=
{
	.t_type=ATN_PRINT,
	.t_name="Print",
	.t_to_opcode=print_to_opcode,
};

	







