#include"op_code.h"
#include<rstd/gr_std.h>
#include<string.h>
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
	unsigned char* new_codes=gr_malloc(new_cap);
	if(new_codes==NULL)
	{
		grerr_nomemory();
		return -1;
	}
	unsigned char* old_codes=op->o_codes;
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

