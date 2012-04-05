#include"rtype.h"
#include"bt_array.h"
#include<assert.h>
#include<rstd/redy_std.h>
#include<stdio.h>
#include<utility_c/marocs.h>
#include<object/null_object.h>
#include"bt_int.h"
#include"bt_long.h"

static BtArray* ba_malloc(ssize_t cap);
static int ba_enlarge(BtArray* ba,ssize_t size)
{
	if(size<SMALL_ARRAY_SIZE)
	{
		BUG("Array Enlarged Size Will Larger Than %d But is %d)",
											SMALL_ARRAY_SIZE,size);
		size=SMALL_ARRAY_SIZE;
	}

	Robject** new_obs=(Robject**)ry_malloc(sizeof(*new_obs)*size);
	if(new_obs==NULL)
	{
		ryerr_nomemory();
		return -1;
	}
		
	Robject** old_obs=ba->a_objects;
	assert(old_obs);
	int i;
	for(i=0;i<ba->a_size;i++)
	{
		new_obs[i]=old_obs[i];
	}
	if(old_obs!=ba->a_small_objects)
	{
		ry_free(old_obs);
	}
	ba->a_objects=new_obs;
	ba->a_cap=size;
	return 0;
}

static inline int ba_outof_range(BtArray* ba,ssize_t index)
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

static int ba_set_item(Robject* ro,Robject* index,Robject* item)
{
	int type=rt_type(index);
	BtArray* ba=R_TO_A(ro);
	int pos;
	if(type==RT_INT)
	{
		pos=btint_get(R_TO_I(index));
		return btarray_set_item(ba,pos,item);
	}
	if(type==RT_LONG)
	{
		if(btlong_over_int(R_TO_L(index)))
		{
			except_index_err_format("cannot fix long to int");
			return -1;
		}
		pos=btlong_to_int(R_TO_L(index));
		return btarray_set_item(ba,pos,item);
	}

	except_index_err_format("array index must integer,not '%s'",
							robject_name(index));
	return -1;
}
static Robject* ba_get_item(Robject* ro,Robject* index)
{
	int type=rt_type(index);
	int pos=0;
	BtArray* ba=R_TO_A(ro);
	if(type==RT_INT)
	{
		pos=btint_get(R_TO_I(index));
		return btarray_get_item(ba,pos);
	}
	if(type==RT_LONG)
	{
		if(btlong_over_int(R_TO_L(index)))
		{
			except_index_err_format("cannot fix long to int");
			return NULL;
		}
		pos=btlong_to_int(R_TO_L(index));
		return btarray_get_item(ba,pos);
	}

	except_index_err_format("array index must integer,not '%s'",
							robject_name(index));
	return NULL;
}

static Robject* ba_plus(Robject* l,Robject* r)
{
	int type=rt_type(r);
	if(type!=RT_ARRAY)
	{
		except_type_err_format("cannot concatenate array and '%s'",
								robject_name(r));
		return NULL;
	}

	BtArray* ret= btarray_plus(R_TO_A(l),R_TO_A(r));
	return ret==NULL?NULL:A_TO_R(ret);
}
static int ba_bool(Robject* ro)
{
	BtArray* ba=R_TO_A(ro);
	return btarray_bool(ba);
}
static int ba_print(Robject* ro,FILE* f,int flags)
{
	BtArray* ba=R_TO_A(ro);
	return btarray_print(ba,f,flags);
}




static struct expr_ops ba_expr_ops=
{
	.ro_get_item=ba_get_item,
	.ro_set_item=ba_set_item,
	.ro_plus=ba_plus,
	.ro_bool=ba_bool,
};

static void ba_free(Robject* ro)
{
	BtArray* ba=R_TO_A(ro);
	btarray_free(ba);
}
static struct object_ops array_object_ops=
{
	.ro_free=ba_free,
};

static TypeObject type_array=
{
	.t_name="Array",
	.t_type=RT_ARRAY,
	.t_expr_funcs=&ba_expr_ops,
	.t_object_funcs=&array_object_ops,
	.t_print=ba_print,
};



void btarray_free(BtArray* ba)
{
	assert(ba->a_objects!=NULL);
	int i=0;
	for(;i<ba->a_size;i++)
	{
		robject_release(ba->a_objects[i]);
	}
	if(ba->a_objects!=ba->a_small_objects)
	{
		ry_free(ba->a_objects);
		ba->a_objects=NULL;
	}
	ry_free(ba);
}

int btarray_insert(BtArray* ba,ssize_t index ,Robject* item)
{
	if(index<0||index>ba->a_size)
	{
		except_index_err_format("array index out of range");
		return -1;
	}
	int ret;
	if(ba->a_size==ba->a_cap)
	{
		int enlarged=ba->a_cap*2;
		ret=ba_enlarge( ba,enlarged);
		if(ret<0)
		{
			return -1;
		}
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
	return 0;
}
int btarray_set_item(BtArray* ba,ssize_t index,Robject* item)
{
	if(ba_outof_range(ba,index))
	{
		except_index_err_format("array index out of range");
		return -1;
	}
	robject_addref(item);
	robject_release(ba->a_objects[index]);
	ba->a_objects[index]=item;
	return 0;
}

int btarray_push_back(BtArray* ba,Robject* item)
{
	int ret;
	if(ba->a_size==ba->a_cap)
	{
		int enlarged=ba->a_cap*2;
		ret=ba_enlarge(ba,enlarged);
		if(ret<0)
		{
			return -1;
		}
	}
	robject_addref(item);
	ba->a_objects[ba->a_size++]=item;
	return 0;
}

Robject* btarray_get_item(BtArray* ba,int index)
{
	if(ba_outof_range(ba,index))
	{
		except_index_err_format("array index out of range");
		return NULL;
	}
	Robject* item=ba->a_objects[index];
	robject_addref(item);
	return item;
}
int btarray_remove(BtArray* ba ,ssize_t index)
{
	if(ba_outof_range(ba,index))
	{
		except_index_err_format("array index out of range");
		return -1;
	}
	Robject* item=ba->a_objects[index];
	robject_release(item);
	int i=index;
	int size=ba->a_size;
	Robject** obs=ba->a_objects;
	for(;i<size-1;i++)
	{
		obs[i]=obs[i+1];
	}
	ba->a_size--;
	return 0;
}
BtArray* btarray_plus(BtArray* l,BtArray* r)
{
	int l_size=l->a_size;
	Robject** l_obs=l->a_objects;
	int r_size=r->a_size;
	Robject** r_obs=r->a_objects;
	int m_size=l_size+r_size;
	BtArray* m=ba_malloc(m_size);
	if(m==NULL)
	{
		return NULL;
	}
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
int btarray_print(BtArray* ba,FILE* f,int flags)
{
	if(ba->a_flags&ARRAY_FLAG_PRINT)
	{
		printf("[...]");
		goto over;
	}
	ba->a_flags|=ARRAY_FLAG_PRINT;
	if(ba->a_size==0)
	{
		printf("[ ]");
		goto over;
	}
	ssize_t size=ba->a_size;
	Robject** obs=ba->a_objects;
	printf("[");
	robject_print(obs[0],f,flags&(~PRINT_FLAGS_NEWLINE));
	ssize_t i=1;
	for(;i<size;i++)
	{
		printf(",");
		robject_print(obs[i],f,flags&(~PRINT_FLAGS_NEWLINE));
	}

	printf("]");
over:
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
	ba->a_flags&=(~ARRAY_FLAG_PRINT);
	return 0;
}

static BtArray* ba_malloc(ssize_t cap)
{
	BtArray* ret=ry_malloc(sizeof(*ret));
	if(ret==NULL)
	{
		ryerr_nomemory();
		return NULL;
	}
	if(cap<=SMALL_ARRAY_SIZE)
	{
		ret->a_objects=ret->a_small_objects;
	}
	else
	{
		Robject** array=ry_malloc(sizeof(Robject*)*cap);
		if(array==NULL)
		{
			ry_free(ret);
			ryerr_nomemory();
			return NULL;
		}
		ret->a_objects=array;
	}
	robject_init((Robject*)ret,&type_array);
	ret->a_cap=cap<=SMALL_ARRAY_SIZE?SMALL_ARRAY_SIZE:cap;
	ret->a_size=0;
	ret->a_flags=0;
	return ret;
}
BtArray* btarray_create_size(ssize_t size)
{
	BtArray* ret=ba_malloc(size);
	if(ret==NULL)
	{
		return NULL;
	}
	int i=0;
	Robject** ro=ret->a_objects;
	for(;i<size;i++)
	{
		robject_addref(NullObject);
		ro[i]=NullObject;
	}
	ret->a_size=size;
	return ret;
}


BtArray* btarray_create()
{
	return ba_malloc(0);
}
