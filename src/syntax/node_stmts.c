#include"node_stmts.h"
#include"vm/except.h"
#include<rstd/redy_std.h>
#include<utility_c/marocs.h>
#include<object/func_object.h>
#include"node_expr.h"




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
		if(codes[i]==OP_TEMP_IF3)
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
	/* use OP_USER1_3 for temp,it will replace by OP_JUMPR later */
	op_code_push3(op,OP_TEMP_IF3,0);


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


static int for_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,3);
	CHECK_NODE_TYPE(ab,ATN_FOR);

	AstObject* symbol;
	AstObject* expr;
	AstObject* stmts;
	int ret;
	ssize_t for_begin;
	ssize_t for_end;
	u_int8_t* codes;
	ssize_t i;


	ast_node_getsub3(ab,&symbol,&expr,&stmts);

	/* expr to opcode */
	ret=ast_to_opcode(expr,m,op);
	if(ret<0) return ret;

	ret=op_code_enlarge_more(op,5);
	if(ret<0) return ret;

	op_code_push(op,OP_ITER);
	for_begin=op_code_size(op);

	/* @begin */
	op_code_push(op,OP_ITER_NEXT);

	/* update jump pos later @end*/
	op_code_push3(op,OP_JUMPR,0);

	/* symbols to opcode */
	ret=ast_to_assign_opcode(symbol,m,op);
	if(ret<0) return ret;

	/* stmts to opcode */
	ret=ast_to_opcode(stmts,m,op);
	if(ret<0) return ret;

	/* jump to @begin */
	ret=op_code_enlarge_more(op,4);
	for_end=op_code_size(op);
	op_code_push3(op,OP_JUMPR,for_begin-for_end);

	/* @end */
	for_end=op_code_size(op);
	op_code_push(op,OP_DISCARD);

	/* update pre jump  @end */
	op_code_set3(op,for_begin+1,OP_JUMPR,for_end-(for_begin+1));

	/* update continue and break */

	codes=op->o_codes;
	for(i=for_begin;i<for_end;i++)
	{
		if(codes[i]==OP_BREAK)
		{
			op_code_set3(op,i,OP_JUMPR,for_end-i);
		}
		if(codes[i]==OP_CONTINUE)
		{
			op_code_set3(op,i,OP_JUMPR,for_begin-i);
		}
		if(codes[i]>=OP_NEED_PARAM2)
		{
			i+=2;
		}
	}
	return 0;
}


static int  break_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_BREAK);
	int ret;
	ret=op_code_enlarge_more(op,3);
	if(ret<0) return ret;

	/* pos will update later by for or while stmt*/
	op_code_push3(op,OP_BREAK,0);
	return 0;
}
static int continue_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,0);
	CHECK_NODE_TYPE(ab,ATN_CONTINUE);
	int ret;
	ret=op_code_enlarge_more(op,3);
	if(ret<0) return ret;
	
	op_code_push3(op,OP_CONTINUE,0);
	return 0;
}

static int arg_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_NODE_TYPE(ab,ATN_ARG);
	int ret;
	int arg_type;
	AstNodeArg* arg=AST_TO_ARG(ab);
	arg_type=arg->a_type;
	AstObject* expr;

	if(arg_type==ARG_SIMPLY||arg_type==ARG_MANY)
	{
		CHECK_SUB_NODE_NUM(ab,0);
		return 0;
	}
	else if(arg_type==ARG_DEFALUT_VALUE)
	{
		CHECK_SUB_NODE_NUM(ab,1);
		ast_node_getsub1(ab,&expr);
		ret=ast_to_opcode(expr,m,op);
		if(ret<0) return ret;
		ret=op_code_enlarge_more(op,1);
		if(ret<0) return ret;
		op_code_push(op,OP_ARRAY_PUSH);
	}
	else
	{
		BUG("Unkown Arg Type");
		return -1;
	}
	return 0;
}

static int func_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op)
{
	CHECK_SUB_NODE_NUM(ab,3);
	CHECK_NODE_TYPE(ab,ATN_FUNC);
	int ret;
	int arg_type;
	unsigned long flags=0;
	AstObject* name;
	AstObject* arg_list;
	AstObject* stmts;
	BtString* func_name;
	AstObject* _arg;
	AstNodeArg* arg;
	int arg_nu=0;
	int arg_min=0;
	ssize_t name_id;
	ssize_t func_id;



	FuncObject* func=0;
	BtArray* args_name=0;
	OpCode* func_opcode=0;
	

	ast_node_getsub3(ab,&name,&arg_list,&stmts);
	func_name=AST_TO_VAR(name)->v_symbol;

	func=func_new();
	args_name=btarray_create();
	func_opcode=op_code_new();
	if(func==NULL||args_name==NULL||func_opcode==NULL)
	{
		goto error;
	}
	/* map id */
	func_id=module_map_const(m,FUNC_TO_R(func));
	name_id=module_map_symbol(m,S_TO_R(func_name));
	if(func_id<0||name_id<0)
	{
		goto error;
	}

	/* set func name */ 
	func_set_name(func,func_name);

	/* Generate func Body Codes */
	ret=ast_to_opcode(stmts,m,func_opcode);
	if(ret<0) goto error;
	func_set_opcode(func,func_opcode);
	func_opcode=NULL;


	/* func begin */
	ret=op_code_enlarge_more(op,6);
	if(ret<0) goto error;
	if(op_code_is_udata2(func_id))
	{
		op_code_push3(op,OP_LOAD_CONST,func_id);
	}
	else
	{
		op_code_push5(op,OP_LOAD_CONST2,func_id);
	}
	op_code_push(op,OP_ARRAY_BEGIN);


	/* traverse arg_list */
	list_for_each_entry(_arg,&arg_list->a_chirldren,a_sibling)
	{
		arg=AST_TO_ARG(_arg);
		arg_type=arg->a_type;
		if(arg_type==ARG_SIMPLY)
		{
			arg_nu++;
			arg_min++;

		}
		else if(arg_type==ARG_DEFALUT_VALUE)
		{
			arg_nu++;
			flags|=FUNC_FLAGS_DEFALUT_ARGS;
		}
		else if(arg_type==ARG_MANY)
		{
			flags|=FUNC_FLAGS_MANY_ARGS;
		}
		else 
		{
			BUG("Unkown Arg Type");
			goto error;
		}
		ret=btarray_push_back(args_name,S_TO_R(arg->a_name));
		if(ret<0) goto error;
		ret=ast_to_opcode(ARG_TO_AST(arg),m,op);
		if(ret<0) goto error;
	}
	ret=op_code_enlarge_more(op,7);
	if(ret<0) goto error;
	op_code_push(op,OP_ARRAY_END);
	op_code_push(op,OP_FUNC_DEFALUT_ARGS);
	if(op_code_is_udata2(name_id))
	{
		op_code_push3(op,OP_STORE_SYMBOL,name_id);
	}
	else
	{
		op_code_push5(op,OP_STORE_SYMBOL2,name_id);
	}
	if(func) robject_release(FUNC_TO_R(func));
	if(args_name) robject_release(A_TO_R(args_name));
	return 0;
error:
	if(func) robject_release(FUNC_TO_R(func));
	if(args_name) robject_release(A_TO_R(args_name));
	if(func_opcode) op_code_free(func_opcode);
	return -1;
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

AstNodeType node_for=
{
	.t_type=ATN_FOR,
	.t_name="For",
	.t_to_opcode=for_to_opcode,
};
	
AstNodeType node_break=
{
	.t_type=ATN_BREAK,
	.t_name="Break",
	.t_to_opcode=break_to_opcode,
};
AstNodeType node_continue=
{
	.t_type=ATN_CONTINUE,
	.t_name="Continue",
	.t_to_opcode=continue_to_opcode,
};

AstNodeType node_arg=
{
	.t_type=ATN_ARG,
	.t_name="Arg",
	.t_to_opcode=arg_to_opcode,
};
AstNodeType node_func=
{
	.t_type=ATN_FUNC,
	.t_name="Func",
	.t_to_opcode=func_to_opcode,
};






