#ifndef _CODGER_OBJECT_GR_FLOAT_H_
#define _CODGER_OBJECT_GR_FLOAT_H_
#include"gr_object.h"
#include"assert.h"
#define GR_FLOAT_DEBUG

struct gr_float
{
	INHERIT_GROBJECT;
	float f_value;
};
typedef struct gr_float GrFloat;

extern struct gr_type_info Gr_Type_Float;

GrFloat* GrFloat_GcNew(float value);
GrFloat* GrFloat_GcNewFlag(float value,long flags);

GrFloat* GrFloat_GcNewFromStr(const char* str);
GrFloat* GrFloat_GcNewFromStrFlag(const char* str,long flags);


GrFloat* GrFloat_GetAttr(GrFloat*,GrObject*);

static inline float GrFloat_GetValue(GrFloat*);
static inline GrFloat* GrFloat_Positive(GrFloat*);
static inline GrFloat* GrFloat_Negative(GrFloat*);

static inline GrFloat* GrFloat_Mul(GrFloat*,GrFloat*);
static inline GrFloat* GrFloat_Div(GrFloat*,GrFloat*);


static inline GrFloat* GrFloat_Plus(GrFloat*,GrFloat*);
static inline GrFloat* GrFloat_Minus(GrFloat*,GrFloat*);

static inline int  GrFloat_Cmp(GrFloat* ,GrFloat*);
static inline int GrFloat_Bool(GrFloat*);

static inline int GrFloat_Print(GrFloat*,FILE* f);

static inline ssize_t GrFloat_Hash(GrFloat*);
static inline int GrFloat_Verify(GrObject*);

struct gr_class* GrFloat_GetFloatClass();
#include"gr_float.inl"

int GrModule_FloatInit();
int GrModule_FloatExit();

#ifdef GR_FLOAT_DEBUG
static inline GrObject*  F_TO_GR(GrFloat* gi)
{
	return (GrObject*)gi;
}
static inline GrFloat* GR_TO_F(GrObject* gr)
{
	assert(GrFloat_Verify(gr));
	return (GrFloat*)gr;
}
#else 
#define GR_TO_F(x) ((GrFloat*)(x))
#define F_TO_GR(x) ((GrObject*)(x))
#endif /*GR_FLOAT_DEBUG*/

#endif 
