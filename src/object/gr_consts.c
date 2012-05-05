#include"gr_consts.h"
#include<memory/gc.h>
#include"gr_string.h"
#include"gr_int.h"

GrObject* Gr_Const_S_Lambda=0;
GrObject* Gr_Const_S_This=0;
GrObject* Gr_False=0;
GrObject* Gr_True=0;

int GrModule_ConstsInit()
{
	Gr_Const_S_Lambda=(GrObject*)GrString_GcNewFlag("#lambda",GRGC_HEAP_STATIC);
	if(Gr_Const_S_Lambda==NULL) return -1;

	Gr_Const_S_This=(GrObject*)GrString_GcNewFlag("This",GRGC_HEAP_STATIC);
	if(Gr_Const_S_This==NULL) return -1;

	Gr_False=(GrObject*)GrGc_AllocStatic(GrInt,&Gr_Type_Bool);
	if(Gr_False==NULL) return -1;
	GR_TO_I(Gr_False)->i_value=0;

	Gr_True=(GrObject*)GrGc_AllocStatic(GrInt,&Gr_Type_Bool);
	if(Gr_True==NULL) return -1;
	GR_TO_I(Gr_True)->i_value=1;

	return 0;
}


int GrModule_ConstExit()
{
	return 0;
}
