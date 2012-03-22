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
Robject* robject_positive(Robject* r)
{
	if(r->r_expr_ops==0)
	{
		goto default_action;
	}
	if(r->r_expr_ops->ro_positive==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=r->r_expr_ops->ro_positive(r);
	return ret;
default_action:
	rt_raise_type_error(MSG_UEXPR(robject_name(r),OPER_POSITIVE));
	robject_addref(robject_null);
	return robject_null;
}


Robject* robject_negative(Robject* r)
{
	if(r->r_expr_ops==0)
	{
		goto default_action;
	}
	if(r->r_expr_ops->ro_negative==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=r->r_expr_ops->ro_negative(r);
	return ret;
default_action:
	rt_raise_type_error(MSG_UEXPR(robject_name(r),OPER_NEGATIVE));
	robject_addref(robject_null);
	return robject_null;
}

Robject* robject_bit_negated(Robject* r)
{
	if(r->r_expr_ops==0)
	{
		goto default_action;
	}
	if(r->r_expr_ops->ro_bit_negated==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=r->r_expr_ops->ro_bit_negated(r);
	return ret;
default_action:
	rt_raise_type_error(MSG_UEXPR(robject_name(r),OPER_NEGATED));
	robject_addref(robject_null);
	return robject_null;
}


/*binary expr*/
Robject* robject_mul(Robject* left,Robject* right)
{
	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_mul==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_mul(left,right);
	return ret;

default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MUL));
	robject_addref(robject_null);
	return robject_null;
}


Robject* robject_div(Robject* left,Robject* right)
{
	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_div==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_div(left,right);
	return ret;

default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_DIV));
	robject_addref(robject_null);
	return robject_null;
}

Robject* robject_mod(Robject* left,Robject* right)
{
	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_mod==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_mod(left,right);
	return ret;

default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MOD));
	robject_addref(robject_null);
	return robject_null;
}
/* additive_expr*/
Robject* robject_plus(Robject* left,Robject* right)
{

	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_plus==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_plus(left,right);
	return ret;
default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_PLUS));
	robject_addref(robject_null);
	return robject_null;
}

Robject* robject_minus(Robject* left,Robject* right)
{

	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_minus==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_minus(left,right);
	return ret;
default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MINUS));
	robject_addref(robject_null);
	return robject_null;
}

/* shift_expr */

Robject* robject_lshift(Robject* left,Robject* right)
{

	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_lshift==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_lshift(left,right);
	return ret;
default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_LSHIFT));
	robject_addref(robject_null);
	return robject_null;
}

Robject* robject_rshift(Robject* left,Robject* right)
{

	if(left->r_expr_ops==0)
	{
		goto default_action;
	}
	if(left->r_expr_ops->ro_rshift==0)
	{
		goto default_action;
	}
	Robject* ret=0;
	ret=left->r_expr_ops->ro_rshift(left,right);
	return ret;
default_action:
	rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_LSHIFT));
	robject_addref(robject_null);
	return robject_null;
}


