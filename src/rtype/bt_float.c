#include<utility_c/marocs.h>
#include<stdio.h>
#include"bt_float.h"
#include"bt_int.h"
#include"bt_string.h"
#include"bt_long.h"

struct bt_int* btfloat_to_btint(BtFloat* bf)
{
	TODO("BtFloat To Int");
	return NULL;
}
struct bt_string* btfloat_to_btstring(BtFloat* bf)
{
	TODO("BtFloat To String");
	return NULL;
}
struct bt_long* btfloat_to_btlong(BtFloat* bf)
{
	TODO("BtFloat To long");
	return NULL;
}
/*unary expr*/
static inline BtFloat* btfloat_positive(BtFloat* bf)
{
	robject_addref(F_TO_R(bf));
	return bf;
}
static inline BtFloat* btfloat_negative(BtFloat* bf)
{
	float value=-bf->f_value;
	return btfloat_create(value);
}

/*arithmetic expr*/
static inline BtFloat* btfloat_div(BtFloat* x,BtFloat* y)
{
	if(y->f_value==0)
	{
		except_divzero_err_format("%s divide or module zero",
				robject_name(I_TO_R(x)));
		return NULL;
	}
	
	float value=x->f_value/y->f_value;
	return btfloat_create(value);
}


static inline BtFloat* btfloat_mod(BtFloat* x,BtFloat* y)
{
	TODO("Float mod Float ");
	return NULL;
}

/*compare expr*/
int btfloat_cmp(BtFloat* x,BtFloat* y,int op)
{
	switch(op)
	{
		case CMP_LT:
			return btfloat_lt(x,y);
		case CMP_LE:
			return btfloat_le(x,y);
		case CMP_EQ:
			return btfloat_eq(x,y);
		case CMP_NE:
			return btfloat_ne(x,y);
		case CMP_GT:
			return btfloat_gt(x,y);
		case CMP_GE:
			return btfloat_ge(x,y);
	}
	BUG("Error cmpare op(%d)",op);
	return 0;
}



/*hash code*/
ssize_t btfloat_hash(BtFloat* bf);

/* print */
int btfloat_print(BtFloat* bf,FILE* f,int flags)
{
	TODO("Print Float");
	return 0;
}


/* unary oparator + - */
static Robject* bf_negative(Robject* rt)
{
	BtFloat* ret=btfloat_negative(R_TO_F(rt));
	if(ret==NULL)
	{
		return NULL;
	}
	return F_TO_R(ret);
}

static Robject* bf_positive(Robject* rt)
{
	BtFloat* ret=btfloat_positive(R_TO_F(rt));
	if(ret==NULL)
	{
		return NULL;
	}
	return F_TO_R(ret);
}

/* arithmetic operator * /  */
/* float * float =float 
 * float * int =float 
 * float * long =float
 */
static Robject* bf_mul(Robject* x,Robject* y)
{
	int type=rt_type(y);
	BtFloat* c_y=NULL;
	if(type==RT_FLOAT)
	{
		robject_addref(y);
		c_y=y;
	}
	if(type==RT_INT)
	{
		BtFloat* c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		BtFloat* c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							robject_name(x),
							robject_name(y),OPER_MUL);
		return NULL;
	}
	BtFloat* ret=btfloat_mul(x,c_y);
	robject_release(F_TO_R(c_y));
	if(ret==NULL)
	{
		return NULL;

	}
	return F_TO_R(ret);

}

/* float / float =Float
 * float / int =float 
 * float / long =float 
 */
static Robject* bf_div(Robject* x,Robject* y)
{
	int type=rt_type(y);
	BtFloat* c_y=NULL;
	if(type==RT_FLOAT)
	{
		robject_addref(y);
		c_y=y;
	}
	if(type==RT_INT)
	{
		BtFloat* c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		BtFloat* c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							robject_name(x),
							robject_name(y),OPER_DIV);
		return NULL;
	}
	BtFloat* ret=btfloat_div(x,c_y);
	robject_release(F_TO_R(c_y));
	if(ret==NULL)
	{
		return NULL;

	}
	return F_TO_R(ret);
}

/*arithmetic  + - */

/* float + float =Float
 * float + int =float 
 * float + long =float 
 */
static Robject* bf_plus(Robject* x,Robject* y)
{
	int type=rt_type(y);
	BtFloat* c_y=NULL;
	if(type==RT_FLOAT)
	{
		robject_addref(y);
		c_y=y;
	}
	if(type==RT_INT)
	{
		BtFloat* c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		BtFloat* c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_STRING)
	{
		BtString* c_x=btfloat_to_btstring(F_TO_R(x));
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
		return ret;
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							robject_name(x),
							robject_name(y),OPER_PLUS);
		return NULL;
	}
	BtFloat* ret=btfloat_plus(x,c_y);
	robject_release(F_TO_R(c_y));
	if(ret==NULL)
	{
		return NULL;

	}
	return F_TO_R(ret);
	
}


/* float - float =Float
 * float - int =float 
 * float - long =float 
 */
static Robject* bf_minus(Robject* x,Robject* y)
{
	int type=rt_type(y);
	BtFloat* c_y=NULL;
	if(type==RT_FLOAT)
	{
		robject_addref(y);
		c_y=y;
	}
	if(type==RT_INT)
	{
		BtFloat* c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		BtFloat* c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							robject_name(x),
							robject_name(y),OPER_MINUS);
		return NULL;
	}
	BtFloat* ret=btfloat_minus(x,c_y);
	robject_release(F_TO_R(c_y));
	if(ret==NULL)
	{
		return NULL;

	}
	return F_TO_R(ret);
}


/* cmp operator used for lt le eq ne ge gt */

int  bf_cmp(Robject* x,Robject* y,int op)
{
	int type=rt_type(y);
	BtFloat* c_y=NULL;
	if(type==RT_FLOAT)
	{
		robject_addref(y);
		c_y=y;
	}
	if(type==RT_INT)
	{
		BtFloat* c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		if(btlong_over_float(R_TO_L(y)))
		{
			switch(op)
			{
				case CMP_LT:
					return 1;
				case CMP_LE:
					return 1;
				case CMP_EQ:
					return 0;
				case CMP_NE:
					return 1;
				case CMP_GT:
					return 0;
				case CMP_GE:
					return 0;
			}
			BUG("Error cmpare op(%d)",op);
		}
		BtFloat* c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							robject_name(x),
							robject_name(y),CMP_NAME(op));
		return NULL;
	}
	BtFloat* ret=btfloat_cmp(x,c_y,op);
	robject_release(F_TO_R(c_y));
	if(ret==NULL)
	{
		return NULL;

	}
	return F_TO_R(ret);
}
static int bf_lt(Robject* x,Robject* y)
{
	return bf_cmp(x,y,CMP_LT);
}
static int bf_le(Robject* x,Robject* y)
{
	return bf_cmp(x,y,CMP_LE);
}
static int bf_eq(Robject* x,Robject* y)
{
	return bf_cmp(x,y,CMP_EQ);
}
static int bf_ne(Robject* x,Robject* y)
{
	return bf_cmp(x,y,CMP_NE);
}
static int bf_ge(Robject* x,Robject* y)
{
	return bf_cmp(x,y,CMP_GE);
}

static int bf_gt(Robject* x,Robject* y)
{
	return bf_cmp(x,y,CMP_Gt);
}

/* logic operator used for and or not */
static int  bf_bool(Robject* btf)
{
	return btfloat_bool(btf);
}

static int bf_print(Robject* btf,FILE* f,int flags)
{
	printf("%g",R_TO_F(btf)->f_value);
	return 0;
}







static struct rexpr_ops bf_expr_ops=
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

	/*compare operator*/
	.ro_lt=bf_lt,
	.ro_le=bf_le,
	.ro_ge=bf_ge,
	.ro_gt=bf_gt,
	.ro_ne=bf_ne,
	.ro_eq=bf_eq,
	/* logic operator */
	.ro_bool=bf_bool,

	/* print */
	.ro_print=bf_print,

};


static void bf_free(Robject* bt)
{
	free(R_TO_F(bt));
}

static struct object_ops float_object_ops=
{
	.ro_free=bf_free,
};

static TypeObject type_float=
{
	.t_name="Float",
	.t_type=RT_FLOAT,
	.t_expr_funcs=&bf_expr_ops,
	.t_object_func=&float_object_ops,
};

BtFloat* bt_float_malloc()
{
	return robject_new(BtFloat,&type_float);
}

BtFloat* bt_float_create(float value)
{
	BtFloat* ret=bt_float_malloc();
	if(ret==0)
	{
		return NULL;
	}
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

