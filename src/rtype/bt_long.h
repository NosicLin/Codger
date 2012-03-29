#ifndef _REDY_RTYPE_BT_LONG_H_
#define _REDY_RTYPE_BT_LONG_H_
#include"rtype.h"
#include"big_integer.h"
struct bt_long
{
	INHERIT_ROBJECT;
	struct blg_integer* l_value;
};

typedef struct bt_long BtLong;

#ifdef RTYPE_DEBUG 

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
#else 

#define R_TO_L(bt) ((BtLong*)bt)
#define L_TO_R(btl) ((Robject*)btl)

#endif 


/* constructor */

BtLong* btlong_create(BGInteger* bg);
BtLong* btlong_from_int(int value);
BtLong* btlong_from_str(char* str);

/* deconstructor */
static inline void btlong_free(BtLong* btl)
{
	bg_free(btl->l_value);
	free(btl);
}


static inline int btlong_over_int(BtLong* bl)
{
	return bg_overflow_int(bl->l_value);
}

static inline int btlong_over_float(BtLong* bl);
static inline int btlong_is_zero(BtLong* bl)
{
	return bl->l_value->b_len==0;
}

struct bt_int;
struct bt_float;
struct bt_string;

struct bt_int * btlong_to_btint(BtLong* bl);
struct bt_float* btlong_to_btfloat(Btlong* bl);
struct bt_string* btlong_to_btstring(BtLong* bl);

BtLong* btlong_positive(BtLong* bl);
BtLong* btlong_negative(BtLong* bl);
BtLong* btlong_negated(BtLong* bl);

/*arithmetic expr*/
BtLong* btlong_mul(BtLong* x,BtLong* y);
BtLong* btlong_div(BtLong* x,BtLong* y);
BtLong* btlong_mod(BtLong* x,BtLong* y);
BtLong* btlong_plus(BtLong* x,BtLong* y);
BtLong* btlong_minus(BtLong* x,BtLong* y);

/*bltwise expr*/
BtLong* btlong_lshift(BtLong* x,BtLong* y);
BtLong* btlong_rshift(BtLong* x,BtLong* y);
BtLong* btlong_or(BtLong* x,BtLong* y);
BtLong* btlong_xor(BtLong* x,BtLong* y);
BtLong* btlong_and(BtLong* x,BtLong* y);

/*compare expr*/
int btlong_lt(BtLong* x,BtLong* y);
int btlong_le(BtLong* x,BtLong* y);
int btlong_eq(BtLong* x,BtLong* y);
int btlong_ne(BtLong* x,BtLong* y);
int btlong_ge(BtLong* x,BtLong* y);
int btlong_gt(BtLong* x,BtLong* y);
int btlong_cmp(BtLong* x,BtLong* y,int op);


/*logic expr*/
int btlong_bool(BtLong* bl);

/*hash code*/
ssize_t btlong_hash(BtLong* bl);

/* print */
int btlong_print(BtLong* bl,FILE* f,int flags);
#endif



	
