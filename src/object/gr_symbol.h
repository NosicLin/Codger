#ifndef _CODGER_OBJECT_SYMBOL_H_
#define _CODGER_OBJECT_SYMBOL_H_
#include"gr_object.h"
#include"gr_string.h"

struct gr_symbol
{
	INHERIT_GROBJECT;
	long s_flags;
	GrString* s_name;
};

typedef struct gr_symbol GrSymbol;

extern GrTypeInfo Gr_Type_Symbol;

GrSymbol* GrSymbol_GcNew(GrString* ,long);
GrSymbol* GrSymbol_GcNewFromStr(const char*,long);
GrSymbol* GrSymbol_GcNewFlag(GrString*,long,long);
GrSymbol* GrSymbol_GcNewFlagFromStr(const char*,long,long);

ssize_t GrSymbol_Hash(GrSymbol*);

int GrSymbol_Print(GrSymbol* s,FILE* f);
static inline int GrSymbol_Verify(GrObject* g)
{
	return GrObject_Type(g)==&Gr_Type_Symbol;
}



#endif /*_CODGER_OBJECT_SYMBOL_H_*/

