#ifndef _REDY_RTYPE_ROBJECT_H_
#define _REDY_RTYPE_ROBJECT_H_

/*Robject short for Redy Object*/
typedef struct  robject 
{
	struct robject_ops* r_ops;
	struct rexpr_ops* r_expr_ops;
	int r_ref;
	int r_type;
	char* r_name;
};

typedef struct robject Robject;

struct rexpr_ops
{
	/*posifix operator '()'and '[]' */
	Robject* (*ro_call)(Robject*);
	Robject* (*ro_postfix_get)(Robject*,Robject* );
	Robject* (*ro_postfix_set)(Robject*,Robject*);

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
	/* equal (==) */
	/* greater than( gt,>), greater equal (ge, <=)*/
	Robject* (*ro_lt)(Robject* ,Robject*);
	Robject* (*ro_le)(Robject* ,Robject*);
	Robject* (*ro_equal)(Robject* ,Robject*);
	Robject* (*ro_gt)(Robject* ,Robject*);
	Robject* (*ro_ge)(Robject* ,Robject*);

	/*bit_and(&), bit_or(|) bit_xor(^) */
	Robject* (*ro_bit_and)(Robject*,Robject*);
	Robject* (*ro_bit_or)(Robject* ,Robject*);
	Robject* (*ro_bit_xor)(Robject*,Robject*);

	/*logic and ,logic_or */
	Robject* (*ro_booleaned)(Robject*);

	/*logic not */
	Robject* (*ro_not)(Robject*);
};


struct robjct_ops; 
{
	void (*ro_free)(Robject*);
};



/*create and free*/
Robject* robject_create();

static inline void robject_free(Robject* rt)
{
	return rt->r_ops.ro_free(rt);
}

/* init */
static inline void robject_init(Robject* rt,int type)
{
	rt->r_type=type;
}

/*reference and release*/
static inline void robject_ref(Robject* rt);
{
	rt->r_ref++;
}
static inline void robject_release(Robject* rt);
{
	rt->r_ref--;
	if(rt->r_ref==0)
	{
		rt->r_ops.ro_free(rt);
	}
}

#endif 
