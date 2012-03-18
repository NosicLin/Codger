#include"rtype.h"
#include<utility_c/marocs.h>

/* unary oparator + - */
static Robject* bf_negative(Robject* rt)
{
	float value=-R_TO_F(rt)->f_value;
	BtFloat* ret=bt_float_create(value);
	return F_TO_R(ret);
}

static Robject* bf_positive(Robject* rt)
{
	robject_addref(rt);
	return rt;
}

/* arithmetic operator * /  */
/* float * float =float 
 * float * int =float 
 * float * long =float
 */
static Robject* bf_mul(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT)
	{
		float value=R_TO_F(left)->f_value*R_TO_F(right)->f_value;
		BtFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_mul_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_mul_float_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MUL));
		robject_addref(robject_null);
		return robject_null;
	}
}

/* float / float =Float
 * float / int =float 
 * float / long =float 
 */
static Robject* bf_div(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT)
	{
		if(R_TO_F(right)->f_value==0)
		{
			rt_raise_div_zero(MSG_DIV(robject_name(left)));
			robject_addref(robject_null);
			return robject_null;
		}
		float value=R_TO_F(left)->f_value/R_TO_F(right)->f_value;
		BtFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_div_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_div_float_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_DIV));
		robject_addref(robject_null);
		return robject_null;
	}
}

/*arithmetic  + - */

/* float + float =Float
 * float + int =float 
 * float + long =float 
 */
static Robject* bf_plus(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT)
	{
		float value=R_TO_F(left)->f_value+R_TO_F(right)->f_value;
		BtFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_plus_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_plus_float_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_PLUS));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* float - float =Float
 * float - int =float 
 * float - long =float 
 */
static Robject* bf_minus(Robject* left,Robject* right)
{

	if(rt_type(right)==RT_FLOAT)
	{
		float value=R_TO_F(left)->f_value-R_TO_F(right)->f_value;
		BtFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_minus_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_minus_float_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MINUS));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* cmp operator used for lt le eq ne ge gt */

static Robject* bf_cmp(Robject* left,Robject* right)
{
	int ret=0;
	if(rt_type(right)==RT_FLOAT)
	{
		float value=R_TO_F(left)->f_value-R_TO_F(right)->f_value;
		if(value<0)
		{
			ret=-1;
		}
		else if(value==0)
		{
			ret=0;
		}
		else 
		{
			ret=1;
		}
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_cmp_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_cmp_float_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_CMP));
		robject_addref(robject_null);
		return robject_null;
	}
	BtInt* r=bt_int_create(ret);
	return I_TO_R(r);
}




/* logic operator used for and or not */
static Robject*  bf_bool(Robject* btf)
{
	BtBoolean* ret=NULL;
	float value=R_TO_F(btf)->f_value;
	if(value==0)
	{
		ret=bt_boolean_create(0);
	}
	else
	{
		ret=bt_boolean_create(1);
	}
	return B_TO_R(ret);
}

static void  bf_print(Robject* btf)
{
	printf("%g",R_TO_F(btf)->f_value);
}







static struct rexpr_ops bt_float_expr_ops=
{
	/*unary oparator + - */
	.ro_negative=bf_negative,
	.ro_positive=bf_positive,

	/*arithmetic  * / % */
	.ro_mul=bf_mul,
	.ro_div=bf_div,

	/* arithmetic + -  */
	.ro_plus=bf_plus,
	.ro_minus=bf_minus,

	/* compare operator */
	.ro_cmp=bf_cmp,

	/* logic operator */
	.ro_bool=bf_bool,

	/* print */
	.ro_print=bf_print,

};


static void bf_free(Robject* bt)
{
	free(R_TO_F(bt));
}

static struct robject_ops bt_float_ops=
{
	.ro_free=bf_free,
};


BtFloat* bt_float_malloc()
{
	BtFloat* ret=(BtFloat*)malloc(sizeof(*ret));
	ret->f_value=0.0;
	Robject* base=&ret->f_base;
	base->r_name="Float";
	base->r_expr_ops=&bt_float_expr_ops;
	base->r_type=RT_FLOAT;
	base->r_ops=&bt_float_ops;
	base->r_ref=1;
	return ret;

}

BtFloat* bt_float_create(float value)
{
	BtFloat* ret=bt_float_malloc();
	ret->f_value=value;
	return ret;

}
BtFloat* bt_float_from_str(char* str)
{
	BtFloat* ret=bt_float_malloc();
	float value=atof(str);
	ret->f_value=value;
	return ret;
}

