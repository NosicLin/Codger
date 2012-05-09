#ifndef _CODGER_OBJECT_OP_CODE_H_
#define _CODGER_OBJECT_OP_CODE_H_

#include"gr_object.h"
#include"gr_string.h"
#include"gr_array.h"
#include"assert.h"

#define GR_OPCODE_DEBUG 

#define GR_OPCODE_FLAG_MANY_ARG 0x1l
#define GR_OPCODE_FLAG_DEFAULT_ARG (0x1l<<1)


struct gr_module;

struct  gr_opcode 
{
	INHERIT_GROBJECT;

	long o_flags;

	int o_args_nu;
	int o_args_min;

	GrString* o_name;
	GrArray* o_args_name;

	struct gr_module* o_module;

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
static inline void GrOpcode_SetModule(GrOpcode*,struct gr_module*);


static inline int GrOpcode_Verify(GrObject*);

#include"gr_opcode.inl"

int GrOpcode_WriteToFile(GrOpcode* ,FILE* f,int indent);
const char* GrOpcode_Name(u_int8_t );

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
	OP_XOR,
	OP_OR,
	OP_LT,
	OP_LE,
	OP_EQ,
	OP_NE,
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

	/*func object*/
	OP_FUNC_BEGIN,
	OP_FUNC_DEFALUT_ARGS,

	/*class */
	OP_CLASS_BEGIN,
	OP_CLASS_INHERIT,


	/* Data op */
	OP_LOAD_NIL,
	OP_DISCARD,
	OP_DUP_DATA1,
	OP_DUP_DATA2,
	OP_DUP_DATA3,
	OP_DATA_SWAP0_1,
	OP_DATA_SWAP0_2,
	OP_DATA_SWAP0_3,
	OP_SET_HOST,

	/* engine op */
	OP_EXIT,
	OP_RETURN,
	OP_RETURN_NIL,

#define OP_NEED_PARAM2 OP_GET_ATTR
	OP_GET_ATTR,
	OP_SET_ATTR,


	OP_CLASS_TEMPLATE,
	OP_CLASS_ATTR,


	OP_FUNC_OPCODE,

	OP_LOAD_CONST,  /* load const<id> to reg0,sizeof(id)=2 */
	OP_LOAD_SYMBOL,
	OP_LOAD_U_SYMBOL,

	OP_STORE_SYMBOL,
	OP_STORE_U_SYMBOL,

	/* flow control op */
	OP_BREAK,
	OP_CONTINUE,

	OP_JUMP_FORWARD,
	OP_JUMP_BACK,
	OP_JUMP_FALSE_FORWARD,
	OP_JUMP_FALSE_BACK,
	OP_JUMP_TRUE_FORWARD,
	OP_JUMP_TRUE_BACK,

	OP_JUMPR_FORWARD,
	OP_JUMPR_BACK,
	OP_JUMPR_FALSE_FORWARD,
	OP_JUMPR_FALSE_BACK,
	OP_JUMPR_TRUE_FORWARD,
	OP_JUMPR_TRUE_BACK,

	/*used for if */
	OP_TEMP_IF3,

#define OP_NEED_PARAM4 OP_LOAD_CONST2
	OP_LOAD_CONST2,  /* load const<id> to reg0,sizeof(id)=4 */
	OP_LOAD_SYMBOL2,
	OP_LOAD_U_SYMBOL2,

	OP_STORE_SYMBOL2,
	OP_STORE_U_SYMBOL2,

	OP_GET_ATTR2,
	OP_SET_ATTR2,

	OP_CLASS_INHERIT2,

	OP_CLASS_TEMPLATE2,
	OP_CLASS_ATTR2,

	OP_CODE_NUM,
};

#endif /* _CODGER_OBJECT_OP_CODE_H_*/






