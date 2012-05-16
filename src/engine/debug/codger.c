#include"eg_codger.h"
#include<object/gr_module.h>
#include<stdlib.h>
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		fprintf(stderr,"usage %s <filename>\n",argv[0]);
		exit(-1);
	}

	int ret;
	ret=EgCodger_ModuleInit();
	if(ret<0)
	{
		fprintf(stderr,"Init Codger Module Failed");
		return -1;
	}

	GrModule* module=EgCodger_ParseFile(argv[1]);
	if(module==NULL)
	{
		goto error;
	}

	EgThread* thread=EgThread_New();
	if(thread==NULL) goto error;

	EgSframe* sf=EgSframe_NewFromModule(module);
	if(sf==NULL) goto error;

	EgThread_PushSframe(thread,sf);
	sf=NULL;

	EgThread_Run(thread);

error:
	
	EgCodger_ModuleExit();
	return 0;
}
