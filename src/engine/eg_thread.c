#include"eg_thread.h"
#include<utility_c/marocs.h>
#include<memory/memory.h>
#include"except.h"
#include<string.h>
#include<stdio.h>
#include<object/gr_consts.h>
#include<object/gr_func.h>
#define EG_THREAD_DEFALUT_DATA_SIZE (1024*8) 

static EgThread* eg_thread_cur=0;

EgThread* EgThread_GetSelf()
{
	return eg_thread_cur;
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

inline int EgThread_PushSframe(EgThread* t,EgSframe* f)
{
	/* save cur frame state */
	if(t->t_fstack)
	{
		t->t_fstack->f_pc=t->t_pc;
		t->t_fstack->f_sp=t->t_sp;
	}

	/* use new frame */
	f->f_thread=t;
	f->f_link=t->t_fstack;
	t->t_fstack=f;

	/* init new frame sp and pc */
	f->f_sp=t->t_sp;
	f->f_pc=0;

	EG_THREAD_SET_FLAGS(t,EG_THREAD_FLAGS_FRAME_CHANGE);
	return 0;
}

inline EgSframe* EgThread_PopSframe(EgThread* eg)
{
	EgSframe* f=eg->t_fstack;
	if(eg->t_fstack) eg->t_fstack=f->f_link;

	EG_THREAD_SET_FLAGS(eg,EG_THREAD_FLAGS_FRAME_CHANGE);
	return f;
}
void EgThread_SFrameReturn(EgThread* eg)
{
	EgSframe* f=eg->t_fstack;
	eg->t_fstack=f->f_link;

	/* push return value to data stack */
	if(eg->t_fstack)
	{
		eg->t_dstack[eg->t_fstack->f_sp++]=eg->t_relval;
	}
	EG_THREAD_SET_FLAGS(eg,EG_THREAD_FLAGS_FRAME_CHANGE);

	EgSframe_Free(f);
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

#define REF_ONE_OP \
	do{ \
		r0=dstack[sp-1]; \
	}while(0) \

#define REF_TWO_OP \
	do{  \
		r0=dstack[sp-2]; \
		r1=dstack[sp-1]; \
	}while(0)

#define REF_THREE_OP \
	do{ \
		r0=dstack[sp-3]; \
		r1=dstack[sp-2]; \
		r2=dstack[sp-1]; \
	}while(0) 


#define ACC_PUSH \
	do{ \
		dstack[sp++]=acc; \
	}while(0) 

#define R0_PUSH \
	do{ \
		dstack[sp++]=r0; \
	}while(0) 

#define R1_PUSH \
	do{ \
		dstack[sp++]=r1; \
	}while(0) 

#define R2_PUSH \
	do{ \
		dstack[sp++]=r2; \
	}while(0) 

#define EG_THREAD_USE_FRAME(f) \
	do{ \
		pc=f->f_pc;  \
		sp=f->f_sp;  \
		codes=f->f_codes->o_codes; \
		scope=f->f_scope;  \
		if(cur_module!=f->f_codes->o_module) \
		{ \
			cur_module=f->f_codes->o_module; \
			consts_pool=cur_module->m_consts_pool->a_objects; \
			symbols_pool=cur_module->m_symbols_pool->a_objects; \
			opcodes_pool=cur_module->m_opcodes_pool->a_objects; \
		} \
	}while(0)


#define DATA_SWAP(x,y) \
	do{ \
		r0=dstack[sp-x-1]; \
		dstack[sp-x-1]=dstack[sp-y-1]; \
		dstack[sp-y-1]=r0; \
	}while(0)





int  EgThread_Run(EgThread* e)
{
	eg_thread_cur=e;
	if(e->t_fstack==NULL)
	{
		return EG_THREAD_EXIT_NORMAL;
	}

	EgThread* eg=e;

	register GrObject** dstack=eg->t_dstack;

		
	/* used for temp compute */
	register u_int8_t cur_code;	/* instruction register*/
	register u_int32_t rd; 		/* data register */
	u_int32_t rs; 				/* status register */
	GrObject* rh=Gr_Object_Nil;
	register GrObject* acc;		
	register GrObject* r0;
	register GrObject* r1;
	register GrObject* r2;
	



	/* frame relative */
	register size_t pc=0;
	register size_t sp=0;
	register u_int8_t* codes=0;
	register GrScope* scope=0;
	GrModule* cur_module=0;
	GrObject** consts_pool=0;
	GrObject** symbols_pool=0;
	GrObject** opcodes_pool=0;
	EgSframe* cur_frame=0;


	/* make sure use cur frame */

	cur_frame=eg->t_fstack;
	EG_THREAD_USE_FRAME(cur_frame);
	EG_THREAD_CLR_FLAGS(eg,EG_THREAD_FLAGS_FRAME_CHANGE);

next_instruct:
	if(GrExcept_Happened())
	{
		return EG_THREAD_EXIT_EXCEPTION;
	}
	if(eg->t_flags)
	{
		if(EG_THREAD_HAS_FLAGS(eg,EG_THREAD_FLAGS_FRAME_CHANGE))
		{
			cur_frame=eg->t_fstack;
			if(cur_frame==NULL)
			{
				return EG_THREAD_EXIT_NORMAL;
			}
			EG_THREAD_USE_FRAME(cur_frame);
			EG_THREAD_CLR_FLAGS(eg,EG_THREAD_FLAGS_FRAME_CHANGE);
		}
	}

	//printf("pc=%d\n",pc);
	cur_code=codes[pc++];
	if(cur_code>=OP_NEED_PARAM2)
	{
		rd=((u_int32_t)(codes[pc++])<<8);
		rd|=(codes[pc++]);
	}

	switch(cur_code)
	{
		case OP_CALL:
			UNPACK_TWO_OP;
			eg->t_sp=sp;
			eg->t_pc=pc;
			r2=rh;
			rh=Gr_Object_Nil;
			acc=GrObject_Call(r0,r2,r1);
			ACC_PUSH;
			goto next_instruct;
		case OP_SET_ITEM:
			UNPACK_THREE_OP;
			GrObject_SetItem(r1,r2,r0);
			goto next_instruct;
		case OP_GET_ITEM:
			UNPACK_TWO_OP;
			acc=GrObject_GetItem(r0,r1);
			ACC_PUSH;
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
		case OP_BOOL_NOTAKE:
			REF_ONE_OP;
			rs=GrObject_Bool(r0);
			ACC_PUSH;
			goto next_instruct;
		case OP_BOOL:
			UNPACK_ONE_OP;
			rs=GrObject_Bool(r0);
			goto next_instruct;
		case OP_LOGIC_NOT:
			assert(0);
			goto next_instruct;
		case OP_PRINT:
			UNPACK_ONE_OP;
			GrObject_Print(r0,stdout,GR_PRINT_SPACE);
			goto next_instruct;
		case OP_PRINT_LN:
			fprintf(stdout,"\n");
			goto next_instruct;
		case OP_ITER:
			UNPACK_ONE_OP;
			acc=GrObject_Iter(r0);
			ACC_PUSH;
			goto next_instruct;
		case OP_ITER_NEXT:
			REF_ONE_OP;
			acc=GrObject_IterNext(r0);
			if(GrExcept_Happened())
			{
				if(GrExcept_Type()==Gr_Except_Iter_Stop)
				{
					GrExcept_Clr();
					goto next_instruct;
				}
			}
			else
			{
				pc+=3;
			}
			ACC_PUSH;
			goto next_instruct;

		case OP_ARRAY_BEGIN:
			acc=(GrObject*)GrArray_GcNew();
			ACC_PUSH;
			goto next_instruct;
		case OP_ARRAY_PUSH:
			UNPACK_TWO_OP;
			GrArray_Push((GrArray*)r0,r1);
			R0_PUSH;
			goto next_instruct;
		case OP_ARRAY_END:
			goto next_instruct;

		case OP_FUNC_BEGIN:
			acc=(GrObject*)GrFunc_GcNew();
			if(acc==NULL) goto next_instruct;
			GrFunc_SetScope((GrFunc*)acc,scope);
			ACC_PUSH;
			goto next_instruct;
		case OP_FUNC_DEFALUT_ARGS:
			REF_TWO_OP;
			GrFunc_SetDefaultArgs((GrFunc*)r0,(GrArray*)r1);
			sp--;
			goto next_instruct;

		/* Data op */
		case OP_DISCARD:
			sp--;
			goto next_instruct;
		case OP_DUP_DATA1:
			REF_ONE_OP;
			R0_PUSH;
			goto next_instruct;
		case OP_DUP_DATA2:
			REF_TWO_OP;
			R0_PUSH;
			R1_PUSH;
			goto next_instruct;
		case OP_DUP_DATA3:
			REF_THREE_OP;
			R0_PUSH;
			R1_PUSH;
			R2_PUSH;
			goto next_instruct;
		case OP_DATA_SWAP0_1:
			DATA_SWAP(0,1);
			goto next_instruct;
		case OP_DATA_SWAP0_2:
			DATA_SWAP(0,2);
			goto next_instruct;
		case OP_DATA_SWAP0_3:
			DATA_SWAP(0,3);
			goto next_instruct;
		case OP_SET_HOST:
			UNPACK_ONE_OP;
			rh=r0;
			goto next_instruct;

		/* frame op */
		case OP_EXIT:
			assert(0);
			goto over;
		case OP_RETURN:
			UNPACK_ONE_OP;
			eg->t_relval=r0;
			EgThread_SFrameReturn(eg);
			goto next_instruct;
		case OP_RETURN_NIL:
			eg->t_relval=Gr_Object_Nil;
			EgThread_SFrameReturn(eg);
			goto next_instruct;

		/* OP_NEED_PARAM2 OPCODE */
		case OP_GET_ATTR:
			UNPACK_ONE_OP;
			r1=symbols_pool[rd];
			acc=GrObject_GetAttr(r0,r1,0);
			ACC_PUSH;
			goto next_instruct;
		case OP_SET_ATTR:
			UNPACK_TWO_OP;
			r2=symbols_pool[rd];
			GrObject_SetAttr(r1,r2,r0,0);
			goto next_instruct;
		case OP_FUNC_OPCODE:
			REF_ONE_OP;
			GrFunc_SetOpcode((GrFunc*)r0,(GrOpcode*)(opcodes_pool[rd]));
			goto next_instruct;
			
		case  OP_LOAD_CONST:
			dstack[sp++]=consts_pool[rd];
			goto next_instruct;
		case OP_LOAD_SYMBOL:
			r0=symbols_pool[rd];
			acc=GrScope_Lookup(scope,r0);
			ACC_PUSH;
			goto next_instruct;
		case OP_LOAD_U_SYMBOL:
			r0=symbols_pool[rd];
			acc=GrScope_LookupUpper(scope,r0);
			ACC_PUSH;
			goto next_instruct;
		case OP_STORE_SYMBOL:
			UNPACK_ONE_OP;
			r1=symbols_pool[rd];
			GrScope_Map(scope,r1,r0);
			goto next_instruct;
		case OP_STORE_U_SYMBOL:
			UNPACK_ONE_OP;
			r1=symbols_pool[rd];
			GrScope_MapUpper(scope,r1,r0);
			goto next_instruct;

		/* flow control op */
		case OP_BREAK:
			assert(0);
		case OP_CONTINUE:
			assert(0);

		case OP_JUMPR_FORWARD:
			pc+=rd-3;
			goto next_instruct;
		case OP_JUMPR_BACK:
			pc-=rd+3;
			goto next_instruct;
		case OP_JUMPR_FALSE_FORWARD:
			if(!rs) pc+=rd-3;
			goto next_instruct;
		case OP_JUMP_FALSE_BACK:
			if(!rs) pc-=rd+3;
			goto next_instruct;
		case OP_JUMPR_TRUE_FORWARD:
			if(rs) pc+=rd-3;
			goto next_instruct;
		case OP_JUMP_TRUE_BACK:
			if(rs) pc-=rd+3;
			goto next_instruct;

		case OP_TEMP_IF3:
			assert(0);




	}

	if(cur_code<OP_CODE_NUM)
	{
		printf("Not Implement %s\n",GrOpcode_Name(cur_code));
	}
	else
	{
		BUG("Unkown instruction<%d>",cur_code);
	}

over:

	return 0;
}














