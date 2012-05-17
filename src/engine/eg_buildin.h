#ifndef _CODGER_ENGINE_BUIDING_IN_H_
#define _CODGER_ENGINE_BUIDING_IN_H_
#include<object/gr_hash.h>
#include<object/gr_object.h>

GrHash* EgCodger_GetBuildin();
int EgCodger_BuildinAdd(GrObject* k,GrObject* v);

int GrModule_BuildinInit();
int GrModule_BuildinExit();
#endif 

