#include"engine.h"
#include"stack_frame.h"
#include<object/module_object.h>
#include<object/robject.h>
#include<utility_c/marocs.h>
#include<rtype/bt_array.h>
#include<rtype/bt_bool.h>
#include<rstd/gr_std.h>
#include"object/symbol_table.h"
/* declare*/
static StackFrame exit_frame;
void enlarge_data_stack();

/* define */
static ModuleObject* eg_module_cur=0;
static StackFrame* eg_frame_bottom=&exit_frame;
static StackFrame* eg_frame_cur=&exit_frame;

/* pc: program countor */
static u_int32_t reg_pc=0;



static u_int8_t* mem_codes=0;
static Robject** const_pool=0;
static Robject** symbol_pool=0;

static SymbolTable* var_scope=0;

static Robject* reg_acc=0;
static Robject* reg_op0=0;
static Robject* reg_op1=0;
static Robject* reg_op2=0;


/* sp: stack pointer */
static u_int32_t reg_sp=0;
static Robject** data_stack=0;
static u_int32_t data_stack_size=0;

/* data register  */
int32_t reg_dp=0;

u_int32_t reg_flags=0;

#define WORD_FROM_CODE \
	do{ \
		reg_dp=(int16_t)(0xff00&((u_int16_t)(mem_codes[reg_pc++])<<8)); \
		reg_dp|=0xff&((u_int16_t)(mem_codes[reg_pc++])); \
	}while(0);

#define DWORD_FORM_CODE \
	do{ \
		reg_dp=(int32_t)(0xff000000&((u_int32_t)(mem_codes[reg_pc++])<<24)); \
		reg_dp|=((u_int32_t)(mem_codes[reg_pc++])<<16); \
		reg_dp|=((u_int32_t)(mem_codes[reg_pc++])<<8); \
		reg_dp|=(mem_codes[reg_pc++]); \
	}while(0)


#define DATA_PUSH_NOREF \
	do { \
		if(reg_sp>=data_stack_size) {enlarge_data_stack();} \
		data_stack[reg_sp++]=reg_acc; \
	} while(0)

#define DATA_PUSH \
	do { \
		if(reg_sp>=data_stack_size) {enlarge_data_stack();} \
		robject_addref(reg_acc); \
		data_stack[reg_sp++]=reg_acc; \
	} while(0)
#define UNPACK_ONE_OP \
	do{ \
		reg_op0=data_stack[--reg_sp];\
	}while(0) 
#define RELEASE_ONE_OP \
	do { \
		robject_release(reg_op0); \
	}while(0) 

#define UNPACK_TWO_OP \
	do{ \
		reg_op1=data_stack[--reg_sp]; \
		reg_op0=data_stack[--reg_sp];  \
	}while(0)

#define RELEASE_TWO_OP \
	do{ \
		robject_release(reg_op1); \
		robject_release(reg_op0); \
	}while(0)

#define UNPACK_THREE_OP \
	do{ \
		reg_op2=data_stack[--reg_sp]; \
		reg_op1=data_stack[--reg_sp]; \
		reg_op0=data_stack[--reg_sp];  \
	}while(0)

#define RELEASE_THREE_OP \
	do{ \
		robject_release(reg_op2); \
		robject_release(reg_op1); \
		robject_release(reg_op0); \
	} while(0)


#define RELEASE_OP0 \
	do { \
		robject_release(reg_op0); \
	}while(0) 

#define RELEASE_OP1 \
	do { \
		robject_release(reg_op1); \
	}while(0) 

#define RELEASE_OP2 \
	do { \
		robject_release(reg_op2); \
	}while(0) 
static void vm_handle_except(){
	TODO("VM_HANDLE_EXCEPT");
	StackFrame* s=eg_frame_bottom;
	s=0;
}


int engine_run()
{
	int runing=1;
	StackFrame* s=0;

	while(runing)
	{
		//printf("pc=%u\n",reg_pc);
		u_int8_t op=mem_codes[reg_pc++];
		switch(op)
		{
			case OP_POSITIVE:
				UNPACK_ONE_OP;
				reg_acc=robject_positive(reg_op0);
				DATA_PUSH_NOREF;
				RELEASE_ONE_OP;
				break;
			case OP_NEGATIVE:
				UNPACK_ONE_OP;
				reg_acc=robject_negative(reg_op0);
				DATA_PUSH_NOREF;
				RELEASE_ONE_OP;
				break;
			case OP_NEGATED:
				UNPACK_ONE_OP;
				reg_acc=robject_negated(reg_op0);
				DATA_PUSH_NOREF;
				RELEASE_ONE_OP;
				break;
			case OP_MUL:
				UNPACK_TWO_OP;
				reg_acc=robject_mul(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_DIV:
				UNPACK_TWO_OP;
				reg_acc=robject_div(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_MOD:
				UNPACK_TWO_OP;
				reg_acc=robject_mod(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_PLUS:
				UNPACK_TWO_OP;
				reg_acc=robject_plus(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_MINUS:
				UNPACK_TWO_OP;
				reg_acc=robject_minus(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_LSHIFT:
				UNPACK_TWO_OP;
				reg_acc=robject_lshift(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_RSHIFT:
				UNPACK_TWO_OP;
				reg_acc=robject_rshift(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_AND:
				UNPACK_TWO_OP;
				reg_acc=robject_and(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_XOR:
				UNPACK_TWO_OP;
				reg_acc=robject_xor(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_OR:
				UNPACK_TWO_OP;
				reg_acc=robject_or(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;
			case OP_LT:
				UNPACK_TWO_OP;
				reg_flags=robject_lt(reg_op0,reg_op1);
				reg_acc=(Robject*)(reg_flags==0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_TWO_OP;
				break;
			case OP_LE:
				UNPACK_TWO_OP;
				reg_flags=robject_le(reg_op0,reg_op1);
				reg_acc=(Robject*)(reg_flags==0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_TWO_OP;
				break;
			case OP_GE:
				UNPACK_TWO_OP;
				reg_flags=robject_ge(reg_op0,reg_op1);
				reg_acc=(Robject*)(reg_flags==0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_TWO_OP;
				break;
			case OP_GT:
				UNPACK_TWO_OP;
				reg_flags=robject_gt(reg_op0,reg_op1);
				reg_acc=(Robject*)(reg_flags==0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_TWO_OP;
				break;
			case OP_NE:
				UNPACK_TWO_OP;
				reg_flags=robject_ne(reg_op0,reg_op1);
				reg_acc=(Robject*)(reg_flags==0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_TWO_OP;
				break;
			case OP_EQ:
				UNPACK_TWO_OP;
				reg_flags=robject_eq(reg_op0,reg_op1);
				reg_acc=(Robject*)(reg_flags==0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_TWO_OP;
				break;
			case OP_ARRAY_BEGIN:
				reg_acc=(Robject*)btarray_create();
				DATA_PUSH_NOREF;
				break;
			case OP_ARRAY_END:
				break;
			case OP_ARRAY_PUSH:
				UNPACK_TWO_OP;
				btarray_push_back(R_TO_A(reg_op0),reg_op1);
				reg_acc=reg_op0;
				DATA_PUSH_NOREF;
				RELEASE_OP1;
				break;
			case OP_SET_ITEM:
				UNPACK_THREE_OP;
				robject_set_item(reg_op1,reg_op2,reg_op0);
				RELEASE_THREE_OP;
				break;
			case OP_GET_ITEM:
				UNPACK_TWO_OP;
				reg_acc=robject_get_item(reg_op0,reg_op1);
				DATA_PUSH_NOREF;
				RELEASE_TWO_OP;
				break;

			case OP_BOOL:
				UNPACK_ONE_OP;
				reg_flags=robject_bool(reg_op0);
				RELEASE_ONE_OP;
				break;
			case OP_BOOL_NOTAKE:
				/* ref top stack data, but not take*/
				reg_op0=data_stack[reg_sp-1];
				reg_flags=robject_bool(reg_op0);
				break;
			case OP_LOGIC_NOT:
				UNPACK_ONE_OP;
				reg_flags=robject_bool(reg_op0);
				reg_acc=(Robject*)(reg_flags!=0?ObjectFalse:ObjectTrue);
				DATA_PUSH;
				RELEASE_ONE_OP;
				break;
			case OP_DISCARD:
				UNPACK_ONE_OP;
				RELEASE_ONE_OP;
				break;

			/* control flow instruction */
			case OP_JUMP_FALSE:
				WORD_FROM_CODE;
				if(reg_flags==0) reg_pc=reg_dp;
				break;
			case OP_JUMP_TRUE:
				WORD_FROM_CODE;
				if(reg_flags==1) reg_pc=reg_dp;
				break;
			case OP_JUMP:
				WORD_FROM_CODE;
				reg_pc=reg_dp;
				break;
			case OP_JUMPR_FALSE:
				WORD_FROM_CODE;
				if(reg_flags==0) reg_pc+=reg_dp-3;
				break;
			case OP_JUMPR_TRUE:
				WORD_FROM_CODE;
				if(reg_flags==1) reg_pc+=reg_dp-3;
				break;
			case OP_JUMPR:
				WORD_FROM_CODE;
				reg_pc+=reg_dp-3;
				break;
			case OP_EXIT:
				runing=0;
				break;
			case OP_RETURN:
				s=engine_pop();
				sframe_free(s);
				break;
			case OP_PRINT:
				UNPACK_ONE_OP;
				robject_print(reg_op0,NULL,PRINT_FLAGS_SPACE);
				RELEASE_ONE_OP;
				break;
			case OP_PRINT_LN:
				printf("\n");
				break;
			case OP_LOAD_CONST:
				WORD_FROM_CODE;
				reg_acc=const_pool[reg_dp];
				DATA_PUSH;
				break;
			case OP_LOAD_CONST2:
				DWORD_FORM_CODE;
				reg_acc=const_pool[reg_dp];
				DATA_PUSH;
				break;
			case OP_LOAD_SYMBOL:
				WORD_FROM_CODE;
				reg_op0=symbol_pool[reg_dp];
				reg_acc=sy_table_lookup(var_scope,reg_op0);
				DATA_PUSH_NOREF;
				break;
			case OP_STORE_SYMBOL:
				WORD_FROM_CODE;
				UNPACK_ONE_OP;
				reg_acc=symbol_pool[reg_dp];
				sy_table_map(var_scope,reg_acc,reg_op0);
				RELEASE_ONE_OP;
				break;
			default:
				BUG("Unkown OpCode(%u) pc=%u",op,reg_pc);
				runing=0;
		}
		if(vm_except_happened())
		{
			vm_handle_except();
		}

	}
	return 1;
}
static OpCode exit_code=
{
	.o_size=1,
	.o_cap=1,
	.o_codes=exit_code.o_small_codes,
	.o_small_codes={OP_EXIT,},
};

static StackFrame exit_frame=
{
	.sf_codes=&exit_code,
	.sf_pc=0,
	.sf_sp=0,
};


static inline int restore_context(StackFrame* s)
{
	reg_pc=s->sf_pc;
	reg_sp=s->sf_sp;
	mem_codes=s->sf_codes->o_codes;
	var_scope=s->sf_scope;

	if(eg_module_cur!=s->sf_modules&&s->sf_modules!=NULL)
	{
		eg_module_cur=s->sf_modules;
		const_pool=eg_module_cur->m_consts->a_objects;
		symbol_pool=eg_module_cur->m_symbols->a_objects;

	}
	return 0;
}

int engine_push(StackFrame* s)
{
	/* only keep the pc and sp value is enough*/
	eg_frame_cur->sf_pc=reg_pc; 
	eg_frame_cur->sf_sp=reg_sp;

	s->sf_link=eg_frame_cur;
	eg_frame_cur=s;

	return  restore_context(s);
}

StackFrame* engine_pop()
{
	StackFrame* s=eg_frame_cur;
	eg_frame_cur=eg_frame_cur->sf_link;
	restore_context(eg_frame_cur);
	return s;
}
#define DEFAULT_DATA_STACK_SIZE 1024*8*sizeof(Robject*)

int engine_init()
{
	data_stack=gr_malloc(DEFAULT_DATA_STACK_SIZE);
	if(data_stack==NULL)
	{
		grerr_nomemory();
		return-1;
	}
	data_stack_size=DEFAULT_DATA_STACK_SIZE-1;
	return 0;
}

void enlarge_data_stack()
{
	ssize_t new_size=(data_stack_size+1)*2;
	Robject** new_statck=gr_malloc(new_size);
	if(new_statck==NULL)
	{
		grerr_nomemory();
		return ;
	}
	memcpy(new_statck,data_stack,data_stack_size+1);
	gr_free(data_stack);
	data_stack=new_statck;
	data_stack_size=new_size-1;
}



int engine_exit()
{
	if(data_stack) gr_free(data_stack);
	WARN_ON(reg_sp>1,"Some Error May Be Happed");
	return 0;
}


