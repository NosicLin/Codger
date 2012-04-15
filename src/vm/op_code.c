#include"op_code.h"
#include<rstd/gr_std.h>
#include<string.h>
#include<utility_c/marocs.h>
struct op_code* op_code_new()
{
	struct op_code* op=gr_malloc(sizeof(*op));
	if(op==NULL)
	{
		grerr_nomemory();
		return NULL;
	}
	op->o_codes=op->o_small_codes;
	op->o_cap=DEFALUT_OP_CAP;
	op->o_size=0;
	return op;
}

int op_code_enlarge(struct op_code* op,int cap)
{
	if(cap<=op->o_cap)
	{
		return 0;
	}
	ssize_t new_cap=op->o_cap;
	while(new_cap<cap&&new_cap>0) new_cap<<=1;
	if(new_cap<0)
	{
		return -1;
	}
	u_int8_t* new_codes=gr_malloc(new_cap);
	if(new_codes==NULL)
	{
		grerr_nomemory();
		return -1;
	}
	u_int8_t* old_codes=op->o_codes;
	memcpy(new_codes,old_codes,op->o_size);
	op->o_codes=new_codes;
	op->o_cap=new_cap;
	if(old_codes!=op->o_small_codes) gr_free(old_codes);
	return 0;
}


void op_code_free(struct op_code* op)
{
	assert(op->o_codes);
	if(op->o_codes!=op->o_small_codes)
	{
		gr_free(op->o_codes);
	}
	gr_free(op);
}
static char* s_op_name[]=
{
	"OP_CALL",
	"OP_SET_ITEM",
	"OP_GET_ITEM",
	"OP_POSITIVE",
	"OP_NEGATIVE",
	"OP_NEGATED",
	"OP_MUL",
	"OP_DIV",
	"OP_MOD",
	"OP_PLUS",
	"OP_MINUS",
	"OP_LSHIFT",
	"OP_RSHIFT",
	"OP_AND",
	"OP_OR",
	"OP_XOR",
	"OP_LT",
	"OP_LE",
	"OP_NE",
	"OP_EQ",
	"OP_GE",
	"OP_GT",
	"OP_BOOL_NOTAKE",
	"OP_BOOL",
	"OP_LOGIC_NOT",
	/* op_normal */
	"OP_PRINT",
	"OP_PRINT_LN",
	
	/* iterator */
	"OP_ITER",
	"OP_ITER_NEXT",

	/* array item */
	"OP_ARRAY_BEGIN",
	"OP_ARRAY_PUSH",
	"OP_ARRAY_END",
	/* engine op */
	"OP_EXIT",
	"OP_RETURN",

	/* Data op */
	"OP_STORE",  /* move reg0 to symbol<id> */
	"OP_PUSH",   /* move reg0 to stack */
	"OP_DISCARD",


	"OP_FUNC_DEFALUT_ARGS",

	"OP_GET_ATTR",
	"OP_SET_ATTR",
	"OP_SYMBOL", /* load symbol<id> to reg0 */
	"OP_LOAD_CONST",  /* load const<id> to reg0,sizeof(id)=2 */
	"OP_LOAD_SYMBOL",
	"OP_STORE_SYMBOL",

	/* flow control op */
	"OP_BREAK",
	"OP_CONTINUE",
	"OP_JUMP",
	"OP_JUMP_FALSE",
	"OP_JUMP_TRUE",

	"OP_JUMPR",
	"OP_JUMPR_FALSE",
	"OP_JUMPR_TRUE",

	/* used for if */
	"OP_TEMP_IF3",


	"OP_LOAD_CONST2",  /* load const<id> to reg0,sizeof(id)=4 */
	"OP_STORE_SYMBOL2",


};

void op_code_print(struct op_code* op,FILE* f,int indent)
{
	ssize_t i=0;
	int j;
	for(j=0;j<indent;j++)
	{
		fprintf(f,"\t");
	}
	fprintf(f,"#OpCode Size=%d\n",op->o_size);
	u_int8_t code=0;
	u_int8_t d1=0;
	u_int8_t d2=0;
	i=0;
	while(i<op->o_size)
	{
		code=op->o_codes[i++];
		assert(code<OP_CODE_NUM);
		for(j=0;j<indent;j++)
		{
			fprintf(f,"\t");
		}
		fprintf(f,"%d\t %s",i-1,s_op_name[code]);
		if(code>=OP_NEED_PARAM2)
		{
			d1=op->o_codes[i++];
			d2=op->o_codes[i++];
			printf("<%d>",(int16_t)((u_int16_t)d1<<8|d2));
		}
		else if(code>=OP_NEED_PARAM4)
		{
			TODO("OP_NEED_PARAM4");
		}
		fprintf(f,"\n");
	}
}







