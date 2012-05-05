#ifndef _CODGER_ENGINE_ENGINE_H_
#define _CODGER_ENGINE_ENGINE_H_
#include<utility_c/list_head.h>
#include"eg_sframe.h"
#include<object/gr_object.h>
#define EG_THREAD_EXIT_NORMAL 0x1l
#define EG_THREAD_EXIT_EXCEPTION (0x1l<<1)

#define EG_THREAD_FLAGS_EXCEPTION_HAPPED (0x1l)
struct eg_thread
{
	struct list_head t_link;
	EgSframe* t_fstack;

	long t_flags;

	size_t t_dstack_cap;
	GrObject** t_dstack;
	size_t t_sp;
	size_t t_pc;


	EgSframe* t_cur_frame;

	GrModule* t_cur_module;
	GrObject** t_const_pool;
	GrObject** t_symbol_pool;
	GrObject** t_opcode_pool;
	u_int8_t* t_codes;

};

typedef struct eg_thread EgThread;

EgThread* EgThread_New();
int EgThread_Delete(EgThread*);

//int EgThread_Run(EgThread*);
int EgThread_PushSframe(EgThread*,EgSframe*);
int EgThread_RestoreContex(EgThread*,EgSframe*);

int EgThread_Run(EgThread*);



#endif /*_CODGER_ENGINE_ENGINE_H_*/

