#ifndef _CODGER_OBJECT_STRING_H_
#define _CODGER_OBJECT_STRING_H_

#include"gr_object.h"

struct gr_string
{
	INHERIT_GROBJECT;
	ssize_t s_length;
	ssize_t s_hash;
	char* s_value;
};

typedef struct gr_string GrString;

extern GrTypeInfo Gr_Type_String;

GrString* GrString_GcNew(const char*);
GrString* GrString_GcNewFlag(const char*,long flags);

GrString* GrString_GcNewEscWithQuote(const char*);


int GrString_Init(GrString* ,const char*);
int GrString_InitEscWithQuote(GrString*,const char*);


GrString* GrString_ToGrString(GrString*);


GrString* GrString_Get(GrString*,ssize_t );
GrString* GrString_Plus(GrString*,GrString*);



int GrString_Cmp(GrString* ,GrString*);

int GrString_Bool(GrString*);
int GrString_Hash(GrString*);
int GrString_Print(GrString*,FILE* f);

static inline int GrString_Verify(GrObject* g)
{
	return GrObject_Type(g)==&Gr_Type_String;
}
	

struct gr_class;
int GrModule_StringInit();
int GrModule_StringExit();
struct gr_class* GrString_GetStringClass();

#ifdef GR_STRING_DEBUG
static inline GrString* GR_TO_S(GrObject* g)
{
	assert(GrString_Verify(g));
	return (GrString*)g;
}
static inline GrObject* S_TO_GR(GrString* gs)
{
	return (GrObject*)gs;
}
#else 

#define  GR_TO_S(x) ((GrString*)(x))
#define  S_TO_GR(x) ((GrObject*)(x))

#endif  /*GR_STRING_DEBUG*/

#endif  /*_CODGER_OBJECT_STRING_H_*/






