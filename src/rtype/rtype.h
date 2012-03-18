#ifndef _REDY_RTYPE_RTYPE_H_
#define _REDY_RTYPE_RTYPE_H_

#include"bt_int.h"
#include"bt_boolean.h"
#include"bt_float.h"
#include"bt_long.h"
#include"bt_string.h"
#include"bt_array.h"
#include"bt_common.h"
#include<assert.h>
#include"except_msg.h"
#include"robject.h"

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
#define RTYPE_DEBUG 1

#if RTYPE_DEBUG 

/* int */
static inline BtInt* R_TO_I(Robject* rt)
{
	assert(rt->r_type==RT_INT);
	return (BtInt*) rt;
}

static inline Robject* I_TO_R(BtInt* bt)
{
	assert(((Robject*)bt)->r_type==RT_INT);
	return (Robject*)bt;
}

/* float */
static inline BtFloat* R_TO_F(Robject* rt)
{
	assert(rt_type(rt)==RT_FLOAT);
	return (BtFloat*)rt;
}
static inline Robject* F_TO_R(BtFloat* bt)
{
	assert(rt_type((Robject*)bt)==RT_FLOAT);
	return (Robject*)bt;
}

/*long */
static inline BtLong* R_TO_L(Robject* rt)
{	
	assert(rt_type(rt)==RT_LONG);
	return (BtLong*)rt;
}
static inline Robject* L_TO_R(BtLong* bt)
{
	assert(rt_type((Robject*)bt)==RT_LONG);
	return (Robject*)bt;
}

/* string */
static inline BtString* R_TO_S(Robject* rt)
{
	assert(rt_type(rt)==RT_STRING);
	return (BtString*) rt;
}
static inline Robject* S_TO_R(BtString* bt)
{
	assert(rt_type((Robject*)bt)==RT_STRING);
	return (Robject*)bt;
}

/*array*/
static inline BtArray* R_TO_A(Robject* rt)
{
	assert(rt_type(rt)==RT_ARRAY);
	return (BtArray*) rt;
}
static inline Robject* A_TO_R(BtArray* bt)
{
	assert(rt_type((Robject*)bt)==RT_ARRAY);
	return (Robject*)bt;
}
#else 

#define R_TO_I(rt) ((BtInt*)rt)
#define	I_TO_R(rti) ((Robject*) rti)

#define R_TO_F(rt) ((BtFloat*)rt)
#define	F_TO_R(rtf) ((Robject*) rtf)

#define R_TO_L(bt) ((BtLong*)bt)
#define L_TO_R(btl) ((Robject*)btl)

#define R_TO_S(bt) ((BtString*)bt)
#define S_TO_R(btl) ((Robject*)btl)

#define R_TO_A(bt) ((BtArray*)bt)
#define A_TO_R(btl) ((Robject*)btl)

#endif 


void rt_raise_type_error(char* msg);
void rt_raise_div_zero(char* msg);
void rt_raise_overflow(char* msg);
void rt_raise_value_error(char* msg );
void rt_raise_index_error(char* msg );

#endif /*_REDY_RTYPE_RTYPE_H_*/
