#include"rtype.h"
#include<stdlib.h>
#include<stdio.h>
#include<utility_c/marocs.h>
#define ARRAY_DEFAULT_CAP 8 

static void bt_array_enlarge(BtArray* ba,int size)
{
	if(size<ARRAY_DEFAULT_CAP)
	{
		size=ARRAY_DEFAULT_CAP;
	}
	Robject** new_obs=(Robject**)malloc(sizeof(*new_obs)*size);
	Robject** old_obs=ba->a_objects;
	if(old_obs)
	{
		int i;
		for(i=0;i<ba->a_size;i++)
		{
			new_obs[i]=old_obs[i];
		}
		free(old_obs);
	}
	ba->a_objects=new_obs;
	ba->a_cap=size;
}

int ba_outof_range(BtArray* ba,int index)
{
	if(index<0||index>=ba->a_size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




static void ba_set_item(Robject* bt,Robject* index,Robject* item)
{
	BtArray* ba=R_TO_A(bt);
	int pos=0;
	int index_type=rt_type(index);
	if(index_type==RT_INT)
	{
		pos=bt_int_get(R_TO_I(index));
	}
	else if (index_type==RT_LONG)
	{
		if(bt_long_overflow_int(R_TO_L(index)))
		{
			rt_raise_overflow(MSG_LONG_OVERFLOW);
			goto error;
		}
		pos=bt_long_to_int(R_TO_L(index));
	}
	else
	{
		rt_raise_index_error(MSG_ARRAY_INDEX_TYPE(robject_name(index)));
		goto error;
	}

	if(ba_outof_range(ba,pos))
	{
		rt_raise_index_error(MSG_ARRAY_OUT_OF_RANGE);
		goto error;
	}
	
	Robject* old_item=ba->a_objects[pos];
	robject_addref(item);
	robject_release(old_item);
	ba->a_objects[pos]=item;
	return ;
error:
	return ;
}
static Robject* ba_get_item(Robject* bt,Robject* index)
{
	BtArray* ba=R_TO_A(bt);
	int pos=0;
	int index_type=rt_type(index);
	if(index_type==RT_INT)
	{
		pos=bt_int_get(R_TO_I(index));
	}
	else if (index_type==RT_LONG)
	{
		if(bt_long_overflow_int(R_TO_L(index)))
		{
			rt_raise_overflow(MSG_LONG_OVERFLOW);
			goto error;
		}
		pos=bt_long_to_int(R_TO_L(index));
	}
	else
	{
		rt_raise_index_error(MSG_ARRAY_INDEX_TYPE(robject_name(index)));
		goto error;
	}

	if(ba_outof_range(ba,pos))
	{
		rt_raise_index_error(MSG_ARRAY_OUT_OF_RANGE);
		goto error;
	}
	Robject* ro=ba->a_objects[pos];
	robject_addref(ro);
	return ro;
error:
	robject_addref(robject_null);
	return robject_null;
}

static Robject* ba_plus(Robject* left,Robject* right)
{
	int type=rt_type(right);
	if(type!=RT_ARRAY)
	{
		rt_raise_type_error(MSG_OPER(robject_name(left),robject_name(right),OPER_PLUS));
		goto error;
	}
	BtArray* con=bt_array_merge(R_TO_A(left),R_TO_A(right));
	return A_TO_R(con);
error:
	robject_addref(robject_null);
	return robject_null;
}

static Robject* ba_bool(Robject* bt)
{
	int size=R_TO_A(bt)->a_size;
	BtBoolean* ret=0;
	if(size)
	{
		ret=bt_boolean_create(1);
	}
	else
	{
		ret=bt_boolean_create(0);
	}
	return B_TO_R(ret);
}

static void ba_print(Robject* bt)
{
	BtArray* ba=R_TO_A(bt);
	
	int size=ba->a_size;
	Robject** obs=ba->a_objects;
	
	if(size==0)
	{
		printf("[]");
		return ;
	}
	printf("[");
	int i=0;
	robject_print(obs[0]);
	i++;
	for(;i<size;i++)
	{
		printf(",");
		robject_print(obs[i]);
	}
	printf("]");
}

static struct rexpr_ops ba_expr_ops=
{
	.ro_get_item=ba_get_item,
	.ro_set_item=ba_set_item,
	.ro_plus=ba_plus,
	.ro_bool=ba_bool,
	.ro_print=ba_print,
};

static void ba_free(Robject* bt)
{
	bt_array_free(R_TO_A(bt));
}
static struct robject_ops ba_ops=
{
	.ro_free=ba_free,
};
	
BtArray* bt_array_malloc(int cap)
{
	if(cap<ARRAY_DEFAULT_CAP)
	{
		cap=ARRAY_DEFAULT_CAP;
	}
	BtArray* ret=(BtArray*)malloc(sizeof(*ret));
	Robject** obs=(Robject**)malloc(sizeof(*obs)*cap);
	ret->a_cap=cap;
	ret->a_size=0;
	ret->a_objects=obs;

	Robject* base=&ret->a_base;
	base->r_expr_ops=&ba_expr_ops;
	base->r_name="Array";
	base->r_ops=&ba_ops;
	base->r_ref=1;
	base->r_type=RT_ARRAY;
	return ret;
}
BtArray* bt_array_create()
{
	return bt_array_malloc(ARRAY_DEFAULT_CAP);
}
void bt_array_free(BtArray* ba)
{
	if(ba->a_objects!=NULL)
	{
		int i=0;
		for(;i<ba->a_size;i++)
		{
			robject_release(ba->a_objects[i]);
		}
		free(ba->a_objects);
		ba->a_objects=NULL;
	}
	free(ba);
}

void bt_array_insert(BtArray* ba,int index,Robject* item)
{
	BUG_ON(index<0||index>=ba->a_size,"Access OutOF Pos");
	if(ba->a_size==ba->a_cap)
	{
		int enlarged=ba->a_cap*2;
		bt_array_enlarge( ba,enlarged);
		ba->a_cap=enlarged;
	}
	int i;
	Robject** obs=ba->a_objects;
	for(i=ba->a_size;i>index;i--)
	{
		obs[i]=obs[i-1];
	}
	robject_addref(item);
	obs[index]=item;
	ba->a_size++;
}
void bt_array_set_item(BtArray* ba,int index,Robject* item)
{
	BUG_ON(index<0||index>=ba->a_size,"Access OutOF Pos");
	robject_addref(item);
	robject_release(ba->a_objects[index]);
	ba->a_objects[index]=item;
}

void bt_array_push_back(BtArray* ba,Robject* item)
{
	if(ba->a_size==ba->a_cap)
	{
		int enlarged=ba->a_cap*2;
		bt_array_enlarge( ba,enlarged);
		ba->a_cap=enlarged;
	}
	robject_addref(item);
	ba->a_objects[ba->a_size++]=item;
}

Robject* bt_array_get_item(BtArray* ba,int index)
{
	BUG_ON(index<0||index>=ba->a_size,"Access OutOF Pos");
	Robject* item=ba->a_objects[index];
	robject_addref(item);
	return item;
}
void bt_array_remove(BtArray* ba ,int index)
{
	BUG_ON(index<0||index>=ba->a_size,"Access OutOF Pos");
	Robject* item=ba->a_objects[index];
	robject_release(item);
	int i=index;
	int size=ba->a_size;
	Robject** obs=ba->a_objects;
	for(;i<size-1;i++)
	{
		obs[i]=obs[i+1];
	}
}
BtArray* bt_array_merge(BtArray* l,BtArray* r)
{
	int l_size=l->a_size;
	Robject** l_obs=l->a_objects;
	int r_size=r->a_size;
	Robject** r_obs=r->a_objects;
	int m_size=l_size+r_size;
	BtArray* m=bt_array_malloc(m_size);
	Robject** m_obs=m->a_objects;

	int i;
	for(i=0;i<l_size;i++)
	{
		m_obs[i]=l_obs[i];
		robject_addref(l_obs[i]);
	}
	for(i=0;i<r_size;i++)
	{
		m_obs[i+l_size]=r_obs[i];
		robject_addref(r_obs[i]);
	}
	m->a_size=m_size;
	return m;
}

