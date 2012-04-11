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

static int expr_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_EXPR);
	
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
	op_code_push(op,OP_DISCARD);
	return 0;
}
static int while_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_WHILE);

	AstObject* expr;
	AstObject* stmts;
	ast_node_getsub2(ab,&expr,&stmts);
	int ret;
	ssize_t while_begin=0;
	ssize_t while_jump=0;
	ssize_t while_end=0;

	while_begin=op_code_size(op);

	/* expr opcode */
	ret=ast_to_opcode(expr,m,op);
	if(ret<0)
	{
		return ret;
	}

	/* condition judge opcode */
	ret=op_code_enlarge_more(op,4);
	if(ret<0)
	{
		return ret;
	}
	op_code_push(op,OP_BOOL);

	/* update pos later*/
	while_jump=op_code_size(op);
	op_code_push3(op,OP_JUMPR_FALSE,0);

	/* stmts opcode */
	ret=ast_to_opcode(stmts,m,op);
	if(ret<0)
	{
		return ret;
	}

	/* jump to begin */
	ret=op_code_enlarge_more(op,3);
	if(ret<0)
	{
		return ret;
	}
	while_end=op_code_size(op);
	op_code_push3(op,OP_JUMPR,-(while_end-while_begin));

	/* update condition judge */
	op_code_set3(op,while_jump,OP_JUMPR_FALSE,while_end-while_jump+3);

	return 0;
}

static int assign_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_ASSIGN);
	AstObject* left;
	AstObject* expr;
	ast_node_getsub2(ab,&left,&expr);
	int ret=0;

	ret=ast_to_opcode(expr,m,op);
	if(ret<0)
	{
		return ret;
	}

	ret=ast_to_assign_opcode(left,m,op);
	if(ret<0)
	{
		return ret;
	}
	return 0;
}



static int if_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_IF);

	struct list_head* head=&ab->a_chirldren;
	AstObject* sub_node=0;
	int ret=0;
	
	ssize_t if_begin=op_code_size(op);
	ssize_t if_end=0;
	ssize_t i;

	u_int8_t* codes;

	list_for_each_entry(sub_node,head,a_sibling)
	{
		ret=ast_to_opcode(sub_node,m,op);
		if(ret<0)
		{
			return ret;
		}
	}

	if_end=op_code_size(op);

	//printf("begin=%d,end=%d\n",if_begin,if_end);

	codes=op->o_codes; /* NOTE codes maybe replace when enlarge */
	for(i=if_begin;i<if_end;i++)
	{
		if(codes[i]==OP_BREAK)
		{
			op_code_set3(op,i,OP_JUMPR,if_end-i);
		}
		if(codes[i]>=OP_NEED_PARAM2)
		{
			i+=2;
			continue;
		}
		if(codes[i]>=OP_NEED_PARAM4)
		{
			i+=4;
			continue;
		}
	}
	return 0;
}

static int if_elif_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,2);
	CHECK_NODE_TYPE(ab,ATN_IF_ELIF);

	AstObject* expr;
	AstObject* stmts;
	int ret;
	ssize_t condit_pos;
	ssize_t end_pos;

	ast_node_getsub2(ab,&expr,&stmts);

	ret=ast_to_opcode(expr,m,op);
	if(ret<0)
	{
		return ret;
	}

	ret=op_code_enlarge_more(op,4);
	if(ret<0)
	{
		return ret;
	}

	op_code_push(op,OP_BOOL);
	condit_pos=op_code_size(op);

	op_code_push3(op,OP_JUMPR_FALSE,0);

	ret=ast_to_opcode(stmts,m,op);
	if(ret<0)
	{
		
		return ret;
	}
	ret=op_code_enlarge_more(op,3);
	if(ret<0)
	{
		return ret;
	}
	/* use OP_BREAK for temp,it will replace by OP_JUMPR later */
	op_code_push3(op,OP_BREAK,0);


	end_pos=op_code_size(op);
	op_code_set3(op,condit_pos,OP_JUMPR_FALSE,end_pos-condit_pos);

	return ret;
}
static int else_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,1);
	CHECK_NODE_TYPE(ab,ATN_ELSE);
	AstObject* stmts;
	int ret;

	ast_node_getsub1(ab,&stmts);

	ret=ast_to_opcode(stmts,m,op);
	return ret;
}





		
AstNodeType node_block=
{
	.t_type=ATN_STMTS,
	.t_name="Block",
	.t_to_opcode=stmts_to_opcode,
};

AstNodeType node_print=
{
	.t_type=ATN_PRINT,
	.t_name="Print",
	.t_to_opcode=print_to_opcode,
};
AstNodeType node_expr=
{
	.t_type=ATN_EXPR,
	.t_name="Expr",
	.t_to_opcode=expr_to_opcode,
};
AstNodeType node_while=
{
	.t_type=ATN_WHILE,
	.t_name="While",
	.t_to_opcode=while_to_opcode,
};
AstNodeType node_assign=
{
	.t_type=ATN_ASSIGN,
	.t_name="Assign",
	.t_to_opcode=assign_to_opcode,
};

AstNodeType node_if=
{
	.t_type=ATN_IF,
	.t_name="If",
	.t_to_opcode=if_to_opcode,
};
AstNodeType node_if_elif=
{
	.t_type=ATN_IF_ELIF,
	.t_name="If_Elif",
	.t_to_opcode=if_elif_to_opcode,
};
AstNodeType node_else=
{
	.t_type=ATN_ELSE,
	.t_name="Else",
	.t_to_opcode=else_to_opcode,
};

	







