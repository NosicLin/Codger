#ifndef _CODGER_OBJECT_CONST_H_
#define _CODGER_OBJECT_CONST_H_
#include"gr_object.h"

/* string const */
extern GrObject* Gr_Const_String_lambda;
extern GrObject* Gr_Const_String_this;
extern GrObject* Gr_Const_String_mul;
extern GrObject* Gr_Const_String_div;
extern GrObject* Gr_Const_String_mod;
extern GrObject* Gr_Const_String_add;
extern GrObject* Gr_Const_String_sub;
extern GrObject* Gr_Const_String_lshift;
extern GrObject* Gr_Const_String_rshift;
extern GrObject* Gr_Const_String_and;
extern GrObject* Gr_Const_String_xor;
extern GrObject* Gr_Const_String_or;
extern GrObject* Gr_Const_String_get_attr;
extern GrObject* Gr_Const_String_set_attr;
extern GrObject* Gr_Const_String_set_item;
extern GrObject* Gr_Const_String_get_item;
extern GrObject* Gr_Const_String_iter;
extern GrObject* Gr_Const_String_iter_next;



extern GrObject* Gr_False;
extern GrObject* Gr_True;
extern GrObject* Gr_Object_Nil;

/* used for class */

extern GrObject* Gr_Object_Class;

extern GrObject* Gr_Int_Class;
extern GrObject* Gr_Float_Class;
extern GrObject* Gr_Long_Class;
extern GrObject* Gr_String_Class;
extern GrObject* Gr_Array_Class;



int GrModule_ConstsInit();
int GrModule_ConstsExit();
#endif


