#ifndef _REDY_RTYPE_FLOAT_H_
#define _REDY_RTYPE_FLOAT_H_
#include<object/robject.h>
#include<rstd/redy_std.h>
#include"rtype.h"
struct bt_float
{
	INHERIT_ROBJECT;
	float f_value;
};
typedef struct bt_float BtFloat;

/* type cast*/
#ifdef RTYPE_DEBUG
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
#else 
#define R_TO_F(rt) ((BtFloat*)rt)
#define	F_TO_R(rtf) ((Robject*) rtf)
#endif /*RTYPE_DEBUG*/


/* default constructor*/
BtFloat* btfloat_create(float value);
BtFloat* btfloat_from_str(char* str);

/*destructor*/
static inline void bt_float_free(BtFloat* btf)
{
	ry_free(btf);
}

static inline int bt_float_is_zero(BtFloat* bf)
{
	return bf->f_value==0;
}

/*setter and getter */
static inline float bt_float_get(BtFloat* bf)
{
	return bf->f_value;
}
static inline void bt_float_set(BtFloat* bf,float value)
{
	bf->f_value=value;
}

struct bt_int;
struct bt_long;
struct bt_string;

struct bt_int* btfloat_to_btint(BtFloat* bf);
struct bt_string* btfloat_to_btstring(BtFloat* bf);
struct bt_long* btfloat_to_btlong(BtFloat* bf);
/* expr */
/*unary expr*/
static inline BtFloat* btfloat_positive(BtFloat* bf)
{
	robject_addref(F_TO_R(bf));
	return bf;
}
static inline BtFloat* btfloat_negative(BtFloat* bf)
{
	float value=-bf->f_value;
	return btfloat_create(value);
}
/*arithmetic expr*/
static inline BtFloat* btfloat_mul(BtFloat* x,BtFloat* y)
{
	float value=x->f_value*y->f_value;
	return btfloat_create(value);
}


BtFloat* btfloat_div(BtFloat* x,BtFloat* y);
BtFloat* btfloat_mod(BtFloat* x,BtFloat* y);

static inline BtFloat* btfloat_plus(BtFloat* x,BtFloat* y)
{
	float value=x->f_value+y->f_value;
	return btfloat_create(value);
}

static inline BtFloat* btfloat_minus(BtFloat* x,BtFloat* y)
{
	float value=x->f_value-y->f_value;
	return btfloat_create(value);
}
/*compare expr*/

static inline int btfloat_lt(BtFloat* x,BtFloat* y)
{
	return x->f_value<y->f_value;
}
static inline int btfloat_le(BtFloat* x,BtFloat* y)
{
	return x->f_value<=y->f_value;
}
static inline int btfloat_eq(BtFloat* x,BtFloat* y)
{
	return x->f_value==y->f_value;
}
static inline int btfloat_ne(BtFloat* x,BtFloat* y)
{
	return x->f_value!=y->f_value;
}
static inline int btfloat_ge(BtFloat* x,BtFloat* y)
{
	return x->f_value>=y->f_value;
}
static inline int btfloat_gt(BtFloat* x,BtFloat* y)
{
	return x->f_value>y->f_value;
}

int btfloat_cmp(BtFloat* x,BtFloat* y,int op);


/*logic expr*/
static inline int btfloat_bool(BtFloat* bf)
{
	return bf->f_value!=0;
}

/*hash code*/
ssize_t btfloat_hash(BtFloat* bf);

/* print */
int btfloat_print(BtFloat* bf,FILE* f,int flags);

#endif /*_REDY_RTYPE_FLOAT_H_*/
