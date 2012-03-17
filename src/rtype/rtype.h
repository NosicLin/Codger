#ifndef _REDY_RTYPE_RTYPE_H_
#define _REDY_RTYPE_RTYPE_H_

#include"bt_int.h"
#include"bt_boolean.h"
#include"bt_float.h"
#include"bt_long.h"
#include"bt_string.h"
#include"bt_common.h"
#include<assert.h>

enum RTYPE
{
	RT_UNKOWN=0,
	RT_INT,
	RT_FLOAT,
	RT_LONG,
	RT_STRING,
	RT_ITER,
	RT_ARRAY,
	RT_NULL,
	RT_OTHER,
};
#define OPER_MUL "*"
#define OPER_DIV "/"
#define OPER_MOD "%"
#define OPER_PLUS "+"
#define OPER_MINUS "-"
#define OPER_LSHIFT "<<"
#define OPER_RSHIFT ">>"
#define OPER_CMP "cmp"
#define OPER_AND "and"
#define OPER_OR "or"
#define OPER_XOR "xor"

#define RTYPE_DEBUG 1

#if RTYPE_DEBUG 
#define R_TO_I(rt) (assert(rt->r_type==RT_INT),(BtInt*)rt)
#define I_TO_R(bt) (assert(((Robject*)bt)->r_type==RT_INT),(Robject*)bt)

#define R_TO_F(rt) (assert(rt->r_type==RT_FLOAT),(BtFloat*)rt)
#define F_TO_R(bt) (assert(((Robject*)bt)->r_type==RT_FLOAT),(Robject*)bt)

#define R_TO_L(rt) (assert(rt->r_type==RT_LONG),(BtLong*)rt)
#define L_TO_R(bt) (assert(((Robject*)bt)->r_type==RT_LONG),(Robject*)bt)

#else 
#define R_TO_I(rt) ((BtInt*)rt)
#define	I_TO_R(rti) ((Robject*) rti)

#define R_TO_F(rt) ((BtFloat*)rt)
#define	F_TO_R(rtf) ((Robject*) rtf)

#define R_TO_L(bt) ((BtLong*)bt)
#define L_TO_R(btl) ((Robject*)btl)

#endif 

void rt_raise_oper_type_error(Robject* left,Robject* right,char* );

void rt_raise_div_zero(Robject* bt);
void rt_raise_overflow(Robject* bt);
void rt_raise_value_error(char* );

#endif /*_REDY_RTYPE_RTYPE_H_*/
