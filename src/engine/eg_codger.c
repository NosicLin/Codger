#include"eg_codger.h"
#include"eg_thread.h"


int EgCodger_StartThread(EgThread* eg)
{
	int ret;
	if(eg->t_fstack==NULL)
	{
		return EG_THREAD_EXIT_NORMAL;
	}

	EgThread_RestoreContex(eg,eg->t_fstack);
	ret=EgThread_Run(eg);
	return ret;
}




