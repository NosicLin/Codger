#include<string.h>
#include<stdio.h>
#include<utility_c/marocs.h>
#include"bt_string.h"
#include"bt_long.h"
#include"bt_int.h"
#include"bt_float.h"

/*FIXME  find this hash function  from google ,
 * so i'm not sure whether it is good or not. 
 * only kown js use it 
 */
static size_t __string_hash(char* str)
{
	size_t hash = 1315423911;
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	return hash ;
}	



BtString* btstring_get_item(BtString* bs,int index)
{
	if(index>=bs->s_length)
	{
		except_index_err_format("string index out of range");
		return NULL;
	}
	return btstring_from_char(bs->s_value[index]);
}


BtString* btstring_plus(BtString* x,BtString* y)
{
	char* c_x=x->s_value;
	int l_length=x->s_length;
	char* c_y=y->s_value;
	int r_length=y->s_length;
	int new_length=l_length+r_length;
	BtString* new_bs=0;
	new_bs=btstring_malloc(new_length);

	if(new_bs==NULL) return NULL;

	char* new_str=new_bs->s_value;

	int i=0;
	for(;i<l_length;i++)
	{
		new_str[i]=c_x[i];
	}
	for(i=0;i<r_length;i++)
	{
		new_str[i+l_length]=c_y[i];
	}
	new_bs->s_hash=__string_hash(new_bs->s_value);
	return new_bs;
}

int btstring_cmp(BtString* x,BtString* y,int op)
{
	switch(op)
	{
		case CMP_LT:
			return btstring_lt(x,y);
		case CMP_LE:
			return btstring_le(x,y);
		case CMP_GE:
			return btstring_ge(x,y);
		case CMP_GT:
			return btstring_gt(x,y);
		case CMP_NE:
			return btstring_ne(x,y);
		case CMP_EQ:
			return btstring_eq(x,y);
	}
	BUG("Error cmpare op(%d)",op);
	return -1;
}

static Robject* bs_get_item(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_INT)
	{
		int index=btint_get(R_TO_I(y));
		BtString* ret=btstring_get_item(R_TO_S(x),index);
		return ret==NULL?NULL:S_TO_R(ret);
	}
	if(type==RT_LONG)
	{
		if(btlong_over_int(R_TO_L(y)))
		{
			except_index_err_format("cannot fix long to int");
			return NULL;
		}
		int index=btlong_to_int(R_TO_L(y));
		BtString* ret=btstring_get_item(R_TO_S(x),index);
		return ret==NULL?NULL:S_TO_R(ret);
	}
	except_type_err_format("string index must integer,not '%s'",
							robject_name(y));
	return NULL;


}

static Robject* bs_plus(Robject* x,Robject* y)
{
	int type=rt_type(y);
	if(type==RT_STRING)
	{
		BtString* ret=btstring_plus(R_TO_S(x),R_TO_S(y));
		return ret==NULL?NULL:S_TO_R(ret);
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT, 
							OPER_PLUS,robject_name(x),
							robject_name(y));
	return NULL;
}
static int  bs_cmp(Robject* x,Robject* y,int op)
{
	int type=rt_type(y);
	if(type==RT_STRING)
	{
		int ret=btstring_cmp(R_TO_S(x),R_TO_S(y),op);
		return ret;
	}
	except_type_err_format(MSG_BINARY_UNSUPPORT,
							CMP_NAME(op),robject_name(x),
							robject_name(y));
	return -1;
}
static int  bs_rich_cmp(Robject* x,Robject* y,int op)
{
	int type=rt_type(y);
	if(type==RT_STRING)
	{
		int ret=btstring_cmp(R_TO_S(x),R_TO_S(y),op);
		return ret;
	}
	return CMP_NOT_SUPPORT;
}
static int bs_lt(Robject* x,Robject* y)
{
	return bs_cmp(x,y,CMP_LT);
}
static int bs_le(Robject* x,Robject* y)
{
	return bs_cmp(x,y,CMP_LE);
}

static int bs_ge(Robject* x,Robject* y)
{
	return bs_cmp(x,y,CMP_GE);
}

static int bs_gt(Robject* x,Robject* y)
{
	return bs_cmp(x,y,CMP_GT);
}

static int bs_eq(Robject* x,Robject* y)
{
	return bs_cmp(x,y,CMP_EQ);
}

static int bs_ne(Robject* x,Robject* y)
{
	return bs_cmp(x,y,CMP_NE);
}

static int  bs_bool(Robject* bt)
{
	return btstring_bool(R_TO_S(bt));
}

static int bs_print(Robject* bt,FILE* f,int flags)
{
	BtString* bs=R_TO_S(bt);
	printf("\"%s\"",bs->s_value);
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
	return 0;
}

static ssize_t bs_hash(Robject* bt)
{
	BtString* bs=R_TO_S(bt);
	return btstring_hash(bs);
}
	
static struct expr_ops bs_expr_ops=
{
	.ro_get_item=bs_get_item,
	.ro_plus=bs_plus,
	.ro_lt=bs_lt,
	.ro_le=bs_le,
	.ro_gt=bs_gt,
	.ro_ge=bs_ge,
	.ro_eq=bs_eq,
	.ro_ne=bs_ne,
	.ro_bool=bs_bool,
};

static void bs_free(Robject* bts)
{
	BtString* s=R_TO_S(bts);
	free(s);
}

static struct object_ops string_object_ops=
{
	.ro_free=bs_free,
};

static TypeObject type_string=
{
	.t_name="String",
	.t_type=RT_STRING,
	.t_expr_funcs=&bs_expr_ops,
	.t_object_funcs=&string_object_ops,
	.t_rich_cmp=bs_rich_cmp,
	.t_print=bs_print,
	.t_hash=bs_hash,
};





BtString* btstring_malloc(int length)
{
	BtString* ret=(BtString*)ry_malloc(sizeof(*ret)+length+1);
	if(ret==NULL)
	{
		ryerr_nomemory();
		return NULL;
	}
	robject_init((Robject*)ret,&type_string);

	ret->s_value[length]=0;
	ret->s_length=length;
	return ret;
}



/*FIXME  escape special character */
BtString* btstring_create(char* str)
{
	int length=strlen(str);
	BtString* bs=btstring_malloc(length-2);
	if(bs==NULL)
	{
		return NULL;
	}
	memcpy(bs->s_value,str+1,length-2);
	bs->s_hash=__string_hash(bs->s_value);
	return bs;
}
BtString* btstring_create_no_esc(char* str)
{
	int length=strlen(str);
	BtString* bs=btstring_malloc(length);
	if(bs==NULL)
	{
		return NULL;
	}
	memcpy(bs->s_value,str,length);
	bs->s_hash=__string_hash(bs->s_value);
	return bs;
}

BtString* btstring_from_char(char c)
{
	BtString* bs=btstring_malloc(1);
	if(bs==NULL)
	{
		return NULL;
	}
	bs->s_value[0]=c;
	bs->s_hash=__string_hash(bs->s_value);
	return bs;
}
















