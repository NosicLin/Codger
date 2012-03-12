#include"rtype.h"

#define R_TO_INT(rt) ((BTInt*)rt)
#define INT_TO_R(bti) ((Robject*)bti)

static Robject* bt_int_negative(Robject* rt)
{
	int value=-R_TO_INT(rt)->i_value;
	BTInt* ret=bt_int_create(value);
	return INT_TO_R(ret);
}

static Robject* bt_int_positive(Robject* rt)
{
	robject_ref(rt);
	return rt;
	
}
static Robject* bt_int_mul(Robject* left,Robject* right)
{
	/* int*int ,eg 1*2*/
	if(bt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value*R_TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}

	/* int*float ,eg 1*1.3*/
	else if(bt_type(right)==RT_FLOAT)
	{
		return r_mul_int_float(left,right);
	}
	/* int*long, eg 2*333l */
	else if(bt_type(RT_LONG))
	{
		return r_mul_int_long(left,right);
	}
	/* int*array, eg 2*[3,4] */
	else
	{
		raise_type_error("Unsupport Operand for *");
		robject_ref(robject_null)
		return robject_null;
	}

};

static Robject* bt_int_div(Robject* left,Robject* right)
{
	/* int div int, eg 1/2 */
	if(rt_type(right)==RT_INT)
	{
		if(R_TO_INT(right)->i_value==0)
		{
			raise_divzero_error("Integer Div Zero");
			robject_null->ref();
			return robject_null;
		}
		int value=R_TO_INT(left)->i_value/TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_div_int_float(left,right);'
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_div_int_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for /");
		robject_ref(robject_null)
		return robject_null;
	}

};

static Robject* bt_int_mod(Robject* left,Robject* right)
{
	/* int div int, eg 1/2 */
	if(rt_type(right)==RT_INT)
	{
		if(R_TO_INT(right)->i_value==0)
		{
			raise_divzero_error("Integer Mod Zero");
			robject_null->ref();
			return robject_null;
		}
		int value=R_TO_INT(left)->i_value%TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_mod_int_float(left,right);'
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_mod_int_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for %");
		robject_ref(robject_null)
		return robject_null;
	}

};
static Robject* bt_int_plus(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value+TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_plus_int_float(left,right);
	}
	else if( rt_type(right)==RT_LONG)
	{
		return r_plus_int_long(left,right);
	}
	else 
	{
		raise_type_error("Unsupport Operand for +");
		robject_ref(robject_null)
		return robject_null;
	}
}

static Robject* bt_int_minus(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value-TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_minus_int_float(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_minus_int_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for -");
		robject_ref(robject_null)
		return robject_null;
	}

}
static Robject* bt_int_lshift(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value<<TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_lshift_int_long(left,right);
	}
	else 
	{
		raise_type_error("Unsupport Operand for <<");
		robject_ref(robject_null)
		return robject_null;
	}
}


static Robject* bt_int_rshift(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value>>TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return INT_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_rshift_int_long(left,right);
	}
	else 
	{
		raise_type_error("Unsupport Operand for <<");
		robject_ref(robject_null)
		return robject_null;
	}
}

static int  bt_int_cmp(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value-TO_INT(right)->i_value;
		return value;
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_cmp_int_float(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_gt_int_long(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for >");
		robject_ref(robject_null)
		return robject_null;
	}
}


static Robject* bt_int_bit_and(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value&TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return BOOLEAN_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return s_lt_int_bit_and(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for &");
		robject_ref(robject_null);
		return robject_null;
	}
}



static Robject* bt_int_bit_or(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value|TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return BOOLEAN_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return s_lt_int_bit_or(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for |");
		robject_ref(robject_null);
		return robject_null;
	}
}

static Robject* bt_int_bit_xor(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_INT(left)->i_value^TO_INT(right)->i_value;
		BTInt* ret=bt_int_create(value);
		return BOOLEAN_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return s_lt_int_bit_xor(left,right);
	}
	else
	{
		raise_type_error("Unsupport Operand for ^");
		robject_ref(robject_null);
		return robject_null;
	}
}

static int bt_int_booleaned(Robject* bti)
{
	return R_TO_INT(bti)->i_value;

}

static struct  rexpr_ops bt_int_expr_ops=
{
	.ro_negative=bt_int_negative,
	.ro_positive=bt_int_positive,

	.ro_mul=bt_int_mul,
	.ro_div=bt_int_div,
	.ro_mod=bt_int_mod,

	.ro_plus=bt_int_plus,
	.ro_minus=bt_int_minus,
	
	.ro_lshift=bt_int_lshift,
	.ro_rshift=bt_int_rshift,
	
	.ro_cmp=bt_int_cmp,

	.ro_bit_and=bt_int_and,
	.ro_bit_or=bit_int_or,
	.ro_bit_xor=bt_int_xor,
	
	.ro_booleaned=bt_int_booleaned,

};

static void bt_int_free(Robject* bt)
{
	free(R_TO_INT(bt));
}

static Robject_ops bt_int_ops=
{
	.ro_free=bt_int_free;
};

BTInt* bt_int_create(int value)
{
	BTInt* ret=(BTInt*)malloc(sizeof(*ret));
	ret->i_value=value;
	Robject* base=ret->i_base;

	base->r_name="Integer";
	base->r_expr_ops=&bt_int_expr_ops;
	base->r_type=RT_INT;
	base->r_ops=&bt_int_ops;
	return ret;
}


/* 
 * boolean parts
 * boolean is a specify type of integer
 * true = 1
 * false =0 
 */


static void bt_bool_free(Robject* bt)
{
}
static Robject_ops bt_bool_ops=
{
	.ro_free=bt_bool_free;
}

static BTInt bt_bool_true=
{
	{&bt_bool_ops,&bt_int_expr_ops,1,RT_INT,"Boolean"},
	1,
};



static BTInt bt_bool_false=
{
	{&bt_bool_ops,&bt_int_expr_ops,1,RT_INT,"Boolean"},
	0,
};

BTInt* bt_boolean_create(int value)
{
	BTInt* ret;
	if(value)
	{
		ret=&bt_bool_true;
	}
	else
	{
		ret=&bt_bool_false;
	}
	robject_ref(ret);
	return ret;
}

