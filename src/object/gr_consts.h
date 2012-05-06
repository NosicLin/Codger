#ifndef _CODGER_OBJECT_CONST_H_
#define _CODGER_OBJECT_CONST_H_
#include"gr_object.h"

extern GrObject* Gr_Const_S_Lambda;
extern GrObject* Gr_Const_S_This;
extern GrObject* Gr_False;
extern GrObject* Gr_True;
extern GrObject* Gr_Object_Nil;

int GrModule_ConstsInit();
int GrModule_ConstsExit();
#endif


