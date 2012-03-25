#include "robject.h"
#include<utility_c/marocs.h>
#include"rtype.h"

static void null_object_free(Robject*  rt)
{
	BUG("NUll Obejct Shouldn't Be Free");
}

static struct robject_ops null_object_ops=
{
	.ro_free=null_object_free,
};
void null_print(Robject* r)
{
	BUG_ON(r->r_type!=RT_NULL,"Error Robject");
	printf("Null");
}
static struct rexpr_ops null_expr_ops=
{
	.ro_print=null_print,
};
static struct robject __robject_null=
{
	.r_ref=1,
	.r_type=RT_NULL,
	.r_name="NULL",
	.r_ops=&null_object_ops,
	.r_expr_ops=&null_expr_ops,
};

struct robject* robject_null= &__robject_null;

static struct robject __robject_other=
{
	.r_ref=1,
	.r_type=RT_OTHER,
	.r_name="OTHER",
	.r_ops=&null_object_ops,
	.r_expr_ops=0,
};

struct robject* robject_other= &__robject_other;

void robject_print(Robject* rt)
{
	if(!rt->r_expr_ops)
	{
		goto default_action;
	}
	if(!rt->r_expr_ops->ro_print)
	{
		goto default_action;
	}

	rt->r_expr_ops->ro_print(rt);
	printf("\n");
	return ;
default_action:
	printf("Object At %ld\n",(long)rt);
	return ;

}

/*unary expr*/
#define UNARY_OPERATOR(Hl,Ll) \
Robject* robject_##Ll(Robject* r) \
{ \
	if(r->r_expr_ops==0) \
	{ \
		goto default_action; \
	}  \
	if(r->r_expr_ops->ro_##Ll==0) \
	{ \
		goto default_action; \
	} \
	Robject* ret=0; \
	ret=r->r_expr_ops->ro_##Ll(r); \
	return ret; \
default_action: \
	rt_raise_type_error(MSG_UEXPR(robject_name(r),OPER_##Hl)); \
	robject_addref(robject_null); \
	return robject_null; \
}
UNARY_OPERATOR(POSITIVE,positive);
UNARY_OPERATOR(NEGATIVE,negative);
UNARY_OPERATOR(NEGATED,bit_negated);

/*binary expr*/
#define BINARY_OPERATOR(Hl,Ll) \
Robject* robject_##Ll(Robject* left,Robject* right) \
{ \
	if(left->r_expr_ops==0) \
	{ \
		goto default_action; \
	} \
	if(left->r_expr_ops->ro_##Ll==0) \
	{ \
		goto default_action; \
	} \
	Robject* ret=0; \
	ret=left->r_expr_ops->ro_##Ll(left,right); \
	return ret; \
default_action: \
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_##Hl)); \
	robject_addref(robject_null); \
	return robject_null; \
}

/*multiply_oper*/
BINARY_OPERATOR(MUL,mul);
BINARY_OPERATOR(DIV,div);
BINARY_OPERATOR(MOD,mod);

/*addtive_expr*/
BINARY_OPERATOR(PLUS,plus);
BINARY_OPERATOR(MINUS,minus);

/*shift_expr*/
BINARY_OPERATOR(LSHIFT,lshift);
BINARY_OPERATOR(RSHIFT,rshift);

/*bitwise_expr*/
BINARY_OPERATOR(BIT_AND,bit_and);
BINARY_OPERATOR(BIT_XOR,bit_xor);
BINARY_OPERATOR(BIT_OR,bit_or);


#define COMPARE_OPERATOR(Hl,Ll,op)  \
Robject* robject_##Ll(Robject* left,Robject* right) \
{ \
	Robject* ret=0; \
	if(left->r_expr_ops==0) \
	{ \
		goto default_action; \
	} \
	if(left->r_expr_ops->ro_##Ll) \
	{ \
		ret=left->r_expr_ops->ro_##Ll(left,right); \
		goto over; \
	} \
	if(ret==0) \
	{ \
		if(left->r_expr_ops->ro_cmp) \
		{ \
			ret=left->r_expr_ops->ro_cmp(left,right); \
			if(rt_type(ret)==RT_INT) \
			{ \
				int value=bt_int_get(R_TO_I(ret)); \
				robject_release(ret); \
				if(value op 0) \
				{ \
					ret=B_TO_R(bt_boolean_create(1)); \
				} \
				else \
				{ \
					ret=B_TO_R(bt_boolean_create(0)); \
				} \
			} \
			return ret; \
		} \
	} \
default_action: \
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_LT)); \
	robject_addref(robject_null); \
	return robject_null; \
over: \
	return ret; \
}

COMPARE_OPERATOR(LT,lt,<);
COMPARE_OPERATOR(LE,le,<=);
COMPARE_OPERATOR(GT,gt,>);
COMPARE_OPERATOR(GE,ge,>=);
COMPARE_OPERATOR(EQ,eq,==);
COMPARE_OPERATOR(NE,ne,!=);


/*logic expr*/
Robject* robject_bool(Robject* rt)
{
	Robject* ret=0;
	if(rt->r_expr_ops==0)
	{
		goto default_action;
	}
	if(rt->r_expr_ops->ro_bool==0)
	{
		goto default_action;
	}
	ret=rt->r_expr_ops->ro_bool(rt);
	return ret;
default_action:
	ret=B_TO_R(bt_boolean_create(1));
	return ret;
}



