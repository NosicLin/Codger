#include"ex_math.h"
#include<object/gr_util.h>
#include<object/gr_inner_func.h>
#include<object/gr_object.h>
#include<object/gr_array.h>
#include<object/gr_float.h>
#include<object/gr_int.h>
#include<object/gr_module.h>
#include<assert.h>
#include<math.h>
#include<engine/eg_codger.h>
#include<stdlib.h>
#include<time.h>

#define MATH_METHOD_ARG1(x) \
	static GrObject* ex_math_##x(GrObject* host,GrArray* args) \
{ \
	GrObject* item=GrArray_Get(args,0); \
	assert(item); \
	GrFloat* value=(GrFloat*)GrObject_ToGrFloat(item); \
	if(value==NULL) \
	{ \
		return NULL; \
	} \
	float ret=x(value->f_value); \
	return (GrObject*)GrFloat_GcNew(ret); \
}

#define MATH_METHOD_ARG2(x) \
	static GrObject* ex_math_##x(GrObject* host,GrArray* args) \
{ \
	GrObject* item1=GrArray_Get(args,0); \
	GrObject* item2=GrArray_Get(args,1); \
	assert(item1); \
	assert(item2); \
	GrFloat* value1=(GrFloat*)GrObject_ToGrFloat(item1); \
	if(value1==NULL) \
	{ \
		return NULL; \
	} \
	GrFloat* value2=(GrFloat*)GrObject_ToGrFloat(item1); \
	if(value2==NULL) \
	{ \
		return NULL; \
	} \
	float ret=x(value1->f_value,value2->f_value); \
	return (GrObject*)GrFloat_GcNew(ret); \
}
#define MATH_FUNC_ENTRY(x,arg_nu) \
{ \
	.e_name=#x, \
	.e_permission=0, \
	.e_func=ex_math_##x, \
	.e_arg_nu=arg_nu, \
}

MATH_METHOD_ARG1(acos);
MATH_METHOD_ARG1(asin);
MATH_METHOD_ARG1(atan);
MATH_METHOD_ARG2(atan2);

MATH_METHOD_ARG1(cos);
MATH_METHOD_ARG1(sin);
MATH_METHOD_ARG1(tan);

MATH_METHOD_ARG1(cosh);
MATH_METHOD_ARG1(sinh);
MATH_METHOD_ARG1(tanh);

MATH_METHOD_ARG1(acosh);
MATH_METHOD_ARG1(asinh);
MATH_METHOD_ARG1(atanh);

MATH_METHOD_ARG1(exp);
//MATH_METHOD_ARG2(frexp);
MATH_METHOD_ARG2(ldexp);
MATH_METHOD_ARG1(log);
MATH_METHOD_ARG1(log10);

//MATH_METHOD_ARG1(exp10);
//MATH_METHOD_ARG1(pow10);

MATH_METHOD_ARG1(expm1);
MATH_METHOD_ARG1(log1p);
MATH_METHOD_ARG1(logb);

MATH_METHOD_ARG1(exp2);
MATH_METHOD_ARG1(log2);

MATH_METHOD_ARG2(pow);
MATH_METHOD_ARG1(sqrt);

MATH_METHOD_ARG1(ceil);
MATH_METHOD_ARG1(fabs);
MATH_METHOD_ARG1(floor);
MATH_METHOD_ARG2(fmod);

static GrObject* ex_math_random()
{
	long val=rand();
	return (GrObject*)GrInt_GcNew(val);
}


static GrInnerFuncEntry s_math_func[]=
{
	MATH_FUNC_ENTRY(acos,1),
	MATH_FUNC_ENTRY(asin,1),
	MATH_FUNC_ENTRY(atan,1),
	MATH_FUNC_ENTRY(atan2,2),

	MATH_FUNC_ENTRY(cos,1),
	MATH_FUNC_ENTRY(sin,1),
	MATH_FUNC_ENTRY(tan,1),

	MATH_FUNC_ENTRY(cosh,1),
	MATH_FUNC_ENTRY(sinh,1),
	MATH_FUNC_ENTRY(tanh,1),

	MATH_FUNC_ENTRY(acosh,1),
	MATH_FUNC_ENTRY(asinh,1),
	MATH_FUNC_ENTRY(atanh,1),

	MATH_FUNC_ENTRY(exp,1),
	//MATH_FUNC_ENTRY(frexp,2),
	MATH_FUNC_ENTRY(ldexp,2),
	MATH_FUNC_ENTRY(log,1),
	MATH_FUNC_ENTRY(log10,1),

	//MATH_FUNC_ENTRY(exp10,1),
	//MATH_FUNC_ENTRY(pow10,1),

	MATH_FUNC_ENTRY(expm1,1),
	MATH_FUNC_ENTRY(log1p,1),
	MATH_FUNC_ENTRY(logb,1),

	MATH_FUNC_ENTRY(exp2,1),
	MATH_FUNC_ENTRY(log2,1),

	MATH_FUNC_ENTRY(pow,1),
	MATH_FUNC_ENTRY(sqrt,1),

	MATH_FUNC_ENTRY(ceil,1),
	MATH_FUNC_ENTRY(fabs,1),
	MATH_FUNC_ENTRY(floor,1),
	MATH_FUNC_ENTRY(fmod,2),
	{
		.e_name="random",
		.e_permission=0,
		.e_func=ex_math_random,
		.e_arg_nu=0,
	},

	{
		.e_name=NULL,
	},
};


int ExMath_Init()
{
	int ret;
	GrModule* m=GrModule_GcNewFlag(GRGC_HEAP_STATIC);
	GrString* name=GrString_GcNewFlag("math",GRGC_HEAP_STATIC);
	if(m==NULL||name==NULL)
	{
		return -1;
	}
	GrModule_SetName(m,name);
	ret=GrUtil_FillWithGrString(m->m_attrs,s_math_func,GRGC_HEAP_STATIC);
	if(ret<0)
	{
		return -1;
	}

	GrString* s_pi=GrString_GcNewFlag("pi",GRGC_HEAP_STATIC);
	if(s_pi==NULL) return -1;

	GrFloat* f_pi=GrFloat_GcNewFlag(3.141592654,GRGC_HEAP_STATIC);
	if(f_pi==NULL) return -1;

	ret=GrHash_Map(m->m_attrs,(GrObject*)s_pi,(GrObject*)f_pi);
	if(ret<0) return -1;


	srand(time(NULL));

	ret=EgCodger_AddModule(m);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int ExMath_Exit()
{
	return 0;
}












