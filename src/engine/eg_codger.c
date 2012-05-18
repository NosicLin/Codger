#include<string.h>
#include"eg_codger.h"
#include"eg_thread.h"
#include<syntax/parser.h>
#include<syntax/yylex.h>
#include"except.h"
#include<object/gr_module.h>
#include<object/gr_opcode.h>
#include<object/gr_consts.h>
#include<memory/memory.h>
#include<memory/gc.h>
#include"eg_thread.h"
#include"eg_sframe.h"
#include"object/gr_int.h"
#include"object/gr_float.h"
#include"object/gr_array.h"
#include"object/gr_string.h"
#include<memory/mem_base.h>
#include"eg_buildin.h"
#include<extends/ex_math.h>


static GrHash* s_modules=NULL;


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

GrModule* EgCodger_ParseFile(const char* file_name)
{
	int ret;
	AstObject* root=NULL;
	Scanner* sc=NULL;

	GrModule* module=NULL;
	GrString* name=NULL;


	sc=sc_create((char*)file_name);
	if(sc==NULL)
	{
		GrErr_ParseFormat("Can't Open File %s",file_name);
		goto error;
	}
	yl_set_scanner(sc);
	ret=yyparse();
	if(ret!=0)
	{
		GrErr_ParseFormat("Parse File %s Failed(ret=%d)",file_name,ret);
		goto error;
	}
	AstPending_Clear();
	root=parser_get_root();
	module=Ast_ToModule(root);

	int length=strlen(file_name);
	char* module_name=GrMem_Alloc(length+1);
	if(module_name==NULL) goto error;
	memcpy(module_name,file_name,length+1);
	if(length>3)
	{
		if(strcmp(module_name+length-3,".gr")==0)
		{
			module_name[length-3]='\0';
		}
	}
	name=GrString_GcNewFlag(module_name,GRGC_HEAP_STATIC);
	GrMem_Free(module_name);

	if(module==NULL||name==NULL)
	{
		goto error;
	}
	GrModule_SetName(module,name);

	AstTree_Free(root);
	sc_destory(sc);
	return module;
error:
	if(root) AstTree_Free(root);
	if(sc) sc_destory(sc);
	return NULL;
}

int EgCodger_AddModule(GrModule* module)
{
	int ret;
	GrString* name=module->m_name;
	assert(name);
	ret=GrHash_Map(s_modules,(GrObject*)name,(GrObject*)module);
	return ret;
}
	



GrModule* EgCodger_ImportModule(GrString* name)
{
	/* if module already load,just check out */
	GrHashEntry* entry=GrHash_GetEntry(s_modules,(GrObject*)name);
	if(GrHashEntry_Valid(entry))
	{
		return (GrModule*)(entry->e_value);
	}

	/* module not load, load it and init it's data */
	/* FIXME buf file may be overflow*/
	char file_name[1024];

	sprintf(file_name,"%s.gr",name->s_value);

	GrModule* module=EgCodger_ParseFile(file_name);

	EgSframe* sf=NULL;
	EgThread* thread=EgThread_GetSelf();
	assert(thread);

	if(module==NULL)
	{
		return NULL;
	}

	/* create a stack frame for module to run */
	sf=EgSframe_NewFromModule(module);
	if(sf==NULL)
	{
		return NULL;
	}

	/* set module return value */
	sf->f_relval=(GrObject*)module;
	EgThread_PushSframe(thread,sf);
	EgCodger_AddModule(module);
	return module;
}

int eg_codger_init()
{
	s_modules=GrHash_GcNewFlag(GRGC_HEAP_STATIC);
	if(s_modules==NULL)
	{
		return -1;
	}
	return 0;
}
int eg_codger_exit()
{
	s_modules=NULL;
	return 0;
}

int EgCodger_ModuleInit()
{
	int ret;

	ret=GrModule_MemInit()<0;
	if(ret<0) goto mem_failed;

	ret=GrModule_GcInit();
	if(ret<0) goto gc_failed;

	ret=GrModule_IntInit();
	if(ret<0) goto int_failed;

	ret=GrModule_FloatInit();
	if(ret<0) goto float_failed;

	ret=GrModule_StringInit();
	if(ret<0) goto string_failed;

	ret=GrModule_ArrayInit();
	if(ret<0) goto array_failed;

	ret=GrModule_ConstsInit();
	if(ret<0) goto const_failed;

	ret=GrModule_BuildinInit();
	if(ret<0) goto buildin_failed;

	ret=eg_codger_init();
	if(ret<0) goto s_modules_falied;

	ret=ExMath_Init();
	if(ret<0) goto s_math_failed;
	return 0;

s_math_failed:
	eg_codger_exit();
s_modules_falied:
	GrModule_BuildinExit();
buildin_failed:
	GrModule_ConstsExit();
const_failed:
	GrModule_ArrayExit();
array_failed:
	GrModule_StringExit();
string_failed:
	GrModule_FloatExit();
float_failed:
	GrModule_IntExit();
int_failed:
	GrModule_GcExit();
gc_failed:
	GrModule_MemExit();
mem_failed:
	return -1;
}

int EgCodger_ModuleExit()
{
	eg_codger_exit();
	GrModule_ConstsExit();
	GrModule_ArrayExit();
	GrModule_StringExit();
	GrModule_FloatExit();
	GrModule_IntExit();
	GrModule_GcExit();
	GrModule_MemExit();
	return 0;
}

	









