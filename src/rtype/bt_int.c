#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<utility_c/marocs.h>

#include"bt_int.h"
#include"bt_float.h"
#include"bt_string.h"
#include"bt_long.h"

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


BtInt* btint_from_str(char* str)
{
	int value=str_to_int(str);
	BtInt* ret=btint_create(value);
	return ret;
}

struct bt_long* btint_to_btlong(BtInt* i)
{
	TODO("Convert Int TO Long");
	return NULL;
}
struct bt_float* btint_to_btfloat(BtInt* i)
{
	TODO("Convert Int TO Float");
	return NULL;
}
struct bt_string* btint_to_btstring(BtInt* i)
{
	TODO("Convert Int TO String");
	return NULL;
}

/* expr */
/*unary expr*/
inline BtInt* btint_positive(BtInt* bi)
{
	robject_addref(I_TO_R(bi));
	return bi;
}

inline BtInt* btint_negative(BtInt* bi)
{
	int value=-bi->i_value;
	return btint_create(value);
}

inline BtInt* btint_negated(BtInt* bi)
{
	int value=~bi->i_value;
	return btint_create(value);
}

/*arithmetic expr*/
inline BtInt* btint_mul(BtInt* x,BtInt* y)
{
	int value=x->i_value*y->i_value;
	return btint_create(value);
}
	

inline BtInt* btint_div(BtInt* x,BtInt* y)
{
	if(y->i_value==0)
	{
		except_divzero_err_format("%s divide or module zero",
				robject_name(I_TO_R(x)));
		return NULL;
	}

	int value=x->i_value/y->i_value;
	return btint_create(value);
}
inline BtInt* btint_mod(BtInt* x,BtInt* y)
{
	if(y->i_value==0)
	{
		except_divzero_err_format("%s divide or module zero",
				robject_name(I_TO_R(x)));
		return NULL;
	}

	int value=x->i_value%y->i_value;
	return btint_create(value);
}
inline BtInt* btint_plus(BtInt* x,BtInt* y)
{
	int value=x->i_value+y->i_value;
	return btint_create(value);
}
inline BtInt* btint_minus(BtInt* x,BtInt* y)
{
	int value=x->i_value-y->i_value;
	return btint_create(value);
}

/*bitwise expr*/
inline BtInt* btint_lshift(BtInt* x,BtInt* y)
{
	if(y->i_value<0)
	{
		except_value_err_format("negative shift count");
		return NULL;
	}
	int value=x->i_value<<y->i_value;
	return btint_create(value);
}
inline BtInt* btint_rshift(BtInt* x,BtInt* y)
{
	if(y->i_value<0)
	{
		except_value_err_format("negative shift count");
		return NULL;
	}
	int value=x->i_value>>y->i_value;
	return btint_create(value);
}
inline BtInt* btint_or(BtInt* x,BtInt* y)
{
	int value=x->i_value|y->i_value;
	return btint_create(value);
}
inline BtInt* btint_xor(BtInt* x,BtInt* y)
{
	int value=x->i_value^y->i_value;
	return btint_create(value);
}
inline BtInt* btint_and(BtInt* x,BtInt* y)
{
	int value=x->i_value&y->i_value;
	return btint_create(value);
}

/*compare expr*/
inline int btint_lt(BtInt* x,BtInt* y)
{
	return x->i_value<y->i_value;
}


inline int btint_le(BtInt* x,BtInt* y)
{
	return x->i_value<=y->i_value;
}
inline int btint_eq(BtInt* x,BtInt* y)
{
	return x->i_value==y->i_value;
}
inline int btint_ne(BtInt* x,BtInt* y)
{
	return x->i_value!=y->i_value;
}
inline int btint_ge(BtInt* x,BtInt* y)
{
	return x->i_value>=y->i_value;
}
inline int btint_gt(BtInt* x,BtInt* y)
{
	return x->i_value>y->i_value;
}
int btint_cmp(BtInt* x,BtInt* y,int op)
{
	switch(op)
	{
		case CMP_LT:
			return btint_lt(x,y);
		case CMP_LE:
			return btint_le(x,y);
		case CMP_NE:
			return btint_ne(x,y);
		case CMP_EQ:
			return btint_eq(x,y);
		case CMP_GE:
			return btint_ge(x,y);
		case CMP_GT :
			return btint_gt(x,y);
	}
	BUG("Error cmpare op(%d)",op);
	return 0;
}
int btint_bool(BtInt* bi)
{
	if(bi->i_value==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}






/*unary operator + and - */
static Robject* bi_negative(Robject* rt)
{
	BtInt* ret= btint_negative(R_TO_I(rt));
	if(ret==NULL)
	{
		return NULL;
	}
	return I_TO_R(ret);
}

static Robject* bi_positive(Robject* rt)
{
	BtInt* ret= btint_positive(R_TO_I(rt));
	if(ret==NULL)
	{
		return NULL;
	}
	return I_TO_R(ret);
}

/*arithmetic operator * / %*/

/* int * float=float
 * int * long=long
 * int * int =int 
 */
static Robject* bi_mul(Robject* x,Robject* y)
{

	int type=rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_mul(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	if(type==RT_FLOAT)
	{
		BtFloat*  c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtFloat* ret=btfloat_mul(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return  F_TO_R(ret);
	}
	/* int*long, eg 2*333l */
	if(type==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_mul(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	/* error type */
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_MUL);
	return NULL;

}


/* int/int=int 
 * int/long=long
 * int/float=float
 */
static Robject* bi_div(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_mul(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	else if(type==RT_FLOAT)
	{
		BtFloat*  c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtFloat* ret=btfloat_div(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return  F_TO_R(ret);
	}
	if(type==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_div(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_DIV);
	return NULL;

}

/* int%int=int 
 * int%float=float
 * int%long=long
 */
static Robject* bi_mod(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_mod(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	else if(type==RT_FLOAT)
	{
		BtFloat*  c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtFloat* ret=btfloat_mod(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return  F_TO_R(ret);
	}
	if(type==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_mod(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_MOD);
	return NULL;

}



/*arithmetic operator + -*/
/* int+int=int
 * int+float=float
 * int+long=long
 */
static Robject* bi_plus(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_plus(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	else if(type==RT_FLOAT)
	{
		BtFloat*  c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtFloat* ret=btfloat_plus(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return  F_TO_R(ret);
	}
	if(type==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_plus(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	if(type==RT_STRING)
	{
		BtString* c_x=btint_to_btstring(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtString* ret=btstring_plus(c_x,R_TO_S(y));
		robject_release(S_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return S_TO_R(ret);
	}


	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_PLUS);
	return NULL;
}

/* int-int=int;
 * int-float=float;
 * int-long=long
 */
static Robject* bi_minus(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_minus(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	else if(type==RT_FLOAT)
	{
		BtFloat*  c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtFloat* ret=btfloat_minus(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return  F_TO_R(ret);
	}
	if(type==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_minus(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}


	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_MINUS);
	return NULL;
}

/* bit_operator x shift and y shift */

/* int << int =int 
 * int << long=long
 */
static Robject* bi_lshift(Robject* x,Robject* y)
{
	int type =rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_lshift(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_lshift(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_LSHIFT);
	return NULL;

}

/* int >> int=int
 * int >> long=long
 */
static Robject* bi_rshift(Robject* x,Robject* y)
{
	int type =rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_rshift(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_rshift(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_RSHIFT);
	return NULL;
}

/*compare operator */

int bi_cmp(Robject* x,Robject* y,int op)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		int ret=btint_cmp(R_TO_I(x),R_TO_I(y),op);
		return op;
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL)
		{
			return -1;
		}
		int  ret=btlong_rshift(c_x,R_TO_L(y));
		robject_release(F_TO_R(c_x));
		return ret;
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return -1;
		}
		int ret=btlong_rshift(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		return ret;
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_NAME[op]);
	return -1;
}
static int bi_lt(Robject* x,Robject* y)
{
	return bi_cmp(x,y,CMP_LT);
}
static int bi_le(Robject* x,Robject* y)
{
	return bi_cmp(x,y,CMP_LE);
}
static int bi_gt(Robject* x,Robject* y)
{
	return bi_cmp(x,y,CMP_GT);
}
static int bi_ge(Robject* x,Robject* y)
{
	return bi_cmp(x,y,CMP_GE);
}
static int bi_eq(Robject* x,Robject* y)
{
	return bi_cmp(x,y,CMP_EQ);
}
static int bi_ne(Robject* x,Robject* y)
{
	return bi_cmp(x,y,CMP_NE);
}
/* bit_operator & | ^ ~ */
/* int&int=int
 * int&long=long
 */
static Robject* bi_and(Robject* x,Robject* y)
{
	int type =rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_and(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_and(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_RSHIFT);
	return NULL;
}


/* int|int=int
 * int|long=long
 */
static Robject* bi_or(Robject* x,Robject* y)
{
	int type =rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_or(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_or(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject(y),OPER_OR);
	return NULL;
}

/* int^int=int
 * int^long=long
 */

static Robject* bi_xor(Robject* x,Robject* y)
{
	int type =rt_type(y);
	if(type==RT_INT)
	{
		BtInt* ret=btint_xor(R_TO_I(x),R_TO_I(y));
		if(ret==NULL)
		{
			return NULL;
		}
		return I_TO_R(ret);
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL)
		{
			return NULL;
		}
		BtLong* ret=btlong_xor(c_x,R_TO_L(y));
		robject_release(L_TO_R(c_x));
		if(ret==NULL)
		{
			return NULL;
		}
		return L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,robject_name(x),robject_name(y),OPER_XOR);
	return NULL;
	
}
/* ~int =int */
static Robject* bi_negated(Robject* x)
{
	BtInt* ret=btint_negated(R_TO_I(x));
	if(ret==NULL)
	{
		return NULL;
	}
	return I_TO_R(ret);

}

/* logic operator and or not */
static int bi_bool(Robject* bti)
{
	return btint_bool(R_TO_I(bti));
}


/* print operator */
static void bi_print(Robject* bt,FILE* f,int flags)
{
	printf("%d",R_TO_I(bt)->i_value);
}

static struct  expr_ops bi_expr_ops=
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
	.ro_lt=bi_lt,
	.ro_le=bi_le,
	.ro_ge=bi_ge,
	.ro_gt=bi_gt,
	.ro_eq=bi_eq,
	.ro_ne=bi_ne,

	/* bit_operator & | ^ ~ */
	.ro_and=bi_and,
	.ro_or=bi_or,
	.ro_xor=bi_xor,
	.ro_negated=bi_negated,

	/* logic operator and or not */
	.ro_bool=bi_bool,

	/*print */
	.ro_print=bi_print,

};

static void bi_free(Robject* bt)
{
	free(R_TO_I(bt));
}

struct object_ops int_object_ops=
{
	.ro_free=bi_free,
};
static TypeObject type_int=
{
	.t_name="Integer",
	.t_type=RT_INT,
	.t_expr_funcs=&bi_expr_ops,
	.t_object_func=&int_object_ops,
};

inline BtInt* bt_int_malloc()
{
	return robject_new(BtInt,&type_int);
}

BtInt* bt_int_create(int value)
{
	BtInt* ret=bt_int_malloc();
	ret->i_value=value;
	return ret;
}



