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

/*arithmetic expr*/
inline BtFloat* btfloat_div(BtFloat* x,BtFloat* y)
{
	if(y->f_value==0)
	{
		except_divzero_err_format("%s divide or module zero",
				robject_name(F_TO_R(x)));
		return NULL;
	}
	
	float value=x->f_value/y->f_value;
	return btfloat_create(value);
}


inline BtFloat* btfloat_mod(BtFloat* x,BtFloat* y)
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
	return -1;
}



/*hash code*/
ssize_t btfloat_hash(BtFloat* bf);

/* print */
inline int btfloat_print(BtFloat* bf,FILE* f,int flags)
{
	printf("%g",bf->f_value);
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
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
		c_y=R_TO_F(y);
	}
	if(type==RT_INT)
	{
		c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y == NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_MUL,robject_name(x),
							robject_name(y));
		return NULL;
	}
	BtFloat* ret=btfloat_mul(R_TO_F(x),c_y);
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
		c_y=R_TO_F(y);
	}
	if(type==RT_INT)
	{
		c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_DIV,robject_name(x),
							robject_name(y));
		return NULL;
	}
	BtFloat* ret=btfloat_div(R_TO_F(x),c_y);
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
		c_y=R_TO_F(y);
	}
	if(type==RT_INT)
	{
		c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_STRING)
	{
		BtString* c_x=btfloat_to_btstring(R_TO_F(x));
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
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_PLUS,robject_name(x),
							robject_name(y));
		return NULL;
	}
	BtFloat* ret=btfloat_plus(R_TO_F(x),c_y);
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
		c_y=R_TO_F(y);
	}
	if(type==RT_INT)
	{
		c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(type==RT_LONG)
	{
		c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return NULL;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							OPER_MINUS,robject_name(x),
							robject_name(y));
		return NULL;
	}
	BtFloat* ret=btfloat_minus(R_TO_F(x),c_y);
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
		c_y=R_TO_F(y);
	}
	if(type==RT_INT)
	{
		c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return -1;
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
		c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return -1;
		}
	}
	if(c_y==NULL)
	{
		except_type_err_format(MSG_BINARY_UNSUPPORT,
							CMP_NAME(op),robject_name(x),
							robject_name(y));
		return -1;
	}
	int ret=btfloat_cmp(R_TO_F(x),c_y,op);
	robject_release(F_TO_R(c_y));
	return  ret;
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
	return bf_cmp(x,y,CMP_GT);
}

int  bf_rich_cmp(Robject* x,Robject* y,int op)
{
	int type=rt_type(y);
	BtFloat* c_y=NULL;
	if(type==RT_FLOAT)
	{
		robject_addref(y);
		c_y=R_TO_F(y);
	}
	if(type==RT_INT)
	{
		c_y=btint_to_btfloat(R_TO_I(y));
		if(c_y==NULL)
		{
			return -1;
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
		c_y=btlong_to_btfloat(R_TO_L(y));
		if(c_y==NULL)
		{
			return -1;
		}
	}
	if(c_y==NULL)
	{
		return CMP_NOT_SUPPORT;
	}
	int ret=btfloat_cmp(R_TO_F(x),c_y,op);
	robject_release(F_TO_R(c_y));
	return  ret;
}

/* logic operator used for and or not */
static int  bf_bool(Robject* btf)
{
	return btfloat_bool(R_TO_F(btf));
}

static int bf_print(Robject* btf,FILE* f,int flags)
{
	BtFloat* bf=R_TO_F(btf);
	int ret=btfloat_print(bf,f,flags);

	return ret;
}







static struct expr_ops bf_expr_ops=
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
	.t_object_funcs=&float_object_ops,
	.t_rich_cmp=bf_rich_cmp,
	.t_print=bf_print,
};

BtFloat* btfloat_malloc()
{
	return robject_new(BtFloat,&type_float);
}

BtFloat* btfloat_create(float value)
{
	BtFloat* ret=btfloat_malloc();
	if(ret==0)
	{
		return NULL;
	}
	ret->f_value=value;
	return ret;
}

BtFloat* btfloat_from_str(char* str)
{
	BtFloat* ret=btfloat_malloc();
	float value=atof(str);
	ret->f_value=value;
	return ret;
}

