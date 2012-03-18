#include"rtype.h"
#include<string.h>
#include<stdio.h>
#include<utility_c/marocs.h>

static Robject* bs_get_item(Robject* left,Robject* right)
{
	int type=rt_type(right);
	int pos=0;
	if(type==RT_INT)
	{
		 pos=R_TO_I(right)->i_value;
	}
	if(type==RT_LONG)
	{
		BtLong* bl=R_TO_L(right);
		if(bt_long_overflow_int(bl))
		{
			rt_raise_index_error(MSG_LONG_OVERFLOW);
			goto error;
		}
		else
		{
			pos=bt_long_to_int(bl);
		}
	}
	else
	{
		rt_raise_type_error(MSG_STRING_INDEX_TYPE(robject_name(right)));
		goto error;
	}
	BtString* bs=R_TO_S(left);
	if(pos<0)
	{
		rt_raise_value_error(MSG_STRING_INDEX_NEGATIVE);
		goto error;
	}
	if(pos>=bs->s_length)
	{
		rt_raise_index_error(MSG_STRING_OUT_OF_RANGE);
		goto error;
	}
	char* str=bs->s_value;
	BtString* ret=bt_string_from_char(str[pos]);
	return S_TO_R(ret);
error:
	robject_addref(robject_null);
	return robject_null;
}

static Robject* bs_plus(Robject* left,Robject* right)
{
	BtString* new_bs=0;
	if(rt_type(right)!=RT_STRING)
	{
		rt_raise_type_error(MSG_STRING_PLUS(robject_name(right)));
		goto error;
	}
	else
	{
		char* c_left=R_TO_S(left)->s_value;
		int l_length=R_TO_S(left)->s_length;
		char* c_right=R_TO_S(right)->s_value;
		int r_length=R_TO_S(right)->s_length;

		int new_length=l_length+r_length;

		new_bs=bt_string_malloc(new_length);
		char* new_str=new_bs->s_value;

		int i=0;
		for(;i<l_length;i++)
		{
			new_str[i]=c_left[i];
		}
		for(;i<r_length;i++)
		{
			new_str[i+l_length]=c_right[i];
		}
	}
	return S_TO_R(new_bs);
error:
	robject_addref(robject_null);
	return robject_null;


}
static Robject* bs_cmp(Robject* left,Robject* right)
{
	int cmp_value;
	if(rt_type(right)!=RT_STRING)
	{

		rt_raise_type_error(MSG_CMP(robject_name(left),robject_name(right)));
		goto error;
	}
	else 
	{

		char* c_left=R_TO_S(left)->s_value;
		char* c_right=R_TO_S(right)->s_value;
		cmp_value=strcmp(c_left,c_right);
	}
	BtInt* ret=bt_int_create(cmp_value);
	return I_TO_R(ret);

error:
	robject_addref(robject_null);
	return robject_null;
}
static Robject* bs_bool(Robject* bt)
{
	BtString* bs=R_TO_S(bt);
	BtBoolean* ret=bt_boolean_create(bs->s_length);
	return B_TO_R(ret);
}
static void bs_print(Robject* bt)
{
	BtString* bs=R_TO_S(bt);
	printf("%s",bs->s_value);
}

static struct rexpr_ops bs_expr_ops=
{
	.ro_get_item=bs_get_item,
	.ro_plus=bs_plus,
	.ro_cmp=bs_cmp,
	.ro_bool=bs_bool,
	.ro_print=bs_print,
};

static void bs_free(Robject* bts)
{
	BtString* s=R_TO_S(bts);
	free(s);
}

static struct robject_ops bs_ops=
{
	.ro_free=bs_free,
};



static void bs_empty_free(Robject* bts)
{
	/* this func will never called*/
	BUG("Free Empty String");
}
static struct robject_ops bs_empty_string_ops=
{
	.ro_free=bs_empty_free,
};

static BtString* bs_empty_string=0;


BtString* bt_string_malloc(int length)
{
	BtString* bs=(BtString*) malloc(sizeof(*bs)+length+1);
	bs->s_value[length]='\0';
	bs->s_length=length;
	Robject* base=&bs->s_base;
	base->r_expr_ops=&bs_expr_ops;
	base->r_name="String";
	base->r_ops=&bs_ops;
	base->r_ref=1;
	base->r_type=RT_STRING;
	return bs;
}




BtString* bt_string_create(char* str)
{
	int length=strlen(str);
	BtString* bs=bt_string_malloc(length);
	memcpy(bs->s_value,str,length);
	return bs;
}

BtString* bt_string_create_empty()
{
	if(bs_empty_string==0)
	{
		bs_empty_string=bt_string_malloc(0);
		Robject* base=&bs_empty_string->s_base;
		base->r_ops=&bs_empty_string_ops;
	}
	robject_addref(S_TO_R(bs_empty_string));
	return  bs_empty_string;
}

BtString* bt_string_from_char(char c)
{
	BtString* bs=bt_string_malloc(1);
	bs->s_value[0]=c;
	return bs;
}
















