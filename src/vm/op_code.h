#ifndef _CODGER_OBJECT_OP_CODE_H_
#define _CODGER_OBJECT_OP_CODE_H_
#define DEFALUT_OP_CAP 32
#include<assert.h>
#include<stdio.h>


struct op_code
{
	ssize_t o_size;
	ssize_t o_cap;
	unsigned char* o_codes;

	/* @o_small_code:it is very usefull when interactive */
	unsigned char o_small_codes[DEFALUT_OP_CAP]; 
};
typedef struct op_code OpCode;


enum OP_CODES
{
	/* expr op */
	OP_CALL,
	OP_SET_ITEM, 
	OP_GET_ITEM,
	OP_POSITIVE,
	OP_NEGATIVE,
	OP_NEGATED,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_PLUS,
	OP_MINUS,
	OP_LSHIFT,
	OP_RSHIFT,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_LT,
	OP_LE,
	OP_NE,
	OP_EQ,
	OP_GE,
	OP_GT,
	OP_BOOL,
	OP_LOGIC_NOT,
	/* op_normal */
	OP_PRINT,
	OP_PRINT_LN,
	
	/* Data op */
	OP_STORE,  /* move reg0 to symbol<id> */
	OP_PUSH,   /* move reg0 to stack */
	OP_DISCARD,
	OP_GET_ATTR,
	OP_SET_ATTR,
	OP_SYMBOL, /* load symbol<id> to reg0 */
	OP_LOAD_CONST,  /* load const<id> to reg0,sizeof(id)=2 */
	OP_LOAD_CONST2,  /* load const<id> to reg0,sizeof(id)=4 */

	/* flow control op */
	OP_BREAK,
	OP_RETURN,
	OP_JUMP_FALSE,
	OP_JUMP_TRUE,



	/* engine op */
	OP_EXIT,
	OP_CODE_NUM,
};

struct op_code* op_code_new();
void op_code_free(struct op_code* op);

int op_code_enlarge(struct op_code* op,int new_cap);

static inline int op_code_enlarge_more(struct op_code* op,int size)
{
	return op_code_enlarge(op,op->o_size+size);
}


static inline ssize_t op_code_size(struct op_code* op)
{
	return op->o_size;
}
static inline void op_code_set(struct op_code* op,
				ssize_t pos,unsigned char code)
{
	op->o_codes[pos]=code;
}
static inline void op_code_set3(struct op_code* op, ssize_t pos, 
						unsigned char code,unsigned short id)
{
	op->o_codes[pos++]=code;
	op->o_codes[pos++]=(unsigned char)(id>>8);
	op->o_codes[pos++]=(unsigned char)id;
}
/* make sure enough space to store code */
static inline void op_code_push(struct op_code* op,unsigned char code)
{
	assert(op->o_size<op->o_cap);
	op->o_codes[op->o_size++]=code;
}
static inline void op_code_pushs(struct op_code* op, unsigned char* codes,int size)
{
	int i=0;
	for(;i<size;i++) op->o_codes[op->o_size++]=codes[i];
}

static inline void op_code_push3(struct op_code* op,
		unsigned char code, unsigned short id)
{
	op->o_codes[op->o_size++]=code;
	op->o_codes[op->o_size++]=(unsigned char)(id>>8);
	op->o_codes[op->o_size++]=(unsigned char)id;
}

static inline void op_code_push5(struct op_code* op,
		unsigned char code,unsigned long id)
{
	op->o_codes[op->o_size++]=code;
	op->o_codes[op->o_size++]=(unsigned char)(id>>24);
	op->o_codes[op->o_size++]=(unsigned char)(id>>16);
	op->o_codes[op->o_size++]=(unsigned char)(id>>8);
	op->o_codes[op->o_size++]=(unsigned char)id;
}

void op_code_print(struct op_code* op,FILE* f);
#endif 
