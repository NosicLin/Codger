#ifndef _REDY_RTYPE_INT_H_
#define  _REDY_RTYPE_INT_H_
#include"rtype.h"
/* prefix bt short for base type*/
struct bt_int
{
	INHERIT_ROBJECT;
	int i_value;
};
typedef struct bt_int BtInt;

/* type cast */

#ifdef RTYPE_DEBUG 
static inline BtInt* R_TO_I(Robject* rt)
{
	assert(rt_type(rt)==RT_INT);
	return (BtInt*) rt;
}

static inline Robject* I_TO_R(BtInt* bt)
{
	assert(rt_type((Robject*)bt)==RT_INT);
	return (Robject*)bt;
}
#else 

#define R_TO_I(rt) ((BtInt*)rt)
#define	I_TO_R(rti) ((Robject*) rti)

#endif /*RTYPE_DEBUG*/

/*constructor*/
BtInt* btint_create(int value);
BtInt* btint_from_str(char* str);


/*destructor*/
static inline void btint_free(BtInt* bi) { ry_free(bi); }

/*value getter and setter */
static inline int btint_get(BtInt* bti) { return bti->i_value; }
static inline void btint_set(BtInt* bti,int value) { bti->i_value=value; }

struct bt_long;
struct bt_float;
struct bt_string;

struct bt_long* btint_to_btlong(BtInt* i);
struct bt_float* btint_to_btfloat(BtInt* i);
struct bt_string* btint_to_btstring(BtInt* i);
/* expr */
/*unary expr*/
BtInt* btint_positive(BtInt* bi);
BtInt* btint_negative(BtInt* bi);
BtInt* btint_negated(BtInt* bi);

/*arithmetic expr*/
BtInt* btint_mul(BtInt* x,BtInt* y);
BtInt* btint_div(BtInt* x,BtInt* y);
BtInt* btint_mod(BtInt* x,BtInt* y);
BtInt* btint_plus(BtInt* x,BtInt* y);
BtInt* btint_minus(BtInt* x,BtInt* y);

/*bitwise expr*/
BtInt* btint_lshift(BtInt* x,BtInt* y);
BtInt* btint_rshift(BtInt* x,BtInt* y);
BtInt* btint_or(BtInt* x,BtInt* y);
BtInt* btint_xor(BtInt* x,BtInt* y);
BtInt* btint_and(BtInt* x,BtInt* y);

/*compare expr*/
int btint_lt(BtInt* x,BtInt* y);
int btint_le(BtInt* x,BtInt* y);
int btint_eq(BtInt* x,BtInt* y);
int btint_ne(BtInt* x,BtInt* y);
int btint_ge(BtInt* x,BtInt* y);
int btint_gt(BtInt* x,BtInt* y);
int btint_cmp(BtInt* x,BtInt* y,int op);


/*logic expr*/
int btint_bool(BtInt* bi);

/*hash code*/
ssize_t btint_hash(BtInt* bi);

/* print */
int btint_print(BtInt* bi,FILE* f,int flags);


#endif /*_REDY_RTYPE_INT_H_*/

