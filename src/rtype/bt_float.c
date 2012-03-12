#include"rtype.h"

#define R_TO_F(rt) ((BTFloat*)rt)
#define	F_TO_R(rtf) ((Robject*) rtf)

static Robject* bt_float_negative(Robject* rt)
{
	float value=-R_TO_F(rt)->f_value;
	BTFloat* ret=bt_float_create(value);
	return F_TO_R(ret);
}

static Robject* bt_float_positive(Robject* rt)
{
	robject_ref(rt);
	return rt;
}

static Robject* bt_float_mul(Robject* left,Robject* right)
{
	if(bt_type(right)==RT_FLOAT)
	{
		float value=R_TO_F(left)->f_value*R_TO_F(right)->f_value;
		BTFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(bt_type(right)==RT_INT)
	{
		return r_mul_float_int(left,right);
	}
	else if(bt_type(right)==RT_LONG)
	{
		return r_mul_float_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for /");
		robject_ref(robject_null)
		return robject_null;
	}
}
static Robject* bt_float_div(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT)
	{
		if(R_TO_F(right)->f_value==0)
		{
			raise_divzero_error("Float Div Zero");
			robject_null->ref();
			return robject_null;
		}
		float value=R_TO_F(left)->f_value/R_TO_F(right)->f_value;
		BTFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_div_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		retuern r_div_float_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand For /");
		robject_ref(robject_null)
		return robject_null;
	}
}



static Robject* bt_float_mod(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT)
	{
		if(R_TO_F(right)->f_value==0)
		{
			raise_divzero_error("Float Div Zero");
			robject_null->ref();
			return robject_null;
		}
		float value=R_TO_F(left)->f_value%R_TO_F(right)->f_value;
		BTFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_mod_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		retuern r_mod_float_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand For /");
		robject_ref(robject_null)
		return robject_null;
	}

}

static Robject* bt_float_plus(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT)
	{
		float value=R_TO_INT(left)->f_value+R_TO_INT(right)->f_value;
		BTFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_plus_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		retuern r_plus_float_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand For +");
		robject_ref(robject_null)
		return robject_null;
	}
}


static Robject* bt_float_minus(Robject* left,Robject* right)
{

	if(rt_type(right)==RT_FLOAT)
	{
		float value=R_TO_INT(left)->f_value-R_TO_INT(right)->f_value;
		BTFloat* ret=bt_float_create(value);
		return F_TO_R(ret);
	}
	else if(rt_type(right)==RT_INT)
	{
		return r_minus_float_int(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		retuern r_minus_float_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand For -");
		robject_ref(robject_null)
		return robject_null;
	}
}

static int bt_float_cmp(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_FLOAT))
	{
		float value==R_TO_F(left)->f_value-R_TO_F(right)->f_value;
		if(value<0)
		{
			return -1;
		}
		else if(value==0)
		{
			return 0;
		}
		else 
		{
			return 1;
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
		raise_type_error("Unsupport Operand for >");
		robject_ref(robject_null)
		return robject_null;
	}

}





static int bt_float_booleaned(Robject* btf)
{
	return  R_TO_F(btf)->f_value==0;
}






static struct rexpr_ops bt_float_expr_ops=
{
	.ro_negative=bt_float_negative,
	.ro_positive=bt_float_positive,

	ro_mul=bt_float_muls,
	ro_div=bt_float_div,
	ro_mod=bt_float_mod,

	ro_plus=bt_float_plus,
	ro_minus=bt_float_minus,

	ro_cmp=bt_float_cmp,

	ro_booleaned=bt_float_booleaned,
};


static void bt_float_free(Robject* bt)
{
	free(R_TO_F(bt));
}

static Robject_ops bt_float_ops=
{
	.ro_free=bt_float_free,
};


static bt_float* bt_float_create(float value)
{
	BTFloat* ret=(BTFloat*)malloc(sizeof(*ret));
	ret->f_value=value;
	Robject* base=ret->f_base;

	base->r_name="Float";
	base->r_expr_ops=&bt_float_expr_ops;
	base->r_type=RT_FLOAT;
	base->r_ops=&bt_float_ops;
	return ret;
}
