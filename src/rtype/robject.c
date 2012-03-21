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

static struct robject __robject_null=
{
	.r_ref=1,
	.r_type=RT_NULL,
	.r_name="NULL",
	.r_ops=&null_object_ops,
	.r_expr_ops=0,
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
	if(left->r_expr_ops->ro_mul==0)
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
	if(left->r_expr_ops->ro_mul==0)
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






