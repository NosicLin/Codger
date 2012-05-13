#ifndef _CODGER_ENGINE_ENGINE_H_
#define _CODGER_ENGINE_ENGINE_H_
#include<utility_c/list_head.h>
#include"eg_sframe.h"
#include<object/gr_object.h>
#define EG_THREAD_EXIT_NORMAL 0x1l
#define EG_THREAD_EXIT_EXCEPTION (0x1l<<1)

#define EG_THREAD_FLAGS_EXCEPTION_HAPPED (0x1l)
#define EG_THREAD_FLAGS_FRAME_CHANGE (0x1l<<1)
struct eg_thread
{
	struct list_head t_link;
	EgSframe* t_fstack;

	long t_flags;

	size_t t_dstack_cap;
	GrObject** t_dstack;
	GrObject* t_host;
	size_t t_sp;
	size_t t_pc;


	GrObject* t_relval;
};

typedef struct eg_thread EgThread;

EgThread* EgThread_New();
int EgThread_Delete(EgThread*);

//int EgThread_Run(EgThread*);
int EgThread_PushSframe(EgThread*,EgSframe*);

EgSframe* EgThread_PopSframe(EgThread* );
int EgThread_Run(EgThread*);
void EgThread_SFrameReturn(EgThread* eg);

EgThread* EgThread_GetSelf();

#define EG_THREAD_SET_FLAGS(eg,flags) eg->t_flags|=flags
#define EG_THREAD_HAS_FLAGS(eg,flags) (eg->t_flags&(flags))
#define EG_THREAD_CLR_FLAGS(eg,flags) eg->t_flags&=(~(flags))

#endif /*_CODGER_ENGINE_ENGINE_H_*/

