#ifndef _CODGER_OBJECT_GR_INT_H_
#define _CODGER_OBJECT_GR_INT_H_
#include"gr_object.h"
#include"assert.h"
#define GR_INT_DEBUG
struct  gr_int
{
	INHERIT_GROBJECT;
	long i_value;
};
typedef struct gr_int  GrInt;


extern struct gr_type_info Gr_Type_Int;
extern struct gr_type_info Gr_Type_Bool;

/* boolean is a specific type of GrInt */
extern GrInt* Gr_False;
extern GrInt* Gr_True;





/* all return value memory come from gc, you can't free it 
 *
 * if you want to manager memory by you self,please use Gr_Alloc(size_t) 
 * interface to alloc memory for int object,and init value use 
 * GrInt_Init(GrInt*,long value) interface.
 *
 * remember that memory from Gr_Alloc can't interactive with codger
 * system,if do that it will crash the system.
 *
 * make sure memory come from Gr_Alloc only used for object internal data 
 * or temporary compute. it will never access from out side,
 * 
 */
GrInt* GrInt_GcNew(long value);
GrInt* GrInt_GcNewFlag(long value,long flags);

GrInt* GrInt_GcNewFromStr(const char* str);
GrInt* GrInt_GcNewFromStrFlag(const char* str,long flags);

void GrInt_Init(GrInt*,long value);

static inline long GrInt_GetValue(GrInt* gi);

/* type cast */
/*
struct gr_string* GrInt_ToGrString(GrInt*);
struct gr_long* GrInt_ToGrLong(GrInt*);
*/

GrInt* GrInt_GetAttr(GrInt*,GrObject*);
GrInt* GrInt_SetAttr(GrInt*,GrObject*,GrObject*);

static inline GrInt* GrInt_Positive(GrInt*);
static inline GrInt* GrInt_Negative(GrInt*);
static inline GrInt* GrInt_Negated(GrInt*);

static inline GrInt* GrInt_Mul(GrInt*,GrInt*);
static inline GrInt* GrInt_Div(GrInt*,GrInt*);
static inline GrInt* GrInt_Mod(GrInt*,GrInt*);
static inline GrInt* GrInt_Plus(GrInt*,GrInt*);
static inline GrInt* GrInt_Minus(GrInt*,GrInt*);

static inline GrInt* GrInt_LShift(GrInt*,GrInt*);
static inline GrInt* GrInt_RShift(GrInt*,GrInt*);
static inline GrInt* GrInt_And(GrInt*,GrInt*);
static inline GrInt* GrInt_Xor(GrInt*,GrInt*);
static inline GrInt* GrInt_Or(GrInt*,GrInt*);

static inline int GrInt_Cmp(GrInt*,GrInt*);
static inline int GrInt_Bool(GrInt*);

static inline int GrInt_Print(GrInt*,FILE* f);

static inline ssize_t GrInt_Hash(GrInt*);
static inline int GrInt_Verify(GrObject*);
static inline int GrBool_Print(GrInt*,FILE* f);
#include"gr_int.inl"



#ifdef GR_INT_DEBUG
static inline GrObject*  I_TO_GR(GrInt* gi)
{
	return (GrObject*)gi;
}
static inline GrInt* GR_TO_I(GrObject* gr)
{
	assert(GrInt_Verify(gr));
	return (GrInt*)gr;
}
#else 
#define GR_TO_I(x) ((GrInt*)(x))
#define I_TO_GR(x) ((GrObject*)(x))
#endif /*GR_INT_DEBUG*/


int GrModule_IntInit();
int GrModule_IntExit();

#endif /*_CODGER_OBJECT_GR_INT_H_*/

