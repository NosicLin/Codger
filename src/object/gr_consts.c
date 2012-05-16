#include"gr_consts.h"
#include<memory/gc.h>
#include"gr_string.h"
#include"gr_int.h"
#include<stdio.h>

GrObject* Gr_Const_String_lambda=0;
GrObject* Gr_Const_String_this=0;
GrObject* Gr_Const_String_unkown=0;
GrObject* Gr_Const_String_init=0;
GrObject* Gr_False=0;
GrObject* Gr_True=0;
GrObject* Gr_Object_Nil=0;

int nil_print(GrObject* x,FILE* f)
{
	fprintf(f,"Nil");
	return 0;
}

static struct gr_type_ops nil_type_ops=
{
	.t_print=nil_print,
};

GrTypeInfo Gr_Type_Nil=
{
	.t_name="NilObject",
	.t_ops=&nil_type_ops,
	.t_size=sizeof(GrObject),
};
int GrModule_ConstsInit()
{
	Gr_Const_String_lambda=(GrObject*)GrString_GcNewFlag("#lambda",GRGC_HEAP_STATIC);
	if(Gr_Const_String_lambda==NULL) return -1;

	Gr_Const_String_this=(GrObject*)GrString_GcNewFlag("this",GRGC_HEAP_STATIC);
	if(Gr_Const_String_this==NULL) return -1;

	Gr_Const_String_unkown=(GrObject*)GrString_GcNewFlag("unkown",GRGC_HEAP_STATIC);
	if(Gr_Const_String_unkown==NULL) return -1;

	Gr_Const_String_init=(GrObject*)GrString_GcNewFlag("init",GRGC_HEAP_STATIC);
	if(Gr_Const_String_init==NULL) return -1;

	Gr_False=(GrObject*)GrGc_AllocStatic(GrInt,&Gr_Type_Bool);
	if(Gr_False==NULL) return -1;
	GR_TO_I(Gr_False)->i_value=0;

	Gr_True=(GrObject*)GrGc_AllocStatic(GrInt,&Gr_Type_Bool);
	if(Gr_True==NULL) return -1;
	GR_TO_I(Gr_True)->i_value=1;

	Gr_Object_Nil=GrGc_AllocStatic(GrObject,&Gr_Type_Nil);
	if(Gr_Object_Nil==NULL) return -1;


	return 0;
}


int GrModule_ConstsExit()
{
	return 0;
}

