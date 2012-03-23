#include"rtype.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<utility_c/marocs.h>

/* this func don't check error */
/* please be sure the str  is valid value */
static int char_to_int(char c)
{
	int ret=0;
	if('0'<=c && c<='9')
	{
		ret=c-'0';
	}
	else if('a'<=c && c<='f')
	{
		ret= c-'a'+10;
	}
	else if('A'<=c && c<='F')
	{
		ret=c-'A'+10;
	}
	else 
	{
		/* invalid char */
		BUG("Error Char(%c)",c);
		ret=0;
	}
	return ret; 
}

static int str_to_int(char* str)
{
	int len=strlen(str);
	int base=0;
	int value=0;
	assert(len!=0);
	if(len==1)
	{
		BUG_ON(*str<'0'||*str>'9',"Error Str(%s)",str);
		return *str-'0';
	}
	if(*str=='0')
	{
		char str_1=*(str+1);
		if(str_1=='x'||str_1=='X')
		{
			base=16;
			str+=2;
		}
		else if (str_1=='b'||str_1=='B')
		{
			base=2;
			str+=2;
		}
		else if (str_1=='o'||str_1=='O')
		{
			base=8;
			str+=2;
		}
		else 
		{
			base=8;
			str+=1;
		}
	}
	else
	{
		base=10;
	}

	while(*str)
	{
		char c_str=*str;
		int c_value=char_to_int(c_str);
		value=value*base+c_value;
		str++;
	}
	return value;
}


BtInt* bt_int_from_str(char* str)
{
	int value=str_to_int(str);
	BtInt* ret=bt_int_create(value);
	return ret;
}


/*unary operator + and - */
static Robject* bi_negative(Robject* rt)
{
	int value=-R_TO_I(rt)->i_value;
	BtInt* ret=bt_int_create(value);
	return I_TO_R(ret);
}

static Robject* bi_positive(Robject* rt)
{
	robject_addref(rt);
	return rt;
}

/*arithmetic operator * / %*/

/* int * float=float
 * int * long=long
 * int * int =int 
 */
static Robject* bi_mul(Robject* left,Robject* right)
{
	/* int*int ,eg 1*2*/
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value*R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}

	/* int*float ,eg 1*1.3*/
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_mul_int_float(left,right);
	}
	/* int*long, eg 2*333l */
	else if(rt_type(right)==RT_LONG)
	{
		return r_mul_int_long(left,right);
	}
	/* error type */
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MUL));
		robject_addref(robject_null);
		return robject_null;
	}

};


/* int/int=int 
 * int/long=long
 * int/float=float
 */
static Robject* bi_div(Robject* left,Robject* right)
{
	/* int div int, eg 1/2 */
	if(rt_type(right)==RT_INT)
	{
		if(R_TO_I(right)->i_value==0)
		{
			rt_raise_div_zero(MSG_DIV(robject_name(left)));
			robject_addref(robject_null);
			return robject_null;
		}
		int value=R_TO_I(left)->i_value/R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_div_int_float(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_div_int_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_DIV));
		robject_addref(robject_null);
		return robject_null;
	}

};

/* int%int=int 
 * int%float=float
 * int%long=long
 */
static Robject* bi_mod(Robject* left,Robject* right)
{
	/* int div int, eg 1/2 */
	if(rt_type(right)==RT_INT)
	{
		if(R_TO_I(right)->i_value==0)
		{
			rt_raise_div_zero(MSG_DIV(robject_name(left)));
			robject_addref(robject_null);
			return robject_null;
		}
		int value=R_TO_I(left)->i_value%R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	if(rt_type(right)==RT_LONG)
	{
		return r_mod_int_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MOD));
		robject_addref(robject_null);
		return robject_null;
	}

};



/*arithmetic operator + -*/
/* int+int=int
 * int+float=float
 * int+long=long
 */
static Robject* bi_plus(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value+R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
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
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_PLUS));
		robject_addref(robject_null);
		return robject_null;
	}
}

/* int-int=int;
 * int-float=float;
 * int-long=long
 */
static Robject* bi_minus(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value-R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
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
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MINUS));
		robject_addref(robject_null);
		return robject_null;
	}

}

/* bit_operator left shift and right shift */

/* int << int =int 
 * int << long=long
 */
static Robject* bi_lshift(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		if(R_TO_I(right)->i_value<0)
		{
			rt_raise_value_error(MSG_SHIFT_NEGATIVE);
			robject_addref(robject_null);
			return robject_null;
		}

		int value=R_TO_I(left)->i_value<<R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_lshift_int_long(left,right);
	}
	else 
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_LSHIFT));
		robject_addref(robject_null);
		return robject_null;
	}
}

/* int >> int=int
 * int >> long=long
 */
static Robject* bi_rshift(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		if(R_TO_I(right)->i_value<0)
		{
			rt_raise_value_error(MSG_SHIFT_NEGATIVE);
			robject_addref(robject_null);
			return robject_null;
		}
		int value=R_TO_I(left)->i_value>>R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_rshift_int_long(left,right);
	}
	else 
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_RSHIFT));
		robject_addref(robject_null);
		return robject_null;
	}
}

/*compare operator */

static Robject* bi_cmp(Robject* left,Robject* right)
{
	BtInt* ret=0;
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value-R_TO_I(right)->i_value;
		if(value<0)
		{
			ret=bt_int_create(-1);

		}
		else if(value==0)
		{
			ret=bt_int_create(0);
		}
		else
		{
			ret=bt_int_create(1);
		}
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_FLOAT)
	{
		return r_cmp_int_float(left,right);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_cmp_int_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_CMP));
		robject_addref(robject_null);
		return robject_null;
	}
}

/* bit_operator & | ^ ~ */
/* int&int=int
 * int&long=long
 */
static Robject* bi_and(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value&R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_and_int_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_AND));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* int|int=int
 * int|long=long
 */
static Robject* bi_or(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value|R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_or_int_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_OR));
		robject_addref(robject_null);
		return robject_null;
	}
}

/* int^int=int
 * int^long=long
 */

static Robject* bi_xor(Robject* left,Robject* right)
{
	if(rt_type(right)==RT_INT)
	{
		int value=R_TO_I(left)->i_value^R_TO_I(right)->i_value;
		BtInt* ret=bt_int_create(value);
		return I_TO_R(ret);
	}
	else if(rt_type(right)==RT_LONG)
	{
		return r_xor_int_long(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_XOR));
		robject_addref(robject_null);
		return robject_null;
	}
}
/* ~int =int */
static Robject* bi_negated(Robject* left)
{
	int value=~R_TO_I(left)->i_value;
	BtInt* ret=bt_int_create(value);
	return I_TO_R(ret);

}

/* logic operator and or not */
static Robject* bi_booleaned(Robject* bti)
{
	BtBoolean* ret=0;
	if(R_TO_I(bti)->i_value==0)
	{
		ret=bt_boolean_create(0);
	}
	else
	{
		ret=bt_boolean_create(1);
	}
	return B_TO_R(ret);

}


/* print operator */
static void bi_print(Robject* bt)
{
	printf("%d",R_TO_I(bt)->i_value);
}

static struct  rexpr_ops bt_int_expr_ops=
{
	/* unary operator + - */
	.ro_negative=bi_negative,
	.ro_positive=bi_positive,

	/* arithmetic * / % */
	.ro_mul=bi_mul,
	.ro_div=bi_div,
	.ro_mod=bi_mod,

	/* arithmetic + - */
	.ro_plus=bi_plus,
	.ro_minus=bi_minus,

	/* bit_operator << >>*/
	.ro_lshift=bi_lshift,
	.ro_rshift=bi_rshift,

	/* simple compare operator used for 
	 * < <= == != >= > */
	.ro_cmp=bi_cmp,

	/* bit_operator & | ^ ~ */
	.ro_bit_and=bi_and,
	.ro_bit_or=bi_or,
	.ro_bit_xor=bi_xor,
	.ro_bit_negated=bi_negated,

	/* logic operator and or not */
	.ro_bool=bi_booleaned,

	/*print */
	.ro_print=bi_print,

};

static void bi_free(Robject* bt)
{
	free(R_TO_I(bt));
}

struct robject_ops bt_int_ops=
{
	.ro_free=bi_free,
};

inline BtInt* bt_int_malloc()
{
	BtInt* ret=(BtInt*)malloc(sizeof(*ret));
	ret->i_value=0;
	Robject* base=&ret->i_base;

	base->r_name="Integer";
	base->r_expr_ops=&bt_int_expr_ops;
	base->r_type=RT_INT;
	base->r_ops=&bt_int_ops;
	base->r_ref=1;
	return ret;
}
BtInt* bt_int_create(int value)
{
	BtInt* ret=bt_int_malloc();
	ret->i_value=value;
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
	assert(0);/*bt_bool_free will never called*/
}
static struct robject_ops bt_bool_ops=
{
	.ro_free=bt_bool_free,
};

static void  bl_true_print(Robject* bt)
{
	printf("%s","true");
}

static struct rexpr_ops bl_true_ops=
{
	/* unary operator + - */
	.ro_negative=bi_negative,
	.ro_positive=bi_positive,

	/* arithmetic * / % */
	.ro_mul=bi_mul,
	.ro_div=bi_div,
	.ro_mod=bi_mod,

	/* arithmetic + - */
	.ro_plus=bi_plus,
	.ro_minus=bi_minus,

	/* bit_operator << >>*/
	.ro_lshift=bi_lshift,
	.ro_rshift=bi_rshift,

	/* simple compare operator used for 
	 * < <= == != >= > */
	.ro_cmp=bi_cmp,

	/* bit_operator & | ^ ~ */
	.ro_bit_and=bi_and,
	.ro_bit_or=bi_or,
	.ro_bit_xor=bi_xor,
	.ro_bit_negated=bi_negated,

	/* logic operator and or not */
	.ro_bool=bi_booleaned,

	/*print */
	.ro_print=bl_true_print,

};

static void  bl_false_print(Robject* bt)
{
	printf("%s","false");
}

static struct rexpr_ops bl_false_ops=
{
	/* unary operator + - */
	.ro_negative=bi_negative,
	.ro_positive=bi_positive,

	/* arithmetic * / % */
	.ro_mul=bi_mul,
	.ro_div=bi_div,
	.ro_mod=bi_mod,

	/* arithmetic + - */
	.ro_plus=bi_plus,
	.ro_minus=bi_minus,

	/* bit_operator << >>*/
	.ro_lshift=bi_lshift,
	.ro_rshift=bi_rshift,

	/* simple compare operator used for 
	 * < <= == != >= > */
	.ro_cmp=bi_cmp,

	/* bit_operator & | ^ ~ */
	.ro_bit_and=bi_and,
	.ro_bit_or=bi_or,
	.ro_bit_xor=bi_xor,
	.ro_bit_negated=bi_negated,

	/* logic operator and or not */
	.ro_bool=bi_booleaned,

	/*print */
	.ro_print=bl_false_print,

};

static BtInt bt_bool_true=
{
	{
		.r_ref=1,
		.r_type=RT_INT,
		.r_name="Boolean",
		.r_ops=&bt_bool_ops,
		.r_expr_ops=&bl_true_ops,
	},
	1,
};

static BtInt bt_bool_false=
{
	{
		.r_ref=1,
		.r_type=RT_INT,
		.r_name="Boolean",
		.r_ops=&bt_bool_ops,
		.r_expr_ops=&bl_false_ops,
	},
	0,
};

BtBoolean* bt_boolean_create(int value)
{
	BtInt* ret;
	if(value)
	{
		ret=&bt_bool_true;
	}
	else
	{
		ret=&bt_bool_false;
	}
	robject_addref(B_TO_R(ret));
	return ret;
}

