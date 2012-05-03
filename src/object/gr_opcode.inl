#ifndef _CODGER_OBJECT_OP_CODE_INL_
#define _CODGER_OBJECT_OP_CODE_INL_

#ifndef GR_OPCODE_DEBUG
static inline void GR_OPCODE_CHECK_POS(GrOpcode* op,ssize_t pos) 
{
	BUG_ON(pos>=op->o_size,"Pos=%d,Op->o_size=%d",pos,op->o_size);
}
#else
#define GR_OPCODE_CHECK_POS(op,x) 
#endif 


static inline int GrOpcode_GetSize(GrOpcode* op)
{
	return op->o_size;
}


static inline int GrOpcode_NeedMore(GrOpcode* op,ssize_t size)
{
	return GrOpcode_EnlargeTo(op,op->o_size+size);
}

static inline void GrOpcode_SetCode(GrOpcode* op,ssize_t pos,u_int8_t code)
{
	GR_OPCODE_CHECK_POS(op,pos);
	op->o_codes[pos]=code;
}



static inline void 
GrOpcode_SetCode3(GrOpcode* op,ssize_t pos,
									u_int8_t code ,u_int16_t arg)
{
	GR_OPCODE_CHECK_POS(op,pos+2);
	op->o_codes[pos++]=code;
	op->o_codes[pos++]=(u_int8_t) ((arg>>8)&0xff);
	op->o_codes[pos++]=(u_int8_t) (arg&0xff);
}

static inline void 
GrOpcode_SetCode5(GrOpcode* op,ssize_t pos,
								u_int8_t code,u_int32_t arg)
{
	GR_OPCODE_CHECK_POS(op,pos+4);
	op->o_codes[pos++]=code;
	op->o_codes[pos++]=(u_int8_t) ((arg>>24)&0xff);
	op->o_codes[pos++]=(u_int8_t) ((arg>>16)&0xff);
	op->o_codes[pos++]=(u_int8_t) ((arg>>8)&0xff);
	op->o_codes[pos++]=(u_int8_t) (arg&0xff);
}


static inline void 
GrOpcode_Push(GrOpcode* op,u_int8_t code)
{
	op->o_size++;
	GrOpcode_SetCode(op,op->o_size-1,code);
}
static inline void 
GrOpcode_Push3(GrOpcode* op,u_int8_t code,u_int16_t arg)
{
	op->o_size+=3;
	GrOpcode_SetCode3(op,op->o_size-3,code,arg);
}


static inline void 
GrOpcode_Push5(GrOpcode* op,u_int8_t code,u_int32_t arg)
{
	op->o_size+=5;
	GrOpcode_SetCode5(op,op->o_size-5,code,arg);
}

static inline int GrOpcode_OpdataSize16(u_int32_t op_data)
{
	return op_data<(1ul<<16);
}

static inline void GrOpcode_SetArgNu(GrOpcode* op,int nu)
{
	op->o_args_nu=nu;
}
static inline void GrOpcode_SetArgMin(GrOpcode* op,int nu)
{
	op->o_args_min=nu;
}
static inline void GrOpcode_SetFlags(GrOpcode* op,long flags)
{
	op->o_flags|=flags;
}
static inline void GrOpcode_ClrFlags(GrOpcode* op,long flags)
{
	op->o_flags&=~flags;
}

static inline void GrOpcode_SetArgName(GrOpcode* op,GrArray* args_name)
{
	op->o_args_name=args_name;
}
static inline void GrOpcode_SetName(GrOpcode* op,GrString* name)
{
	op->o_name=name;
}

static inline int GrOpcode_Verify(GrObject* g)
{
	return GrObject_Type(g)==&Gr_Type_Opcode;
}
#endif /*_CODGER_OBJECT_OP_CODE_INL_*/

