#ifndef _CODGER_OBJECT_GR_FLOAT_INL_
#define _CODGER_OBJECT_GR_FLOAT_INL_
#include"gr_float.h"
#include<engine/except.h>
static inline float GrFloat_GetValue(GrFloat* gf)
{
	return gf->f_value;
}

static inline GrFloat* GrFloat_Positive(GrFloat* gf)
{
	return gf;
}

static inline GrFloat* GrFloat_Negative(GrFloat* gf)
{
	float val=-gf->f_value;
	return GrFloat_GcNew(val);
}

static inline GrFloat* GrFloat_Mul(GrFloat* x,GrFloat* y)
{
	float x_val=x->f_value;
	float y_val=y->f_value;
	return GrFloat_GcNew(x_val*y_val);
}
static inline GrFloat* GrFloat_Div(GrFloat* x,GrFloat* y)
{
	float x_val=x->f_value;
	float y_val=y->f_value;
	if(y_val==0)
	{
		GrErr_DiveZeroFormat("FloatObject Div Or Mod Zero");
		return NULL;
	}

	return GrFloat_GcNew(x_val/y_val);
}

/*
 * TODO float mod not support yet
static inline GrFloat* GrFloat_Mod(GrFloat* x,GrFloat* y)
{
	float x_val=x->f_value;
	float y_val=y->f_value;
	if(y_val==0)
	{
		GrErr_DivZeroFormat("FloatObject Div Or Mod Zero");
		return NULL;
	}

	return GrFloat_GcNew(x_val%y_val);
}
*/

static inline GrFloat* GrFloat_Plus(GrFloat* x,GrFloat* y)
{
	float x_val=x->f_value;
	float y_val=y->f_value;
	return GrFloat_GcNew(x_val+y_val);
}
static inline GrFloat* GrFloat_Minus(GrFloat* x,GrFloat* y)
{
	float x_val=x->f_value;
	float y_val=y->f_value;
	return GrFloat_GcNew(x_val-y_val);
}

static inline int  GrFloat_Cmp(GrFloat* x,GrFloat* y)
{
	float x_val=x->f_value;
	float y_val=y->f_value;
	float diff=x_val-y_val;
	return diff<0?-1:diff==0?0:1;
}

static inline int GrFloat_Bool(GrFloat* gf)
{
	return gf->f_value!=0.0;
}

static inline int GrFloat_Print(GrFloat* gf,FILE* f)
{
	fprintf(f,"%g",gf->f_value);
	return 0;
}

static inline ssize_t GrFloat_Hash(GrFloat* gf)
{
	union 
	{
		float f;
		ssize_t u;
	} val;
	val.f=gf->f_value;

	if(val.u==-1) val.u=-2;
	return val.u;
}



static inline int GrFloat_Verify(GrObject* g)
{
	return GrObject_Type(g)==&Gr_Type_Float;
}

#endif /*_CODGER_OBJECT_GR_FLOAT_INL_*/

