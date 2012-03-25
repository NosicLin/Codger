#ifndef _REDY_RTYPE_ROBJECT_H_
#define _REDY_RTYPE_ROBJECT_H_

/*Robject short for Redy Object*/
struct robject_ops;
struct rexpr_ops;

struct  robject 
{
	int r_ref;
	int r_type;
	char* r_name;
	struct robject_ops* r_ops;
	struct rexpr_ops* r_expr_ops;
};

typedef struct robject Robject;

struct rexpr_ops
{
	/*posifix operator '[]' */
	Robject* (*ro_get_item)(Robject*,Robject* );
	void (*ro_set_item)(Robject*,Robject* index,Robject* item);

	/* unary operator + and - */
	Robject* (*ro_negative)(Robject* );
	Robject* (*ro_positive)(Robject* );

	/*multiply(*), divide(/) ,mod(%)*/
	Robject* (*ro_mul)(Robject* ,Robject*);
	Robject* (*ro_div)(Robject* ,Robject*);
	Robject* (*ro_mod)(Robject* ,Robject*);

	/*plus (+) and minus(-)*/
	Robject* (*ro_plus)(Robject*, Robject*);
	Robject* (*ro_minus)(Robject* ,Robject*);

	/* left shift(<<) and right shift(>>) */
	Robject* (*ro_lshift)(Robject* , Robject*);
	Robject* (*ro_rshift)(Robject* , Robject*);

	/* less than(lt <), less equal(le <=) */
	Robject* (*ro_lt)(Robject* ,Robject*);
	Robject* (*ro_le)(Robject* ,Robject*);

	/* equal (==), not equal(ne !=)*/
	Robject* (*ro_eq)(Robject* ,Robject*);
	Robject* (*ro_ne)(Robject* ,Robject*);

	/* greater than( gt,>), greater equal (ge, <=)*/
	Robject* (*ro_gt)(Robject* ,Robject*);
	Robject* (*ro_ge)(Robject* ,Robject*);

	/* cmp a short method for lt,le,eq,gt,ge */
	Robject* (*ro_cmp)(Robject* ,Robject*);

	/*bit_and(&), bit_or(|) bit_xor(^) bit_negated*/
	Robject* (*ro_bit_and)(Robject*,Robject*);
	Robject* (*ro_bit_or)(Robject* ,Robject*);
	Robject* (*ro_bit_xor)(Robject*,Robject*);
	Robject* (*ro_bit_negated)(Robject*);

	/*logic and ,logic_or */
	Robject* (*ro_bool)(Robject*);

	/*used for print sentence */
	void (*ro_print)(Robject*);

	/*get iterator */
	Robject* (*ro_iterator)(Robject*);
};


struct robject_ops 
{
	void (*ro_free)(Robject*);
};

extern Robject* robject_null;
extern Robject* robject_other;

/*create and free*/
Robject* robject_create();

static inline void robject_free(Robject* rt)
{
	rt->r_ops->ro_free(rt);
}

/* init */
static inline void robject_init(Robject* rt,int type)
{
	rt->r_type=type;
}

/*reference and release*/
static inline void robject_addref(Robject* rt)
{
	rt->r_ref++;
}
static inline void robject_release(Robject* rt)
{
	rt->r_ref--;
	if(rt->r_ref==0)
	{
		robject_free(rt);
	}
}

/* interface */
static inline int rt_type(Robject* rt)
{
	return rt->r_type;
}

static inline char* robject_name(Robject* rt)
{
	return rt->r_name;
}

/* robject expr */
void robject_print(Robject* rt);
/*unary expr*/
Robject* robject_positive(Robject* r);
Robject* robject_negative(Robject* r);
Robject* robject_bit_negated(Robject* r);
/*binary expr*/

/*multiply_expr*/
Robject* robject_mul(Robject* left,Robject* right);
Robject* robject_div(Robject* left,Robject* right);
Robject* robject_mod(Robject* left,Robject* right);

/*additive_expr*/
Robject* robject_plus(Robject* left,Robject* right);
Robject* robject_minus(Robject* left,Robject* right);

/*shift_expr*/
Robject* robject_lshift(Robject* left,Robject* right);
Robject* robject_rshift(Robject* left,Robject* right);

/*relational_expr*/
Robject* robject_lt(Robject* left,Robject* right);
Robject* robject_le(Robject* left,Robject* right);
Robject* robject_gt(Robject* left,Robject* right);
Robject* robject_ge(Robject* left,Robject* right);

/*equal_expr*/
Robject* robject_ne(Robject* left,Robject* right);
Robject* robject_eq(Robject* left,Robject* right);

/*bitwise_expr*/
Robject* robject_bit_or(Robject* left,Robject* right);
Robject* robject_bit_and(Robject* left,Robject* right);
Robject* robject_bit_xor(Robject* left,Robject* right);

/*logic_expr*/
Robject* robject_bool(Robject* rt);
#endif 

