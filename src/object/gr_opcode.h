#ifndef _CODGER_OBJECT_OP_CODE_H_
#define _CODGER_OBJECT_OP_CODE_H_

#include"gr_object.h"
#include"gr_string.h"
#include"gr_array.h"
#include"assert.h"

#define GR_OPCODE_DEBUG 

#define GR_OPCODE_FLAG_MANY_ARG 0x1l
#define GR_OPCODE_FLAGS_DEFAULT_ARG (0x1l<<1)



struct  gr_opcode 
{
	INHERIT_GROBJECT;

	long o_flags;

	int o_args_nu;
	int o_args_min;

	GrString* o_name;
	GrArray* o_args_name;

	ssize_t o_size;
	ssize_t o_cap;
	u_int8_t* o_codes;
};
typedef struct gr_opcode GrOpcode;

extern GrTypeInfo Gr_Type_Opcode;

GrOpcode* GrOpcode_GcNew();

GrOpcode* GrOpcode_GcNewFlag(long);
int GrOpcode_Init(GrOpcode*);


int GrOpcode_EnlargeTo(GrOpcode*,ssize_t new_cap);
static inline ssize_t GrOpcode_GetSize(GrOpcode*);

static inline int GrOpcode_NeedMore(GrOpcode*,ssize_t size);

static inline void GrOpcode_SetCode(GrOpcode*,ssize_t pos,u_int8_t );
static inline void GrOpcode_SetCode3(GrOpcode*,ssize_t pos,u_int8_t ,u_int16_t);
static inline void GrOpcode_SetCode5(GrOpcode*,ssize_t pos,u_int8_t,u_int32_t);

static inline void GrOpcode_Push(GrOpcode*,u_int8_t code);
static inline void GrOpcode_Push3(GrOpcode*,u_int8_t code,u_int16_t);
static inline void GrOpcode_Push5(GrOpcode*,u_int8_t code,u_int32_t);

static inline int GrOpcode_OpdataSize16(u_int32_t);


static inline void GrOpcode_SetArgNu(GrOpcode*,int);
static inline void GrOpcode_SetArgMin(GrOpcode*,int);
static inline void GrOpcode_SetName(GrOpcode*,GrString* name);
static inline void GrOpcode_SetFlags(GrOpcode*,long);
static inline void GrOpcode_ClrFlags(GrOpcode*,long);
static inline void GrOpcode_SetArgName(GrOpcode*,GrArray*);

static inline int GrOpcode_Verify(GrObject*);

#include"gr_opcode.inl"

int GrOpcode_WriteToFile(GrOpcode* ,FILE* f,int indent);

#ifdef GR_OPCODE_DEBUG 
static inline GrObject* OPCODE_TO_GR(GrOpcode* op)
{
	return (GrObject*)op;
}

static inline GrOpcode* GR_TO_OPCODE(GrObject* op)
{
	assert(GrOpcode_Verify(op));
	return (GrOpcode*)op;
}
#else
#define OPCODE_TO_GR(x) ((GrObject*)(x))
#define GR_TO_OPCODE(x) ((GrOpcode*)(x))
#endif /*GR_OPCODE_DEBUG*/


enum OP_CODES
{
	OP_UNKOWN=0,
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
	OP_BOOL_NOTAKE,
	OP_BOOL,
	OP_LOGIC_NOT,
	/* op_normal */
	OP_PRINT,
	OP_PRINT_LN,

	/* iterator */
	OP_ITER,
	OP_ITER_NEXT,
	
	/* array item */
	OP_ARRAY_BEGIN,
	OP_ARRAY_PUSH,
	OP_ARRAY_END,
	/* engine op */
	OP_EXIT,
	OP_RETURN,

	/* Data op */
	OP_STORE,  /* move reg0 to symbol<id> */
	OP_PUSH,   /* move reg0 to stack */
	OP_DISCARD,

	/* func */
	OP_FUNC_DEFALUT_ARGS,
#define OP_NEED_PARAM2 OP_GET_ATTR
	OP_GET_ATTR,
	OP_SET_ATTR,
	OP_SYMBOL, /* load symbol<id> to reg0 */
	OP_LOAD_CONST,  /* load const<id> to reg0,sizeof(id)=2 */
	OP_LOAD_SYMBOL,
	OP_STORE_SYMBOL,
	OP_LOAD_GLOBAL,
	OP_STORE_GLOBAL,

	/* flow control op */
	OP_BREAK,
	OP_CONTINUE,
	OP_JUMP,
	OP_JUMP_FALSE,
	OP_JUMP_TRUE,

	OP_JUMPR,
	OP_JUMPR_FALSE,
	OP_JUMPR_TRUE,

	/*used for if */
	OP_TEMP_IF3,

#define OP_NEED_PARAM4 OP_LOAD_CONST2
	OP_LOAD_CONST2,  /* load const<id> to reg0,sizeof(id)=4 */
	OP_STORE_SYMBOL2,


	OP_CODE_NUM,
};

#endif /* _CODGER_OBJECT_OP_CODE_H_*/






