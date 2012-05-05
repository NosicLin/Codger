#include"eg_thread.h"
#include<utility_c/marocs.h>
#include<memory/memory.h>
#include"except.h"
#include<string.h>
#include<stdio.h>
#include<object/gr_consts.h>
#define EG_THREAD_DEFALUT_DATA_SIZE (1024*8) 


static inline void eg_thread_use_frame(EgThread* t,EgSframe* f)
{
	GrModule* cur=t->t_cur_module;
	GrModule* target=f->f_codes->o_module;
	if(cur!=target)
	{
		t->t_const_pool=target->m_consts_pool->a_objects;
		t->t_opcode_pool=target->m_opcodes_pool->a_objects;
		t->t_symbol_pool=target->m_symbols_pool->a_objects;
		cur=target;
	}
	t->t_codes=f->f_codes->o_codes;
	t->t_cur_frame=f;
}





EgThread* EgThread_New()
{
	EgThread* t=GrMem_Alloc(sizeof(*t));
	if(t==NULL) 
	{
		GrErr_MemFormat("Can't Alloc Memory For EgThread");
		return NULL;
	}

	memset(t,0,sizeof(*t));

	t->t_dstack=GrMem_Alloc(EG_THREAD_DEFALUT_DATA_SIZE*sizeof(GrObject*));
	if(t->t_dstack==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For EgThread Data Stack");
		GrMem_Free(t);
		return NULL;
	}
	t->t_dstack_cap=EG_THREAD_DEFALUT_DATA_SIZE;
	return t;
}

int EgThread_Delete(EgThread* t)
{
	if(t->t_dstack) GrMem_Free(t->t_dstack);
	GrMem_Free(t);
	return 0;
}

int EgThread_PushSframe(EgThread* t,EgSframe* f)
{
	f->f_thread=t;
	f->f_link=t->t_fstack;
	t->t_fstack=f;
	return 0;
}

int EgThread_RestoreContex(EgThread* t,EgSframe* f)
{
	eg_thread_use_frame(t,f);
	return 0;
}

#define UNPACK_ONE_OP \
	do{ \
		r0=dstack[--sp]; \
	}while(0) 

#define UNPACK_TWO_OP \
	do{ \
		r1=dstack[--sp]; \
		r0=dstack[--sp]; \
	}while(0)

#define UNPACK_THREE_OP  \
	do{ \
		r2=dstack[--sp]; \
		r1=dstack[--sp]; \
		r0=dstack[--sp]; \
	}while(0)

#define ACC_PUSH \
	do{ \
		dstack[sp++]=acc; \
	}while(0) 


int  EgThread_Run(EgThread* e)
{
	if(e->t_fstack==NULL)
	{
		return EG_THREAD_EXIT_NORMAL;
	}
	eg_thread_use_frame(e,e->t_fstack);

	register EgThread* eg=e;

	register size_t pc=eg->t_pc;
	register size_t sp=eg->t_sp;
	register GrObject** dstack=eg->t_dstack;

	register u_int8_t* codes=eg->t_codes;
	register u_int8_t cur_code;

	register u_int32_t rd;
	register GrObject* acc;
	register GrObject* r0;
	register GrObject* r1;
	//register GrObject* r2;


	while(1)
	{
next_instruct:
		cur_code=codes[pc++];
		if(cur_code>=OP_NEED_PARAM2)
		{
			rd=((u_int32_t)(codes[pc++])<<8);
			rd|=(codes[pc++]);
		}
		if(GrExcept_Happened())
		{
			return EG_THREAD_EXIT_EXCEPTION;
		}

		switch(cur_code)
		{
			case  OP_LOAD_CONST:
				dstack[sp++]=eg->t_const_pool[rd];
				goto next_instruct;
			case OP_POSITIVE:
				UNPACK_ONE_OP;
				acc=GrObject_Positive(r0);
				ACC_PUSH;
				goto next_instruct;
			case OP_NEGATIVE:
				UNPACK_ONE_OP;
				acc=GrObject_Negative(r0);
				ACC_PUSH;
				goto next_instruct;

			case OP_NEGATED:
				UNPACK_ONE_OP;
				acc=GrObject_Negated(r0);
				ACC_PUSH;
				goto next_instruct;
			case OP_MUL:
				UNPACK_TWO_OP;
				acc=GrObject_Mul(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_DIV:
				UNPACK_TWO_OP;
				acc=GrObject_Div(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_MOD:
				UNPACK_TWO_OP;
				acc=GrObject_Mod(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_PLUS:
				UNPACK_TWO_OP;
				acc=GrObject_Plus(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_MINUS:
				UNPACK_TWO_OP;
				acc=GrObject_Minus(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_LSHIFT:
				UNPACK_TWO_OP;
				acc=GrObject_LShift(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_RSHIFT:
				UNPACK_TWO_OP;
				acc=GrObject_RShift(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_AND:
				UNPACK_TWO_OP;
				acc=GrObject_And(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_XOR:
				UNPACK_TWO_OP;
				acc=GrObject_Xor(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_OR:
				UNPACK_TWO_OP;
				acc=GrObject_Or(r0,r1);
				ACC_PUSH;
				goto next_instruct;
			case OP_LT:
				UNPACK_TWO_OP;
				acc=GrObject_Lt(r0,r1)?Gr_True:Gr_False;
				ACC_PUSH;
				goto next_instruct;
			case OP_LE:
				UNPACK_TWO_OP;
				acc=GrObject_Le(r0,r1)?Gr_True:Gr_False;
				ACC_PUSH;
				goto next_instruct;
			case OP_GE:
				UNPACK_TWO_OP;
				acc=GrObject_Ge(r0,r1)?Gr_True:Gr_False;
				ACC_PUSH;
				goto next_instruct;
			case OP_GT:
				UNPACK_TWO_OP;
				acc=GrObject_Gt(r0,r1)?Gr_True:Gr_False;
				ACC_PUSH;
				goto next_instruct;
			case OP_EQ:
				UNPACK_TWO_OP;
				acc=GrObject_Eq(r0,r1)?Gr_True:Gr_False;
				ACC_PUSH;
				goto next_instruct;
			case OP_NE:
				UNPACK_TWO_OP;
				acc=GrObject_Ne(r0,r1)?Gr_True:Gr_False;
				ACC_PUSH;
				goto next_instruct;
			case OP_PRINT:
				UNPACK_ONE_OP;
				GrObject_Print(r0,stdout,GR_PRINT_SPACE);
				goto next_instruct;
			case OP_PRINT_LN:
				fprintf(stdout,"\n");
				goto next_instruct;
			case OP_RETURN:
				goto over;
			case OP_RETURN_NIL:
				goto over;

		}


		BUG("Unkown instruction");
	}
over:

	return 0;
}














