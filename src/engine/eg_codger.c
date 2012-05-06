#include"eg_codger.h"
#include"eg_thread.h"


int EgCodger_StartThread(EgThread* eg)
{
	int ret;
	if(eg->t_fstack==NULL)
	{
		return EG_THREAD_EXIT_NORMAL;
	}

	ret=EgThread_Run(eg);
	return ret;
}




