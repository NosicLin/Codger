#include<syntax/parser.h>
#include<syntax/yylex.h>
#include<object/gr_module.h>
#include<object/gr_opcode.h>
#include<object/gr_consts.h>
#include<memory/memory.h>
#include<memory/gc.h>
#include"eg_thread.h"
#include"eg_sframe.h"

int main(int argc,char** argv)
{


	GrModule_MemInit();
	GrModule_GcInit();
	GrModule_ConstsInit();

	Scanner* sc=0;
	AstObject* root=0;
	GrModule* module=0;
	GrString* module_name=0;
	int ret=0;
	if(argc!=2)
	{
		fprintf(stderr,"usage %s <filename>\n",argv[0]);
		exit(-1);
	}
	sc=sc_create(argv[1]);
	if(sc==NULL)
	{
		fprintf(stderr,"Open file %s failed\n",argv[1]);
		exit(-1);
	}
	yl_set_scanner(sc);
	ret=yyparse();
	if(ret!=0)
	{
		fprintf(stderr,"parser <%s> failed\n",argv[1]);
		goto error;
	}

	AstPending_Clear();
	root=parser_get_root();
	
	module=Ast_ToModule(root);
	module_name=GrString_GcNew("main");
	if(module==NULL||module_name==NULL)
	{
		goto error;
	}
	GrModule_SetName(module,module_name);

	EgThread* thread=EgThread_New();
	if(thread==NULL) goto error;

	EgSframe* sf=EgSframe_NewFromModule(module);
	if(sf==NULL) goto error;

	EgThread_PushSframe(thread,sf);
	sf=NULL;

	EgThread_Run(thread);

error:
	if(root) AstTree_Free(root);
	if(sc) sc_destory(sc);
	if(thread) EgThread_Delete(thread);
	return 0;
}
