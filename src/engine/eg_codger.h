#ifndef _CODGER_ENGINE_EG_CODGER_H_
#define _CODGER_ENGINE_EG_CODGER_H_

#include"eg_thread.h"
#include<object/gr_module.h>
#include<object/gr_string.h>

int EgCodger_Run();
int EgCodger_SchedulThread(EgThread* eg,long flags);
int EgCodger_TheadState(EgThread* eg);
int EgCodger_StopThread(EgThread* eg);
int EgCodger_PauseThread(EgThread* eg);
int EgCodger_StartThread(EgThread* eg);

GrModule* EgCodger_ParseFile(const char* file_name);
GrModule* EgCodger_ImportModule(GrString* name);
int EgCodger_AddModule(GrModule* module);




int EgCodger_ModuleInit();
int EgCodger_ModuleExit();

#endif /*_CODGER_ENGINE_EG_CODGER_H_*/

