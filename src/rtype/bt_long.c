#include<stdio.h>
#include<string.h>
#include<utility_c/marocs.h>
#include"bt_long.h"
#include"bt_int.h"
#include"bt_string.h"
#include"bt_float.h"

/*FIXME  btlong_over_float not impliment*/
int btlong_over_float(BtLong* bl)
{
	return 0;
}
int btlong_to_int(BtLong* bl)
{
	return bg_to_int(bl->l_value);
}


struct bt_int * btlong_to_btint(BtLong* bl)
{
	if(btlong_over_int(bl))
	{
		except_overflow_err_format("long is too large to convert to int");
		return NULL;
	}
	int value=btlong_to_int(bl);
	BtInt* ret=btint_create(value);
	return ret;
}

/*FIXME this is only for temp*/
struct bt_float* btlong_to_btfloat(BtLong* bl)
{
	if(btlong_over_float(bl))
	{
		except_overflow_err_format(
					"long is too large to convert to float");
		return NULL;
	}
	float value=bg_to_float(bl->l_value);
	BtFloat* ret=btfloat_create(value);
	return ret;
}
struct bt_string* btlong_to_btstring(BtLong* bl)
{
	TODO("Convert BtLong TO BtString");
	return NULL;
}
BtLong* btlong_positive(BtLong* bl)
{
	robject_addref(L_TO_R(bl));
	return bl;
}

	
BtLong* btlong_negative(BtLong* bl)
{
	BGInteger* bg=bg_negative(bl->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

BtLong* btlong_negated(BtLong* bl)
{
	BGInteger* bg=bg_negated(bl->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

/*arithmetic expr*/
BtLong* btlong_mul(BtLong* x,BtLong* y)
{
	BGInteger* bg=bg_mul(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

BtLong* btlong_div(BtLong* x,BtLong* y)
{
	if(btlong_is_zero(y))
	{
		except_divzero_err_format("%s divide or module zero",
				robject_name(L_TO_R(x)));
		return NULL;
	}
	BGInteger* bg=bg_div(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

		
BtLong* btlong_mod(BtLong* x,BtLong* y)
{
	if(btlong_is_zero(y))
	{
		except_divzero_err_format("%s divide or module zero",
				robject_name(L_TO_R(x)));
		return NULL;
	}
	BGInteger* bg=bg_mod(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}
BtLong* btlong_plus(BtLong* x,BtLong* y)
{
	BGInteger* bg=bg_plus(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}
BtLong* btlong_minus(BtLong* x,BtLong* y)
{
	BGInteger* bg=bg_minus(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

/*bltwise expr*/
BtLong* btlong_lshift(BtLong* x,BtLong* y)
{
	if(btlong_over_int(y))
	{
		except_overflow_err_format("long to large to convert to int");
		return NULL;
	}
	if(btlong_lt_zero(y))
	{
		except_value_err_format("negative shift count");
		return NULL;
	}
	BGInteger* bg=bg_lshift(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}


BtLong* btlong_rshift(BtLong* x,BtLong* y)
{
	if(btlong_over_int(y))
	{
		except_overflow_err_format("long to large to convert to int");
		return NULL;
	}
	if(btlong_lt_zero(y))
	{
		except_value_err_format("negative shift count");
		return NULL;
	}
	BGInteger* bg=bg_rshift(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}
BtLong* btlong_or(BtLong* x,BtLong* y)
{
	BGInteger* bg=bg_or(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}


BtLong* btlong_xor(BtLong* x,BtLong* y)
{
	BGInteger* bg=bg_xor(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

BtLong* btlong_and(BtLong* x,BtLong* y)
{
	BGInteger* bg=bg_and(x->l_value,y->l_value);
	if(bg==NULL)
	{
		return NULL;
	}
	BtLong* ret=btlong_create(bg);
	return ret;
}

/*compare expr*/
int btlong_lt(BtLong* x,BtLong* y)
{
	int ret=bg_cmp(x->l_value,y->l_value);
	if(ret<0)
		return 1;
	else 
		return 0;
}
int btlong_le(BtLong* x,BtLong* y)
{
	int ret=bg_cmp(x->l_value,y->l_value);
	if(ret<=0)
		return 1;
	else 
		return 0;
}
int btlong_eq(BtLong* x,BtLong* y)
{
	int ret=bg_cmp(x->l_value,y->l_value);
	if(ret==0)
		return 1;
	else 
		return 0;
}
int btlong_ne(BtLong* x,BtLong* y)
{
	int ret=bg_cmp(x->l_value,y->l_value);
	if(ret!=0)
		return 1;
	else 
		return 0;
}
int btlong_ge(BtLong* x,BtLong* y)
{
	int ret=bg_cmp(x->l_value,y->l_value);
	if(ret>=0)
		return 1;
	else 
		return 0;
}
int btlong_gt(BtLong* x,BtLong* y)
{
	int ret=bg_cmp(x->l_value,y->l_value);
	if(ret>0)
		return 1;
	else 
		return 0;
}
int btlong_cmp(BtLong* x,BtLong* y,int op)
{
	switch(op)
	{
		case CMP_LT:
			return btlong_lt(x,y);
		case CMP_LE:
			return btlong_le(x,y);
		case CMP_GE:
			return btlong_ge(x,y);
		case CMP_GT:
			return btlong_gt(x,y);
		case CMP_EQ:
			return btlong_eq(x,y);
		case CMP_NE:
			return btlong_ne(x,y);
	}
	BUG("Error cmpare op(%d)",op);
	return -1;
}


int btlong_bool(BtLong* bl)
{
	return bl->l_value->b_len==0;
}

ssize_t btlong_hash(BtLong* bl)
{
	TODO("Long Hash");
	return 1;
}

int btlong_print(BtLong* bl,FILE* f,int flags)
{
	bg_print_dec(bl->l_value);
	return 1;
}


/* unary operator + - */
static Robject* bl_negative(Robject* x)
{
	BtLong* ret= btlong_negative(R_TO_L(x));
	if(ret==0)
	{
		return NULL;
	}
	return L_TO_R(ret);
}

static Robject* bl_positive(Robject* x)
{
	BtLong* ret= btlong_positive(R_TO_L(x));
	if(ret==0)
	{
		return NULL;
	}
	return L_TO_R(ret);
}


/* arithmetic operator * / % */
/* long * long =long 
 * long * int =long 
 * long * float =float 
 */
static Robject* bl_mul(Robject* x, Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_mul(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_mul(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btlong_to_btfloat(R_TO_L(x));
		if(c_x==NULL) return NULL;
		BtFloat* ret=btfloat_mul(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		return ret==NULL?NULL:F_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_MUL,robject_name(x),
						robject_name(y));
	return NULL;

}


/* long / long =long 
 * long /int =long 
 * long / float =float 
 */
static Robject* bl_div(Robject* x, Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_div(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_div(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btlong_to_btfloat(R_TO_L(x));
		if(c_x==NULL) return NULL;
		BtFloat* ret=btfloat_div(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		return ret==NULL?NULL:F_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_DIV,robject_name(x),
						robject_name(y));
	return NULL;
}

/* long % long =long 
 * long % int =long 
 */
static Robject* bl_mod(Robject* x, Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_mod(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_mod(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_MOD,robject_name(x),
							robject_name(y));
	return NULL;
}


/* arithmetic + - */
/* long + long= long 
 * long + int = long 
 * long + float= float 
 */
static Robject* bl_plus(Robject* x, Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_plus(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_plus(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btlong_to_btfloat(R_TO_L(x));
		if(c_x==NULL) return NULL;
		BtFloat* ret=btfloat_plus(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		return ret==NULL?NULL:F_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_PLUS,robject_name(x),
						robject_name(y));
	return NULL;
}


/* long - long= long 
 * long - int = long 
 * long - float= float 
 */
static Robject* bl_minus(Robject* x, Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_minus(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_minus(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_FLOAT)
	{
		BtFloat* c_x=btlong_to_btfloat(R_TO_L(x));
		if(c_x==NULL) return NULL;
		BtFloat* ret=btfloat_minus(c_x,R_TO_F(y));
		robject_release(F_TO_R(c_x));
		return ret==NULL?NULL:F_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_MINUS,robject_name(x),
						robject_name(y));
	return NULL;
}


/* shift operator << >> */

/* long << long =long 
 * long << int =long 
 */
static Robject* bl_lshift(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_lshift(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_lshift(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
					OPER_LSHIFT,robject_name(x),
					robject_name(y));
	return NULL;
}


/* long >> long =long 
 * long >> int =long 
 */
static Robject* bl_rshift(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_rshift(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_rshift(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						OPER_RSHIFT,robject_name(x),
						robject_name(y));
	return NULL;
}


static int bl_cmp(Robject* x,Robject* y,int op)
{

	int type=rt_type(y);
	if(type==RT_LONG)
	{
		return btlong_cmp(R_TO_L(x),R_TO_L(y),op);
	}
	if( type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return -1;
		int ret=btlong_cmp(R_TO_L(x),c_y,op);
		robject_release(L_TO_R(c_y));
		return ret;
	}
	if( type==RT_FLOAT)
	{
		BtFloat* c_x=btlong_to_btfloat(R_TO_L(x));
		if(c_x==NULL) return -1;
		int ret=btfloat_cmp(c_x,R_TO_F(y),op);
		robject_release(F_TO_R(c_x));
		return ret;
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
						CMP_NAME(op),robject_name(x),
						robject_name(y));
	return -1;

}

static int bl_lt(Robject* x,Robject* y)
{
	return bl_cmp(x,y,CMP_LT);
}
static int bl_le(Robject* x,Robject* y)
{
	return bl_cmp(x,y,CMP_LE);
}
static int bl_gt(Robject* x,Robject* y)
{
	return bl_cmp(x,y,CMP_GT);
}
static int bl_ge(Robject* x,Robject* y)
{
	return bl_cmp(x,y,CMP_GE);
}
static int bl_eq(Robject* x,Robject* y)
{
	return bl_cmp(x,y,CMP_EQ);
}
static int bl_ne(Robject* x,Robject* y)
{
	return bl_cmp(x,y,CMP_NE);
}

static int bl_rich_cmp(Robject* x,Robject* y,int op)
{

	int type=rt_type(y);
	if(type==RT_LONG)
	{
		return btlong_cmp(R_TO_L(x),R_TO_L(y),op);
	}
	if( type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return -1;
		int ret=btlong_cmp(R_TO_L(x),c_y,op);
		robject_release(L_TO_R(c_y));
		return ret;
	}
	if( type==RT_FLOAT)
	{
		BtFloat* c_x=btlong_to_btfloat(R_TO_L(x));
		if(c_x==NULL) return -1;
		int ret=btfloat_cmp(c_x,R_TO_F(y),op);
		robject_release(F_TO_R(c_x));
		return ret;
	}
	return CMP_NOT_SUPPORT;
}

/* bitwise operator & | ^ ~ */

/* long & long =long
 * long & int =long 
 */
static  Robject* bl_and(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_and(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_and(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
					OPER_AND,robject_name(x),
					robject_name(y));
	return NULL;

}

/* long | long =long
 * long | int =long 
 */
static  Robject* bl_or(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_or(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_or(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
					OPER_OR,robject_name(x),
					robject_name(y));
	return NULL;
}

/* long ^ long =long
 * long ^ int =long 
 */
static  Robject* bl_xor(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_LONG)
	{
		BtLong* ret=btlong_xor(R_TO_L(x),R_TO_L(y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	if(type==RT_INT)
	{
		BtLong* c_y=btint_to_btlong(R_TO_I(y));
		if(c_y==NULL) return NULL;
		BtLong* ret=btlong_xor(R_TO_L(x),c_y);
		robject_release(L_TO_R(c_y));
		return ret==NULL?NULL:L_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
					OPER_XOR,robject_name(x),
					robject_name(y));
	return NULL;
}


/* ~long=long */
static Robject* bl_negated(Robject* bl)
{
	BtLong* ret=btlong_negated(R_TO_L(bl));
	return ret==NULL?NULL:L_TO_R(ret);
}


/* logic operator and or not */
static int bl_bool(Robject* bl)
{
	return btlong_bool(R_TO_L(bl));
}


/* print operator */
static int bl_print(Robject* bl,FILE* f,int flags)
{
	return btlong_print(R_TO_L(bl),f,flags);
}


static struct expr_ops bl_expr_ops=
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

	/* < <= == != >= > */
	.ro_lt=bl_lt,
	.ro_le=bl_le,
	.ro_gt=bl_gt,
	.ro_ge=bl_ge,
	.ro_eq=bl_eq,
	.ro_ne=bl_ne,


	/* bit_operator & | ^ ~ */
	.ro_and=bl_and,
	.ro_or=bl_or,
	.ro_xor=bl_xor,
	.ro_negated=bl_negated,

	/* logic operator and or not */
	.ro_bool=bl_bool,

	/*print */
	.ro_print=bl_print,
};

static void bl_free(Robject* bt)
{
	bg_free(R_TO_L(bt)->l_value);
	free(R_TO_L(bt));
}

struct object_ops long_object_ops=
{
	.ro_free=bl_free,
};

static TypeObject type_long=
{
	.t_name="LongInteger",
	.t_type=RT_LONG,
	.t_expr_funcs=&bl_expr_ops,
	.t_object_funcs=&long_object_ops,
	.t_rich_cmp=bl_rich_cmp,
};

inline BtLong* btlong_malloc()
{
	return robject_new(BtLong,&type_long);
}
BtLong* btlong_create(BGInteger* value)
{
	BtLong* ret=btlong_malloc();
	ret->l_value=value;
	return ret;
}

BtLong* btlong_from_int(int value)
{
	BtLong* ret=btlong_malloc();
	BGInteger* bg=bg_create_from_int(value);
	ret->l_value=bg;
	return ret;
}
BtLong* btlong_from_str(char* str)
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
	BtLong* ret=btlong_malloc();
	ret->l_value=bg;
	free(str_cpy);
	return ret;
}
