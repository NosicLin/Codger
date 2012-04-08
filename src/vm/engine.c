#include"engine.h"
#include"stack_frame.h"
#include<object/module_object.h>
#include<object/robject.h>

static ModuleObject* eg_module_cur=0;
static StackFrame* eg_frame_bottom=0;
static StackFrame* eg_frame_cur=0;

static ssize_t pc=0;

static Robject* reg_acc=0;


static unsigned char* mem_codes=0;
static Robject* r_consts=0;
static Robject* r_symbols=0;

static Robject* data_stack=0;

static Robject* reg_op1=1;
static Robject* reg_op2=2;
static Robject* reg_op3=3;

#define  UNPACK_TWO_OP \
	do{ \
		reg_op2=data_stack; \
		reg_op1=reg_op2->r_next; \
		data_stack=reg_op1->r_next; \
	}while(0) 

#define UNPACK_THREE_OP \
	do{ \
		reg_op3=data_stack; \
		reg_op2=reg_op3; \
		reg_op1=reg_op2->r_next; \
		data_stack=reg_op1->r_next; \
	}while(0)

int engine_run()
{
	bool runing=true;
	while(runing)
	{
		if(except_happened())
		{
			handle_except();
		}
		unsigned char op=op_codes[s_pc++];
		switch(op)
		{
			case OP_POSITIVE:
				reg_acc=robject_positive(s_reg0);
				break;
			case OP_NEGATIVE:
				reg_acc=robject_negative(s_reg0);
				break;
			case OP_NEGATED:
				reg_acc=robject_negative(s_reg0);
				break;
			case OP_MUL:
				UNPACK_TWO_OP;
				reg_acc=reg_acc=robject_mul(reg_op1,reg_op2);
				break;
			case OP_EXIT:
				runing=false;
				break;
			case OP_RETURN:
				StackFrame* s=engine_pop();
				sframe_free(s);
			default:
				BUG("Unkown OpCode");
				runing=false;
		}
				
	}
	return 1;
}

static inline int init_context(struct stack_frame* s)
{
	pc=s->sf_pc;
	mem_codes=s->sf_codes->o_codes;

	if(eg_module_cur!=s->sf_modules)
	{
		eg_module_cur=s->sf_modules;
		r_consts=eg_module_cur->m_consts->a_objects;
		r_symbols=eg_module_cur->m_symbols->a_objects;
	}
	return 0;
}

int engine_push(struct  stack_frame* s)
{
	eg_frame_cur->sf_pc=pc; /* only keep the pc value is enough*/

	s->sf_link=eg_frame_cur;
	eg_frame_cur=s;

	return  init_context(s);
}

struct stack_frame* engine_pop()
{
	StackFrame* s=eg_frame_cur;
	eg_frame_cur=eg_frame_cur->sf_next;
	init_context(eg_frame_cur);
	return s;
}

