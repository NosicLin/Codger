#ifndef _REDY_RTYPE_RTYPE_H_
#define _REDY_RTYPE_RTYPE_H_

#include<assert.h>
#include"except_msg.h"
#include<object/robject.h>
#include<object/type_object.h>
#include<rstd/redy_std.h>



#define RT_UNKOWN  TYPE_UNKOWN
#define RT_INT TYPE_INT
#define RT_FLOAT TYPE_FLOAT
#define RT_LONG TYPE_LONG
#define RT_STRING TYPE_STRING 
#define RT_ARRAY TYPE_ARRAY 
#define RT_ITER TYPE_ITER 


static inline int rt_type(Robject* rt)
{
	return rt->r_type->t_type;
}

#define RTYPE_DEBUG

void rt_raise_type_error(char* msg);
void rt_raise_div_zero(char* msg);
void rt_raise_overflow(char* msg);
void rt_raise_value_error(char* msg );
void rt_raise_index_error(char* msg );


void except_divzero_err_format(const char* s,...);
void except_type_err_format(const char* s,...);

#endif /*_REDY_RTYPE_RTYPE_H_*/
