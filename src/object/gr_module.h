#ifndef _CODGER_OBJECT_MODULE_OBJECT_H_
#define _CODGER_OBJECT_MODULE_OBJECT_H_

#include"gr_object.h"
#include"gr_hash.h"
#include"gr_opcode.h"
#include"gr_array.h"
#include"gr_string.h"

#include<assert.h>

#define GR_MODULE_MAP_ERR 0xfffffffful

struct gr_module
{
	INHERIT_GROBJECT;

	GrArray* m_consts_pool;
	GrArray* m_symbols_pool;
	GrArray* m_opcode_pool;

	GrString* m_name;
	GrHash* m_attrs;

	GrOpcode* m_codes;
};

typedef struct gr_module GrModule;

extern GrTypeInfo  Gr_Type_Module;

GrModule* GrModule_GcNew();
GrModule* GrModule_GcNewFlag(long);

int GrModule_Init(GrModule* );

u_int32_t GrModule_MapOpcode(GrModule*,GrOpcode*);
u_int32_t GrModule_MapConst(GrModule*,GrObject*);
u_int32_t GrModule_MapSymbol(GrModule*,GrObject*);


int GrModule_SetName(GrModule*,GrString*);
int GrModule_SetOpcode(GrModule*,GrOpcode*);
GrString* GrModule_GetName(GrModule*);


int GrModule_WriteToFile(GrModule* m,FILE* f,long);



#endif 


