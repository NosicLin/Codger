#include"gr_int.h"
#include<memory/gc.h>
#include<memory/memory.h>
#include<utility_c/marocs.h>
#include<string.h>

static int char_to_int(char c)
{
	int ret=0;
	if('0'<=c && c<='9')
	{
		ret=c-'0';
	}
	else if('a'<=c && c<='f')
	{
		ret= c-'a'+10;
	}
	else if('A'<=c && c<='F')
	{
		ret=c-'A'+10;
	}
	else 
	{
		/* invalid char */
		BUG("Error Char(%c)",c);
		ret=0;
	}
	return ret; 
}

static int str_to_int(const char* str)
{
	int len=strlen(str);
	int base=0;
	int value=0;
	assert(len!=0);
	if(len==1)
	{
		BUG_ON(*str<'0'||*str>'9',"Error Str(%s)",str);
		return *str-'0';
	}
	if(*str=='0')
	{
		char str_1=*(str+1);
		if(str_1=='x'||str_1=='X')
		{
			base=16;
			str+=2;
		}
		else if (str_1=='b'||str_1=='B')
		{
			base=2;
			str+=2;
		}
		else if (str_1=='o'||str_1=='O')
		{
			base=8;
			str+=2;
		}
		else 
		{
			base=8;
			str+=1;
		}
	}
	else
	{
		base=10;
	}

	while(*str)
	{
		char c_str=*str;
		int c_value=char_to_int(c_str);
		value=value*base+c_value;
		str++;
	}
	return value;
}



#define GrMem_ALLOC_INT_ERR \
		GrErr_MemFormat("Can't Alloc Memory For Int Object")

inline GrInt* GrInt_GcNew(long value)
{
	GrInt* ret=GrGc_New(GrInt,&Gr_Type_Int);

	if(ret==NULL)
	{
		GrMem_ALLOC_INT_ERR;
		return  NULL;
	}
	ret->i_value=value;
	return ret;
}
inline GrInt* GrInt_GcNewFlag(long value,long flags)
{
	GrInt* ret=GrGc_Alloc(GrInt,&Gr_Type_Int,flags);

	if(ret==NULL)
	{
		GrMem_ALLOC_INT_ERR;
		return  NULL;
	}
	ret->i_value=value;
	return ret;
}

GrInt* GrInt_GcNewFromStr(const char* str)
{
	long val=str_to_int(str);
	return GrInt_GcNew(val);
}
GrInt* GrInt_GcNewFromStrFlag(const char* str,long flags)
{
	long val=str_to_int(str);
	return GrInt_GcNewFlag(val,flags);
}

/*
GrString* GrInt_ToGrString(GrInt* gi)
{
	TODO("Transate GrInt Object To GrString Object");
	GrMem_ALLOC_INT_ERR;
	return NULL;
}
*/

static GrObject* int_mul(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Mul(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}
static GrObject* int_div(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Div(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}
static GrObject* int_mod(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Mod(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}

static GrObject* int_plus(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Plus(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}

static GrObject* int_minus(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Minus(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}

static GrObject* int_lshift(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_LShift(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}

static GrObject* int_rshift(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_RShift(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}
static GrObject* int_and(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_And(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}
static GrObject* int_or(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Or(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}

static GrObject* int_xor(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return (GrObject*)GrInt_Xor(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_OPS_NOT_SUPPORT;
}

static int int_cmp(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return GrInt_Cmp(GR_TO_I(l),GR_TO_I(r));
	}
	return GR_CMP_NOT_SUPPORT;
}

static int int_rich_eq(GrObject* l,GrObject* r)
{
	if(GrInt_Verify(r))
	{
		return GR_TO_I(l)->i_value==GR_TO_I(r)->i_value;
	}
	return GR_CMP_NOT_SUPPORT;
}



static struct gr_operator_ops int_operator_ops=
{
	.t_negative=(GrUnaryFunc)GrInt_Negative,
	.t_positive=(GrUnaryFunc)GrInt_Positive,
	.t_negated=(GrUnaryFunc)GrInt_Negated,

	.t_mul=int_mul,
	.t_div=int_div,
	.t_mod=int_mod,

	.t_plus=int_plus,
	.t_minus=int_minus,

	.t_lshift=int_lshift,
	.t_rshift=int_rshift,

	.t_and=int_and,
	.t_xor=int_xor,
	.t_or=int_or,

	.t_cmp=int_cmp,

	.t_bool=(GrBoolFunc)GrInt_Bool,
};

static struct gr_type_ops int_type_ops=
{
	.t_operator=&int_operator_ops,
	.t_hash=(GrHashFunc)GrInt_Hash,
	.t_print=(GrPrintFunc)GrInt_Print,
	.t_rich_eq=int_rich_eq,
};

struct gr_type_info Gr_Type_Int=
{
	//.t_class=Gr_Int_Class;
	.t_name="IntObject",
	.t_size=sizeof(GrInt),
	.t_ops=&int_type_ops,
};


static struct gr_type_ops bool_type_ops=
{
	.t_operator=&int_operator_ops,
	.t_hash=(GrHashFunc)GrInt_Hash,
	.t_print=(GrPrintFunc)GrBool_Print,
	.t_rich_eq=int_rich_eq,
};
struct gr_type_info Gr_Type_Bool=
{
	.t_name="BoolObject",
	.t_size=sizeof(GrInt),
	.t_ops=&bool_type_ops,
};


GrInt* Gr_False=0;
GrInt* Gr_True=0;

int GrModule_IntInit()
{
	Gr_False=GrGc_AllocStatic(GrInt,&Gr_Type_Bool);
	if(Gr_False==NULL) return -1;
	Gr_False->i_value=0;

	Gr_True=GrGc_AllocStatic(GrInt,&Gr_Type_Bool);
	if(Gr_True==NULL) return -1;
	Gr_True->i_value=1;

	return 0;
}



int GrModule_IntExit()
{
	return 0;
}







