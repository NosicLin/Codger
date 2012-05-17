#include"eg_buildin.h"
#include<object/gr_array.h>
#include<memory/gc.h>
#include<memory/memory.h>
#include"except.h"
#include<utility_c/marocs.h>
#include<object/gr_int.h>
#include<object/gr_consts.h>
#include<object/gr_util.h>
#include<object/gr_class.h>
#include<object/gr_object.h>
static GrHash* s_buildin=NULL;



GrObject* buildin_float(GrObject* host,GrArray* args)
{
	GrObject* item=GrArray_Get(args,0);
	assert(item);
	return GrObject_ToGrFloat(item);
}

GrObject* buildin_int(GrObject* host,GrArray* args)
{
	GrObject* item=GrArray_Get(args,0);
	assert(item);
	return GrObject_ToGrInt(item);
}

GrObject* buildin_string(GrObject* host,GrArray* args)
{
	GrObject* item=GrArray_Get(args,0);
	assert(item);
	return GrObject_ToGrString(item);
}

GrObject* buildin_array(GrObject* host,GrArray* args)
{
	GrObject* item=GrArray_Get(args,0);
	assert(item);
	GrInt* num=(GrInt*)GrObject_ToGrInt(item);
	if(num==NULL)
	{
		return NULL;
	}
	assert(GrInt_Verify((GrObject*)num));
	if(num->i_value<0)
	{
		GrErr_ValueFormat("Create ArrayObject With Negative Value");
		return NULL;
	}
	return (GrObject*)GrArray_GcNewWithSize(num->i_value);
}
GrObject* buildin_hash(GrObject* host,GrArray* args)
{
	return (GrObject*)GrHash_GcNew();
}

static GrInnerFuncEntry s_buildin_func[]=
{
	{
		.e_name="Int",
		.e_permission=0,
		.e_func=buildin_int,
		.e_arg_nu=1,
	},
	{
		.e_name="Float",
		.e_permission=0,
		.e_func=buildin_float,
		.e_arg_nu=1,
	},
	{
		.e_name="String",
		.e_permission=0,
		.e_func=buildin_string,
		.e_arg_nu=1,
	},
	{
		.e_name="Array",
		.e_permission=0,
		.e_func=buildin_array,
		.e_arg_nu=1,
	},
	{
		.e_name="Hash",
		.e_permission=0,
		.e_func=buildin_hash,
		.e_arg_nu=0,
	},
	{
		.e_name=NULL,
	},
};


int GrModule_BuildinInit()
{
	s_buildin=GrHash_GcNewFlag(GRGC_HEAP_STATIC);
	if(s_buildin==NULL)
	{
		return -1;
	}
	return GrUtil_FillWithGrString(s_buildin,s_buildin_func,
			GRGC_HEAP_STATIC);
}
int GrModule_BuildinExit()
{
	s_buildin=0;
	return 0;
}

int EgCodger_BuildinAdd(GrObject* k,GrObject* v)
{
	return GrHash_Map(s_buildin,k,v);
}

GrHash* EgCodger_GetBuildin()
{
	return s_buildin;
}









