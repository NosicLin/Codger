#include"gr_opcode.h"
#include<memory/memory.h>
#include<memory/gc.h>
#include<engine/except.h>
#include<string.h>
#include<utility_c/marocs.h>


struct gr_type_info Gr_Type_Opcode=
{
	.t_name="OpcodeObject",
	.t_size=sizeof(GrOpcode),
	.t_ops=&GR_TYPE_OPS_NOT_SUPPORT,
};


#define GR_OPCODE_MIN_SIZE 128 
GrOpcode* GrOpcode_GcNew()
{
	GrOpcode* op=GrGc_New(GrOpcode,&Gr_Type_Opcode);
	if(op==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Opcode Object");
		return NULL;
	}
	if(GrOpcode_Init(op)<0)
	{
		return NULL;
	}

	return op;
}

GrOpcode* GrOpcode_GcNewFlag(long flags)
{
	GrOpcode* op=GrGc_Alloc(GrOpcode,&Gr_Type_Opcode,flags);
	if(op==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Opcode Object");
		return NULL;
	}
	if(GrOpcode_Init(op)<0)
	{
		return NULL;
	}

	return op;
}

int GrOpcode_Init(GrOpcode* op)
{
	u_int8_t* codes=GrMem_Alloc(GR_OPCODE_MIN_SIZE);
	if(codes==NULL) 
	{
		op->o_codes=NULL;
		GrErr_MemFormat("Can't Alloc Memory For Opcode To Init");
		return -1;
	}
	op->o_size=0;
	op->o_cap=GR_OPCODE_MIN_SIZE;
	op->o_codes=codes;
	op->o_args_nu=0;
	op->o_args_min=0;
	op->o_args_name=0;
	op->o_flags=0;
	op->o_name=0;
	op->o_args_name=0;
	return 0;
}

int GrOpcode_EnlargeTo(GrOpcode* op,ssize_t new_cap)
{
	if(new_cap<op->o_cap)
	{
		return 0;
	}
	ssize_t new_size=op->o_size;
	while(new_size<new_cap) new_size<<=1;
	if(new_size<0)
	{
		GrErr_MemFormat("Can't Alloc Memory For Opcode To Enlarge");
		return -1;
	}

	u_int8_t* codes=GrMem_Alloc(new_size);
	if(codes==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Opcode To Enlarge");
		return -1;
	}

	memcpy(codes,op->o_codes,op->o_size);

	GrMem_Free(op->o_codes);
	op->o_codes=codes;
	op->o_cap=new_size;
	return 0;
}


static void op_print_indent(FILE* f,int indent)
{
	int  i;
	for(i=0;i<indent;i++)
	{
		fprintf(f,"\t");
	}
}

static char* s_op_name[]=
{
	"OP_UNKOWN",
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

	"OP_LOAD_CONST",  /* load const<id> to reg0,sizeof(id)=2 */
	"OP_LOAD_SYMBOL",
	"OP_LOAD_U_SYMBOL",

	"OP_STORE_SYMBOL",
	"OP_STORE_U_SYMBOL",


	/* flow control op */
	"OP_BREAK",
	"OP_CONTINUE",

	"OP_JUMP_FORWARD",
	"OP_JUMP_BACK",
	"OP_JUMP_FALSE_FORWARD",
	"OP_JUMP_FALSE_BACK",
	"OP_JUMP_TRUE_FORWARD",
	"OP_JUMP_TRUE_BACK",

	"OP_JUMPR_FORWARD",
	"OP_JUMPR_BACK",
	"OP_JUMPR_FALSE_FORWARD",
	"OP_JUMPR_FALSE_BACK",
	"OP_JUMPR_TRUE_FORWARD",
	"OP_JUMPR_TRUE_BACK",

	/* used for if */
	"OP_TEMP_IF3",


	"OP_LOAD_CONST2",  /* load const<id> to reg0,sizeof(id)=4 */
	"OP_LOAD_SYMBOL2",
	"OP_LOAD_U_SYMBOL2",
	"OP_STORE_SYMBOL2",


};

int GrOpcode_WriteToFile(GrOpcode* op,FILE* f,int indent)
{
	op_print_indent(f,indent);
	fprintf(f,"Name:%s\n",op->o_name->s_value);

	op_print_indent(f,indent);
	fprintf(f,"ArgNu:%d\n",op->o_args_nu);

	op_print_indent(f,indent);
	fprintf(f,"ArgMin:%d\n",op->o_args_min);

	op_print_indent(f,indent);
	fprintf(f,"Flags:");
	if(op->o_flags&GR_OPCODE_FLAG_MANY_ARG)
	{
		fprintf(f,"DEFAULT_ARGS ");
	}
	if(op->o_flags&GR_OPCODE_FLAGS_DEFAULT_ARG)
	{
		fprintf(f,"MANY_ARGS ");
	}
	if(op->o_flags==0)
	{
		fprintf(f,"NORMAL_CODE");
	}
	fprintf(f,"\n");


	op_print_indent(f,indent);
	fprintf(f,"ArgName:");

	int j;
	for(j=0;j<GrArray_Size(op->o_args_name);j++)
	{
		GrObject* arg_name=GrArray_Get(op->o_args_name,j);
		fprintf(f,"%s ",GR_TO_S(arg_name)->s_value);
	}
	fprintf(f,"\n");

	op_print_indent(f,indent);
	fprintf(f,"OpSize:%d\n",op->o_size);

	op_print_indent(f,indent);
	fprintf(f,"OpCodes\n");

	op_print_indent(f,indent);
	fprintf(f,"{\n");

	u_int8_t code;
	u_int8_t d1;
	u_int8_t d2;

	j=0;
	while(j<op->o_size)
	{
		code=op->o_codes[j++];
		op_print_indent(f,indent+1);

	//	printf("code=%d\n",code);
		fprintf(f,"%d \t %s",j-1,s_op_name[code]);
		if(code>=OP_NEED_PARAM2)
		{
			d1=op->o_codes[j++];
			d2=op->o_codes[j++];
			fprintf(f,"<%d>",((u_int16_t)d1<<8|d2));
		}
		else if(code>=OP_NEED_PARAM4)
		{
			TODO("OP_NEED_PARAM4");
		}
		fprintf(f,"\n");
	}
	op_print_indent(f,indent);
	fprintf(f,"}\n");
	return 0;
}

	




	












