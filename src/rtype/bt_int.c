#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<utility_c/marocs.h>

#include"bt_int.h"
#include"bt_float.h"
#include"bt_string.h"
#include"bt_long.h"
#include"bt_bool.h"

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
	BtLong* ret=btlong_from_int(i->i_value);
	if(ret==NULL) return NULL;
	return ret;
}
struct bt_float* btint_to_btfloat(BtInt* i)
{
	float value=i->i_value;
	BtFloat* ret=btfloat_create(value);
	return ret;
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
	BUG("Error compare op(%d)",op);
	return -1;
}
int btint_bool(BtInt* bi)
{
	return bi->i_value!=0;
}
inline ssize_t btint_hash(BtInt* bi)
{
	int value=bi->i_value;

	return value==-1?-2:value;
}

inline int btint_print(BtInt* bi,FILE* f,int flags)
{
	printf("%d",bi->i_value);
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
	return 0;

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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_MUL, robject_name(x),
						robject_name(y));
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
		BtInt* ret=btint_div(R_TO_I(x),R_TO_I(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
								OPER_DIV,robject_name(x),
								robject_name(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_MOD,robject_name(x),
							robject_name(y));
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


	except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_PLUS,robject_name(x),
							robject_name(y));
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


	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_MINUS,robject_name(x),
						robject_name(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
					OPER_LSHIFT,robject_name(x),
					robject_name(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_RSHIFT,robject_name(x),
						robject_name(y));
	return NULL;
}

/*compare operator */

int bi_cmp(Robject* x,Robject* y,int op)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		int ret=btint_cmp(R_TO_I(x),R_TO_I(y),op);
		return ret;
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL) return -1;
		int  ret=btfloat_cmp(c_x,R_TO_F(y),op);
		robject_release(F_TO_R(c_x));
		return ret;
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL) return -1;
		int ret=btlong_cmp(c_x,R_TO_L(y),op);
		robject_release(L_TO_R(c_x));
		return ret;
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
					CMP_NAME(op),robject_name(x),
					robject_name(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_RSHIFT,robject_name(x),
						robject_name(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_OR,robject_name(x),
						robject_name(y));
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
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_XOR,robject_name(x),
					   	robject_name(y));
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

static int bi_rich_cmp(Robject* x,Robject* y,int op)
{

	int type=rt_type(y);
	if(type==RT_INT)
	{
		int ret=btint_cmp(R_TO_I(x),R_TO_I(y),op);
		return ret;
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btint_to_btfloat(R_TO_I(x));
		if(c_x==NULL) return -1;
		int  ret=btfloat_cmp(c_x,R_TO_F(y),op);
		robject_release(F_TO_R(c_x));
		return ret;
	}
	if(rt_type(y)==RT_LONG)
	{
		BtLong* c_x=btint_to_btlong(R_TO_I(x));
		if(c_x==NULL) return -1;
		int ret=btlong_cmp(c_x,R_TO_L(y),op);
		robject_release(L_TO_R(c_x));
		return ret;
	}
	return CMP_NOT_SUPPORT;
}


/* FIXME int hash is use for temp*/
static ssize_t bi_hash(Robject* bt)
{
	return btint_hash(R_TO_I(bt));
}


/* print operator */
static int bi_print(Robject* bt,FILE* f,int flags)
{
	BtInt* bi=R_TO_I(bt);
	btint_print(bi,NULL,flags);
	return 1;
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
	.t_object_funcs=&int_object_ops,
	.t_rich_cmp=&bi_rich_cmp,
	.t_hash=bi_hash,
	.t_print=bi_print,
};

inline BtInt* btint_malloc()
{
	return robject_new(BtInt,&type_int);
}

BtInt* btint_create(int value)
{
	BtInt* ret=btint_malloc();
	ret->i_value=value;
	return ret;
}







/* bt_bool part */
static int bl_false_print(Robject* r,FILE* f,int flags)
{
	printf("false");
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
	return 0;
}
static int bl_true_print(Robject* r,FILE* f,int flags)
{
	printf("true");
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
	return 0;
}
static void bb_free(Robject* r)
{
	BUG("Free Bool Object");
}
static struct object_ops bool_object_ops=
{
	.ro_free=bb_free,
};

static TypeObject type_bool_false=
{
	.t_name="Bool",
	.t_type=RT_INT,
	.t_expr_funcs=&bi_expr_ops,
	.t_object_funcs=&bool_object_ops,
	.t_rich_cmp=&bi_rich_cmp,
	.t_hash=bi_hash,
	.t_print=bl_false_print,
};
static TypeObject type_bool_true=
{
	.t_name="Bool",
	.t_type=RT_INT,
	.t_expr_funcs=&bi_expr_ops,
	.t_object_funcs=&bool_object_ops,
	.t_rich_cmp=&bi_rich_cmp,
	.t_hash=bi_hash,
	.t_print=bl_true_print,
};

static BtInt bool_object_false=
{
	{.r_ref=1, .r_type=&type_bool_false,},
	0,
};

static BtInt bool_object_true=
{
	{.r_ref=1, .r_type=&type_bool_true,},
	1,
};

BtBool* btbool_create(int value)
{
	BtBool* ret=value?&bool_object_true:&bool_object_false;
	robject_addref(B_TO_R(ret));
	return ret;
}

BtBool* btbool_false()
{
	robject_addref(B_TO_R(&bool_object_false));
	return &bool_object_false;
}
BtBool* btbool_true()
{
	robject_addref(B_TO_R(&bool_object_true));
	return &bool_object_true;
}
int btbool_bool(BtBool* bb)
{
	return bb->i_value!=0;
}





