#include"gr_float.h"
#include<memory/gc.h>
#include<engine/except.h>
#include"gr_int.h"
#include<memory/gc.h>
#include<memory/memory.h>
#include<utility_c/marocs.h>
#include<string.h>
#include"gr_class.h"
#include"gr_consts.h"
#include"gr_array.h"
#include"gr_util.h"

GrFloat* GrFloat_GcNew(float value)
{
	GrFloat* ret=GrGc_New(GrFloat,&Gr_Type_Float);
	if(ret==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For FloatObject");
		return NULL;
	}
	ret->f_value=value;
	return ret;
}

GrFloat* GrFloat_GcNewFlag(float value,long flags)
{
	GrFloat* ret=GrGc_Alloc(GrFloat,&Gr_Type_Float,flags);
	if(ret==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For FloatObject");
		return NULL;
	}
	ret->f_value=value;
	return ret;
}


GrFloat* GrFloat_GcNewFromStr(const char* str)
{
	GrFloat* ret=GrGc_New(GrFloat,&Gr_Type_Float);
	if(ret==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For FloatObject");
		return NULL;
	}
	float value=atof(str);
	ret->f_value=value;
	return  ret;
}

GrFloat* GrFloat_GcNewFromStrFlag(const char* str,long flags)
{
	GrFloat* ret=GrGc_Alloc(GrFloat,&Gr_Type_Float,flags);
	if(ret==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For FloatObject");
		return NULL;
	}
	float value=atof(str);
	ret->f_value=value;
	return  ret;
}

struct gr_int* GrFloat_ToGrInt(GrFloat* gf)
{
	return GrInt_GcNew(gf->f_value);
}

struct gr_float* GrFloat_ToGrFloat(GrFloat* gf)
{
	return gf;
}

struct gr_string* GrFloat_ToGrString(GrFloat* gf)
{
	char buf[100];
	sprintf(buf,"%g",gf->f_value);
	return GrString_GcNew(buf);
}



static GrObject* float_mul(GrObject* x,GrObject* y)
{
	float x_val,y_val;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_OPS_NOT_SUPPORT;
	}
	return (GrObject*)GrFloat_GcNew(x_val*y_val);
}

#define float_mul_reverse float_mul

static GrObject* float_div(GrObject* x,GrObject* y)
{
	float x_val,y_val;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_OPS_NOT_SUPPORT;
	}
	if(y_val==0.0)
	{
		GrErr_DiveZeroFormat("Float Object Div Or Mod Zero");
		return NULL;
	}
	return (GrObject*)GrFloat_GcNew(x_val/y_val);
}

static GrObject* float_div_reverse(GrObject* x,GrObject* y)
{
	float x_val,y_val;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_OPS_NOT_SUPPORT;
	}
	if(x_val==0.0)
	{
		GrErr_DiveZeroFormat("Float Object Div Or Mod Zero");
		return NULL;
	}
	return (GrObject*)GrFloat_GcNew(y_val/x_val);
}

static GrObject* float_plus(GrObject* x,GrObject* y)
{
	float x_val,y_val;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_OPS_NOT_SUPPORT;
	}
	return (GrObject*)GrFloat_GcNew(x_val+y_val);
}
#define float_plus_reverse float_plus 

static GrObject* float_minus(GrObject* x,GrObject* y)
{
	float x_val,y_val;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_OPS_NOT_SUPPORT;
	}
	return (GrObject*)GrFloat_GcNew(x_val-y_val);
}

static GrObject* float_minus_reverse(GrObject* x,GrObject* y)
{
	float x_val,y_val;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_OPS_NOT_SUPPORT;
	}
	return (GrObject*)GrFloat_GcNew(y_val-x_val);
}

static int float_cmp(GrObject* x,GrObject* y)
{
	float x_val,y_val,diff;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_CMP_NOT_SUPPORT;
	}

	diff=x_val-y_val;
	return diff<0?-1:diff==0?0:1;
}


static int float_cmp_reverse(GrObject* x,GrObject* y)
{
	float x_val,y_val,diff;
	
	x_val=GR_TO_F(x)->f_value;
	if(GrFloat_Verify(y))
	{
		y_val=GR_TO_F(y)->f_value;
	}
	else if(GrInt_Verify(y))
	{
		y_val=GR_TO_I(y)->i_value;
	}
	else 
	{
		return GR_CMP_NOT_SUPPORT;
	}

	diff=y_val-x_val;
	return diff<0?-1:diff==0?0:1;
}

static struct gr_type_ops float_type_ops=
{
	.t_hash=(GrHashFunc)GrFloat_Hash,
	.t_print=(GrPrintFunc)GrFloat_Print,

	.t_get_attr=GrUtil_BaseTypeGetAttr,
	.t_set_attr=GrUtil_BaseTypeSetAttr,

	.t_negative=(GrUnaryFunc)GrFloat_Negative,
	.t_positive=(GrUnaryFunc)GrFloat_Positive,
	
	.t_mul=float_mul,
	.t_div=float_div,

	.t_plus=float_plus,
	.t_minus=float_minus,

	.t_cmp=float_cmp,

	/* reverse op */
	.t_mul_reverse=float_mul_reverse,
	.t_div_reverse=float_div_reverse,
	.t_plus_reverse=float_plus_reverse,
	.t_minus_reverse=float_minus_reverse,
	.t_cmp_reverse=float_cmp_reverse,

	.t_to_float=(GrCastFunc)GrFloat_ToGrFloat,
	.t_to_int=(GrCastFunc)GrFloat_ToGrInt,
	.t_to_string=(GrCastFunc)GrFloat_ToGrString,
};
	
struct gr_type_info Gr_Type_Float=
{
	.t_class=NULL, /* Update Later */
	.t_name="FloatObject",
	.t_size=sizeof(GrFloat),
	.t_ops=&float_type_ops,
};


int GrModule_FloatInit()
{

	Gr_Type_Float.t_class=NULL;
	GrClass* c=GrFloat_GetFloatClass();
	if(c==NULL) return -1;

	Gr_Type_Float.t_class=c;
	return 0;
}


int GrModule_FloatExit()
{
	return 0;
}


/* float class */

GrObject* GrFloat_MethodNegative(GrObject* host,GrArray* args)
{
	if(!GrFloat_Verify(host))
	{
		return Gr_Object_Nil;
	}
	return (GrObject*) GrFloat_Negative((GrFloat*)host);
}
GrObject* GrFloat_MethodPositive(GrObject* host,GrArray* args)
{
	if(!GrFloat_Verify(host))
	{
		return Gr_Object_Nil;
	}
	return (GrObject*) GrFloat_Positive((GrFloat*)host);
}

GrObject* GrFloat_MethodMul(GrObject* host,GrArray* args)
{
	if(!GrFloat_Verify(host))
	{
		return Gr_Object_Nil;
	}
	GrObject* right=GrArray_Get(args,0);
	assert(right);
	return float_mul(host,right);
}

GrObject* GrFloat_MethodDiv(GrObject* host,GrArray* args)
{
	if(!GrFloat_Verify(host))
	{
		return Gr_Object_Nil;
	}
	GrObject* right=GrArray_Get(args,0);
	assert(right);
	return float_div(host,right);
}

GrObject* GrFloat_MethodPlus(GrObject* host,GrArray* args)
{
	if(!GrFloat_Verify(host))
	{
		return Gr_Object_Nil;
	}
	GrObject* right=GrArray_Get(args,0);
	assert(right);
	return float_plus(host,right);
}

GrObject* GrFloat_MethodMinus(GrObject* host,GrArray* args)
{
	if(!GrFloat_Verify(host))
	{
		return Gr_Object_Nil;
	}
	GrObject* right=GrArray_Get(args,0);
	assert(right);
	return float_minus(host,right);
}

static GrInnerFuncEntry s_float_method[]=
{
	{
		.e_name="pos",
		.e_permission=0,
		.e_func=GrFloat_MethodPositive,
		.e_arg_nu=0,
	},
	{
		.e_name="neg",
		.e_permission=0,
		.e_func=GrFloat_MethodNegative,
		.e_arg_nu=0,
	},
	{
		.e_name="mul",
		.e_permission=0,
		.e_func=GrFloat_MethodMul,
		.e_arg_nu=1,
	},
	{
		.e_name="div",
		.e_permission=0,
		.e_func=GrFloat_MethodDiv,
		.e_arg_nu=1,
	},
	{
		.e_name="add",
		.e_permission=0,
		.e_func=GrFloat_MethodPlus,
		.e_arg_nu=1,
	},
	{
		.e_name="sub",
		.e_permission=0,
		.e_func=GrFloat_MethodMinus,
		.e_arg_nu=1,
	},
	{
		.e_name=NULL,
	},
};


GrClass* GrFloat_GetFloatClass()
{
	if(Gr_Type_Float.t_class!=NULL)
	{
		return Gr_Type_Float.t_class;
	}

	GrClass* float_class=GrClass_GcNewFlag(GrGc_HEAP_STATIC);
	if(float_class==NULL)
	{
		return NULL;
	}
	GrString* name=GrString_GcNewFlag("FloatClass",GrGc_HEAP_STATIC);
	if(name==NULL)
	{
		return NULL;
	}

	GrClass_SetName(float_class,name);
	int ret=GrUtil_FillInnerMethodsFlag(float_class->c_template,
			s_float_method,GrGc_HEAP_STATIC);

	if(ret<0) return NULL;

	Gr_Type_Float.t_class=float_class;
	return float_class;
}









