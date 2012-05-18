#ifndef _CODGER_ENGINE_STACK_FRAME_H_
#define _CODGER_ENGINE_STACK_FRAME_H_

#include<object/gr_scope.h>
#include<object/gr_opcode.h>
#include<object/gr_module.h>
#include<object/gr_func.h>

struct eg_thread;
struct  eg_sframe
{
	struct eg_sframe* f_link;
	struct eg_thread* f_thread;
	GrScope* f_scope;
	GrOpcode* f_codes;

	GrObject* f_host;
	size_t f_pc;
	size_t f_sp;

	GrObject* f_relval;
};

typedef struct eg_sframe EgSframe;

EgSframe* EgSframe_NewFromFunc(GrFunc*);
EgSframe* EgSframe_NewFromModule(GrModule*);
void EgSframe_Free(EgSframe* );

int EgsFrame_ClearCache();
int GrModule_EgSframeInit();
int GrModule_EgSframeEixt();




#endif /*_CODGER_ENGINE_STACK_FRAME_H_*/
