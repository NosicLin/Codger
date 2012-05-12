#ifndef _CODGER_OBJECT_ROBJECT_H_
#define _CODGER_OBJECT_ROBJECT_H_
#include<stdio.h>
#include<assert.h>
#include<memory/gc.h>
struct gr_type_info;

struct  gr_object 
{

#ifdef GRGC_DEBUG
	GRGC_HEADER ;
#endif 

	union{
		/* keep pointer at least align 4, 
		 * so the lower two bit can used for garbage collection 
		 */
		struct gr_type_info* g_type;
		struct 
		{
			/* @g_ref_low: if object come from high level area reference 
			 * low level object,this bit will mark
			 */
			long g_ref_low:1;  

			/* @g_upgrade: an object alloc from young area,when garbage 
			 * collection works,if it still alive,this bit will mark, and 
			 * the next time garbage collection works again,if it then 
			 * alive,it will be upgrade to old area */
			long g_upgrade:1;
			long g_reverse:30;
		};
	};
};
typedef struct gr_object GrObject;

#include"type_info.h"

#define INHERIT_GROBJECT struct gr_object g_base 
#define TO_GROBJECT(x) ((GrObject*)x)

#define GR_TYPE_ADDR_MASK (~((1ul<<2)-1))
static inline GrTypeInfo* GrObject_Type(GrObject* gr)
{
	return (GrTypeInfo*)((size_t)(gr->g_type)&GR_TYPE_ADDR_MASK);
}

#define GR_CMP_NOT_SUPPORT -2
extern GrObject* GR_OPS_NOT_SUPPORT;
extern struct gr_type_ops GR_TYPE_OPS_NOT_SUPPORT;
	
const char* GrObject_Name(GrObject*);
int GrObject_Cmp(GrObject*,GrObject*,int op);
int GrObject_RichEq(GrObject*,GrObject*);
ssize_t GrObject_Hash(GrObject*);

#define GR_PRINT_SPACE 0x1l
#define GR_PRINT_TAB (0x1l<<1)
#define GR_PRINT_NEWLINE (0x1l<<2)
int GrObject_Print(GrObject*,FILE*,long);

GrObject* GrObject_Positive(GrObject*);
GrObject* GrObject_Negative(GrObject*);
GrObject* GrObject_Negated(GrObject*);
GrObject* GrObject_Mul(GrObject* ,GrObject*);
GrObject* GrObject_Div(GrObject* ,GrObject*);
GrObject* GrObject_Mod(GrObject* ,GrObject*);
GrObject* GrObject_Plus(GrObject* ,GrObject*);
GrObject* GrObject_Minus(GrObject* ,GrObject*);
GrObject* GrObject_LShift(GrObject* ,GrObject*);
GrObject* GrObject_RShift(GrObject* ,GrObject*);
GrObject* GrObject_And(GrObject* ,GrObject*);
GrObject* GrObject_Xor(GrObject* ,GrObject*);
GrObject* GrObject_Or(GrObject* ,GrObject*);
int GrObject_Lt(GrObject*,GrObject*);
int GrObject_Le(GrObject*,GrObject*);
int GrObject_Ge(GrObject*,GrObject*);
int GrObject_Gt(GrObject*,GrObject*);
int GrObject_Eq(GrObject*,GrObject*);
int GrObject_Ne(GrObject*,GrObject*);
int GrObject_Bool(GrObject*);

GrObject* GrObject_GetItem(GrObject*,GrObject*);
int GrObject_SetItem(GrObject*,GrObject*,GrObject*);

GrObject* GrObject_Iter(GrObject*);
GrObject* GrObject_IterNext(GrObject*);

GrObject* GrObject_Call(GrObject*,GrObject*,GrObject*);

GrObject* GrObject_GetAttr(GrObject*,GrObject*,long);

int GrObject_SetAttr(GrObject*,GrObject*,GrObject*,long);

#endif /*_CODGER_OBJECT_ROBJECT_H_*/




