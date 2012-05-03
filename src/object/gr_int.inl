#ifndef GR_OBJECT_GR_INT_INL_
#define GR_OBJECT_GR_INT_INL_
#include<engine/except.h>
#include<stdio.h>
static inline GrInt* GrInt_Positive(GrInt* gi)
{
	return gi;
}
static inline GrInt* GrInt_Negative(GrInt* gi)
{
	long val=-gi->i_value;
	return GrInt_GcNew(val);

}
static inline GrInt* GrInt_Negated(GrInt* gi)
{
	long val=~gi->i_value;
	return GrInt_GcNew(val);
}

static inline GrInt* GrInt_Mul(GrInt* l,GrInt* r)
{
	long val=l->i_value*r->i_value;
	return GrInt_GcNew(val);
}



static inline GrInt* GrInt_Div(GrInt* l,GrInt* r)
{
	if(r->i_value==0)
	{
		GrErr_DiveZeroFormat("Int Object Div Zero");
		return NULL;
	}
	long val=l->i_value/r->i_value;
	return GrInt_GcNew(val);
}

static inline GrInt* GrInt_Mod(GrInt* l,GrInt* r)
{
	if(r->i_value==0)
	{
		GrErr_DiveZeroFormat("Int Object Div Zero");
		return NULL;
	}
	long val=l->i_value%r->i_value;
	return GrInt_GcNew(val);
}
static inline GrInt* GrInt_Plus(GrInt* l,GrInt* r)
{
	long val=l->i_value+r->i_value;
	return GrInt_GcNew(val);
}
static inline GrInt* GrInt_Minus(GrInt* l,GrInt* r)
{
	long val=l->i_value-r->i_value;
	return GrInt_GcNew(val);
}

static inline GrInt* GrInt_LShift(GrInt* l ,GrInt* r)
{
	if(r->i_value<0)
	{
		GrErr_NegitiveShift("Int Object Left Shift With Negative Num");
		return NULL;
	}
	long val=l->i_value<<r->i_value;
	return GrInt_GcNew(val);
}

static inline GrInt* GrInt_RShift(GrInt* l,GrInt* r)
{
	if(r->i_value<0)
	{
		GrErr_NegitiveShift("Int Object Right Shift With Negative Num");
		return NULL;
	}
	long val=l->i_value>>r->i_value;
	return GrInt_GcNew(val);
}
static inline GrInt* GrInt_And(GrInt* l,GrInt* r)
{
	long val=l->i_value&r->i_value;
	return GrInt_GcNew(val);
}

static inline GrInt* GrInt_Xor(GrInt* l,GrInt* r)
{
	long val=l->i_value^r->i_value;
	return GrInt_GcNew(val);
}
static inline GrInt* GrInt_Or(GrInt* l,GrInt* r)
{
	long val=l->i_value|r->i_value;
	return GrInt_GcNew(val);
}

static inline int GrInt_Cmp(GrInt* l,GrInt* r)
{
	long l_val=l->i_value;
	long r_val=r->i_value;

	long diff=l_val-r_val;

	return diff<0?-1:diff==0?0:1;
}

static inline int GrInt_Bool(GrInt* gi)
{
	return gi->i_value!=0;
}

static inline int GrInt_Print(GrInt* gi,FILE* f)
{
	fprintf(f,"%ld",gi->i_value);
	return 0;
}
static inline int GrBool_Print(GrInt* gi,FILE* f)
{
	if(gi->i_value!=0)
	{
		fprintf(f,"%s","True");
	}
	else
	{
		fprintf(f,"%s","False");
	}
	return 0;
}

static inline ssize_t GrInt_Hash(GrInt* gi)
{
	return gi->i_value==-1?-2:gi->i_value;
}

static inline int GrInt_Verify(GrObject* gr)
{
	GrTypeInfo* type=GrObject_Type(gr);
	if(type==&Gr_Type_Int||type==&Gr_Type_Bool)
	{
		return 1;
	}
	return 0;
}

static inline long GrInt_GetValue(GrInt* gi)
{
	return gi->i_value;
}

#endif 
