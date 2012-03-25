#include"rtype.h"
#include<stdio.h>
#include<string.h>
#include<utility_c/marocs.h>



/* unary operator + - */
static Robject* bl_negative(Robject* left)
{
	BGInteger* bg=bg_negative(R_TO_L(left)->l_value);
	BtLong* ret=bt_long_create(bg);
	return L_TO_R(ret);
}

static Robject* bl_positive(Robject* left)
{
	robject_addref(left);
	return left;
}


/* arithmetic operator * / % */
/* long * long =long 
 * long * int =long 
 * long * float =float 
 */
static Robject* bl_mul(Robject* left, Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		BGInteger* bg=bg_mul(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_FLOAT)
	{
		return r_mul_long_float(left,right);
	}
	else if( type==RT_INT)
	{
		return r_mul_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MUL));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* long / long =long 
 * long /int =long 
 * long / float =float 
 */
static Robject* bl_div(Robject* left, Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		if(bg_is_zero(R_TO_L(right)->l_value))
		{
			rt_raise_div_zero(MSG_DIV(robject_name(left)));
			robject_addref(robject_null);
			return robject_null;
		}
		BGInteger* bg=bg_div(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_FLOAT)
	{
		return r_div_long_float(left,right);
	}
	else if( type==RT_INT)
	{
		return r_div_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_DIV));
		robject_addref(robject_null);
		return robject_null;
	}
}

/* long % long =long 
 * long % int =long 
 */
static Robject* bl_mod(Robject* left, Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		if(bg_is_zero(R_TO_L(right)->l_value))
		{
			rt_raise_div_zero(MSG_DIV(robject_name(left)));
			robject_addref(robject_null);
			return robject_null;
		}
		BGInteger* bg=bg_mod(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_INT)
	{
		return r_mod_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MOD));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* arithmetic + - */
/* long + long= long 
 * long + int = long 
 * long + float= float 
 */
static Robject* bl_plus(Robject* left, Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		BGInteger* bg=bg_plus(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_FLOAT)
	{
		return r_plus_long_float(left,right);
	}
	else if( type==RT_INT)
	{
		return r_plus_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_PLUS));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* long - long= long 
 * long - int = long 
 * long - float= float 
 */
static Robject* bl_minus(Robject* left, Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		BGInteger* bg=bg_minus(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_FLOAT)
	{
		return r_minus_long_float(left,right);
	}
	else if( type==RT_INT)
	{
		return r_minus_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_MINUS));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* shift operator << >> */

/* long << long =long 
 * long << int =long 
 */
static Robject* bl_lshift(Robject* left,Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		if(bg_overflow_int(R_TO_L(right)->l_value))
		{
			rt_raise_overflow(MSG_LONG_OVERFLOW);
			goto error;
		}
		if(bg_is_negative(R_TO_L(right)->l_value))
		{
			rt_raise_value_error(MSG_SHIFT_NEGATIVE);
			goto error;
		}
		BGInteger* bg=bg_lshift(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_INT)
	{
		return r_lshift_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_LSHIFT));
		goto error;
	}

error:
	robject_addref(robject_null);
	return robject_null;
}


/* long >> long =long 
 * long >> int =long 
 */
static Robject* bl_rshift(Robject* left,Robject* right)
{
	int type=rt_type(right);
	if(type==RT_LONG)
	{
		if(bg_overflow_int(R_TO_L(right)->l_value))
		{
			rt_raise_overflow(MSG_LONG_OVERFLOW);
			goto error;
		}
		if(bg_is_negative(R_TO_L(right)->l_value))
		{
			rt_raise_value_error(MSG_SHIFT_NEGATIVE);
			goto error;
		}
		BGInteger* bg=bg_rshift(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_INT)
	{
		return r_rshift_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_RSHIFT));
		goto error;
	}

error:
	robject_addref(robject_null);
	return robject_null;
}


static Robject* bl_cmp(Robject* left,Robject* right)
{
	int value=0;
	BtInt* ret=0;

	int type=rt_type(right);
	if(type==RT_LONG)
	{
		value=bg_cmp(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
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
	else if( type==RT_INT)
	{
		return r_cmp_long_int(left,right);
	}
	else if( type==RT_FLOAT)
	{
		return r_cmp_long_float(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_CMP));
		robject_addref(robject_null);
		return robject_null;
	}
}


/* bitwise operator & | ^ ~ */

/* long & long =long
 * long & int =long 
 */
static  Robject* bl_and(Robject* left,Robject* right)
{
	int type=rt_type(right);

	if(type==RT_LONG)
	{
		BGInteger* bg=bg_and(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_INT)
	{
		return r_and_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_BIT_AND));
		robject_addref(robject_null);
		return robject_null;
	}

}

/* long | long =long
 * long | int =long 
 */
static  Robject* bl_or(Robject* left,Robject* right)
{
	int type=rt_type(right);

	if(type==RT_LONG)
	{
		BGInteger* bg=bg_or(R_TO_L(left)->l_value,R_TO_L(right)->l_value);

		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_INT)
	{
		return r_or_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_BIT_OR));
		robject_addref(robject_null);
		return robject_null;
	}

}

/* long ^ long =long
 * long ^ int =long 
 */
static  Robject* bl_xor(Robject* left,Robject* right)
{
	int type=rt_type(right);

	if(type==RT_LONG)
	{
		BGInteger* bg=bg_xor(R_TO_L(left)->l_value,R_TO_L(right)->l_value);
		BtLong* ret=bt_long_create(bg);
		return L_TO_R(ret);
	}
	else if( type==RT_INT)
	{
		return r_xor_long_int(left,right);
	}
	else
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_BIT_XOR));
		robject_addref(robject_null);
		return robject_null;
	}

}


/* ~long=long */
static Robject* bl_negated(Robject* btl)
{
	BGInteger* bg=bg_negated(R_TO_L(btl)->l_value);
	BtLong* ret=bt_long_create(bg);
	return L_TO_R(ret);

}


/* logic operator and or not */
static Robject* bl_booleaned(Robject* btl)
{
	int bg_ret=bg_booleaned(R_TO_L(btl)->l_value);
	BtBoolean* ret=0;
	if(bg_ret)
	{
		ret=bt_boolean_create(1);
	}
	else
	{
		ret=bt_boolean_create(0);
	}
	return B_TO_R(ret);
}


/* print operator */
static void bl_print(Robject* btl)
{
	bg_print_dec(R_TO_L(btl)->l_value);
}


static struct rexpr_ops bt_long_expr_ops=
{
	/* unary operator + - */
	.ro_negative=bl_negative,
	.ro_positive=bl_positive,


	/* arithmetic * / % */
	.ro_mul=bl_mul,
	.ro_div=bl_div,
	.ro_mod=bl_mod,

	/* arithmetic + - */
	.ro_plus=bl_plus,
	.ro_minus=bl_minus,

	/* bit_operator << >>*/
	.ro_lshift=bl_lshift,
	.ro_rshift=bl_rshift,

	/* simple compare operator used for 
	 * < <= == != >= > */
	.ro_cmp=bl_cmp,

	/* bit_operator & | ^ ~ */
	.ro_bit_and=bl_and,
	.ro_bit_or=bl_or,
	.ro_bit_xor=bl_xor,
	.ro_bit_negated=bl_negated,

	/* logic operator and or not */
	.ro_bool=bl_booleaned,

	/*print */
	.ro_print=bl_print,
};

static void bl_free(Robject* bt)
{
	bg_free(R_TO_L(bt)->l_value);
	free(R_TO_L(bt));
}

struct robject_ops bt_long_ops=
{
	.ro_free=bl_free,
};


inline BtLong* bt_long_malloc()
{
	BtLong* ret=(BtLong*)malloc(sizeof(*ret));
	ret->l_value=0;
	Robject* base=&ret->l_base;

	base->r_name="LongInteger";
	base->r_expr_ops=&bt_long_expr_ops;
	base->r_type=RT_LONG;
	base->r_ops=&bt_long_ops;
	base->r_ref=1;
	return ret;
}
BtLong* bt_long_create(BGInteger* value)
{
	BtLong* ret=bt_long_malloc();
	ret->l_value=value;
	return ret;
}

BtLong* bt_long_from_int(int value)
{
	BtLong* ret=bt_long_malloc();
	BGInteger* bg=bg_create_from_int(value);
	ret->l_value=bg;
	return ret;
}
BtLong* bt_long_from_str(char* str)
{
	/*eg. str=0x4444l ,33333L */
	int len=strlen(str);
	/* will remove the postfix L, so len is ok */
	char* str_cpy=malloc(len);
	memcpy(str_cpy,str,len);
	/* remove l */
	str_cpy[len-1]='\0';
	len--;

	BGInteger* bg=0;
	if(len==0)
	{
		BUG("Error Str(%s",str);
		bg=bg_create_from_int(0);
	}
	else if(len==1)
	{
		bg=bg_create_from_decstr(str_cpy);

	}
	else
	{
		if(*str_cpy=='0')
		{
			char c_str=*(str_cpy+1);
			if(c_str=='o'||c_str=='O')
			{
				bg=bg_create_from_octstr(str_cpy+2);
			}
			else if(c_str=='x'||c_str=='X')
			{
				bg=bg_create_from_hexstr(str_cpy+2);
			}
			else if(c_str=='b'|| c_str=='B')
			{
				bg=bg_create_from_binstr(str_cpy+2);
			}
			else
			{
				bg=bg_create_from_octstr(str_cpy+1);
			}
		}
		else
		{
			bg=bg_create_from_decstr(str_cpy);
		}
	}
	BtLong* ret=bt_long_malloc();
	ret->l_value=bg;
	free(str_cpy);
	return ret;
}
