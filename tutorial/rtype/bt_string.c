#include"rtype.h"
#include<string.h>

#define S_TO_R(bts) ((Robject*)bts)
#define R_TO_S(rt) ((BTString*)rt) 
static Robject* bt_string_postfix_get(Robject* left,Robject* right)
{
	if(bt_type(right)==RT_INT)
	{
		char* c_left=R_TO_S(left)->s_value;
		int l_length=R_TO_S(left)->s_length;

		int pos=R_TO_INT(right)->i_value;

		if(pos>=l_length)
		{
			raise_outof_range_error("String Acess Out of Range");
			robject_ref(robject_null)
			return robject_null;
		}
		else
		{
			return bt_string_create_from_char(c_left[pos]);
		}
	}
	else
	{
		raise_type_error("Unsupport Operand for +");
		robject_ref(robject_null)
		return robject_null;
	}

}

static Robject* bt_string_add(Robject* left,Robject* right)
{
	if(bt_type(right)!=RT_STRING)
	{
		raise_type_error("Unsupport Operand for +");
		robject_ref(robject_null)
		return robject_null;
	}
	else
	{
		char* c_left=R_TO_S(left)->s_value;
		int l_length=R_TO_S(left)->s_length;
		char* c_right=R_TO_S(right)->s_value;
		int r_length=R_TO_S(right)->s_length;

		int new_length=l_length+r_length;
		char* new_c=(char*)malloc(new_length+1);

		int i;
		for(;i<l_length;i++)
		{
			new_c[i]=c_left[i];
		}
		for(i=0;i<r_length;i++)
		{
			new_c[i+l_length]=c_right[i];
		}
		new_c[new_length]='\0';
		BTString* ret;
		ret=bt_string_create_with_length(new_c,new_length);
		return S_TO_R(ret);
	}


}
static int bt_string_cmp(Robject* left,Robject* right)
{
	if(bt_type(right)!=RT_STRING)
	{

		raise_type_error("Unsupport Operand for +");
		robject_ref(robject_null)
		return robject_null;
	}
	else 
	{

		char* c_left=R_TO_S(left)->s_value;
		char* c_right=R_TO_S(right)->s_value;
		return strcmp(c_left,c_right);
	}
}
static int bt_string_boolean(Robject* bts)
{
	return 1;
}



static struct rexpr_ops bt_string_expr_ops=
{
	.ro_postfix_get=bt_string_postfix_get,
	.ro_add=bt_string_add,
	.ro_cmp=bt_string_cmp,
	.ro_booleaned=bt_string_boolean,
};

static void bt_string_free(Robject* bts)
{
	BTString* s=R_TO_S(bts);
	free(s->s_value);
	free(s);
}

static Robject_ops bt_string_ops=
{
	.ro_free=bt_string_ops,
};



static void empty_bt_string_free(Robject* bts)
{
}
static Robject_ops empty_bt_string_ops=
{
	.ro_free=empty_bt_string_free,
}

static BTString empty_bt_string=
{
	{&bt_string_expr_ops,&empty_bt_string_ops,1,RT_STRING,"string"},
	"",
	0,
}







static BTString* bt_string_create_internal(char* s,int length);
BTString* bt_string_create_with_length(char* s,int length)
{
	return bt_string_create_internal(s,length);
}
BTString* bt_string_create(char* str)
{
	return bt_string_create_internal(str,strlen(str));

}

BTString* bt_string_create_empty()
{
	 robject_ref(S_TO_R(&empty_bt_string));
	 return &empty_bt_string;
}
BTString* bt_string_create_from_char(char c)
{
	char* str=(char*)malloc(2);
	str[0]=c;
	str[1]='\0';
	return bt_string_create_internal(str,1);
}


	

	











