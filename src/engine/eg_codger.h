#ifndef _CODGER_ENGINE_EG_CODGER_H_
#define _CODGER_ENGINE_EG_CODGER_H_

#include"eg_thread.h"

int EgCodger_Run();
int EgCodger_SchedulThread(EgThread* eg,long flags);
int EgCodger_TheadState(EgThread* eg);
int EgCodger_StopThread(EgThread* eg);
int EgCodger_PauseThread(EgThread* eg);
int EgCodger_StartThread(EgThread* eg);


#endif /*_CODGER_ENGINE_EG_CODGER_H_*/

