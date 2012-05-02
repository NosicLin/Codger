#include"gr_array.h"
#include<memory/gc.h>
#include<memory/memory.h>
#include<engine/except.h>
#include<utility_c/marocs.h>
#include"gr_int.h"

#define GR_ARRAY_FLAG_PRINT 0x1l

static inline GrArray* ga_malloc()
{
	GrArray* ga=GrGc_New(GrArray,&Gr_Type_Array);
	if(ga==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Array Object");
	}
	return ga;
}


static inline int ga_init(GrArray* ga,size_t size)
{
	GrObject** obs;
	ga->a_flags=0;
	ga->a_size=size;

	if(size<=GR_ARRAY_SMALL_SIZE)
	{
		ga->a_cap=GR_ARRAY_SMALL_SIZE;
		ga->a_objects=ga->a_small_objects;
	}
	else
	{
		obs=GrMem_Alloc(sizeof(*obs)*size);
		if(obs==NULL)
		{
			GrErr_MemFormat("Can't Alloc Memory For Array To Init");
			return -1;
		}
		ga->a_cap=size;
		ga->a_objects=obs;
	}
	return 0;
}

static int ga_enlarge(GrArray* ga,size_t size)
{
	if(size<=GR_ARRAY_SMALL_SIZE)
	{
		WARN("Array Enlarged Size Will Larger Than %d,But is %d",
				GR_ARRAY_SMALL_SIZE,size);
		return -1;
	}

	GrObject** new_obs=(GrObject**)GrMem_Alloc(sizeof(*new_obs)*size);
	if(new_obs==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Array Object To Enlarged");
		return -1;
	}
	GrObject** old_obs=ga->a_objects;
	assert(old_obs);
	int i;
	for(i=0;i<ga->a_size;i++)
	{
		new_obs[i]=old_obs[i];
	}
	if(old_obs!=ga->a_small_objects)
	{
		GrMem_Free(old_obs);
	}
	ga->a_objects=new_obs;
	ga->a_cap=size;
	return 0;
}

static  inline int ga_outof_range(GrArray* ga,ssize_t index)
{
	if(index<0||index>=ga->a_size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

GrArray* GrArray_New()
{
	GrArray* ga=ga_malloc();
	if(ga==NULL) return NULL;

	ga_init(ga,0);
	return ga;
}

GrArray* GrArray_NewWithSize(ssize_t size)
{
	int ret;
	if(size<GR_ARRAY_SMALL_SIZE)
	{
		size=GR_ARRAY_SMALL_SIZE;
	}
	GrArray* ga=ga_malloc();
	if(ga==NULL) return NULL;

	ret=ga_init(ga,size);
	if(ret<0)
	{
		return NULL;
	}
	return  ga;
}


int GrArray_Init(GrArray* ga)
{
	return ga_init(ga,GR_ARRAY_SMALL_SIZE);
}

int GrArray_Push(GrArray* ga,GrObject* item)
{
	int ret;
	if(ga->a_size==ga->a_cap)
	{
		size_t enlarged=ga->a_cap*2;
		/*overflow*/
		if(enlarged<ga->a_cap)
		{
			GrErr_MemFormat("Can't Alloc Memory For Array Object To Push");
			return -1;
		}
		ret=ga_enlarge(ga,enlarged);
		if(ret<0)
		{
			return -1;
		}
	}
	ga->a_objects[ga->a_size++]=item;
	return 0;
}
			
			

GrObject* GrArray_Pop(GrArray* ga)
{
	if(ga->a_size==0)
	{
		GrErr_OutOfRangeFormat("Array Object Is Empty,Can't Pop");
		return NULL;
	}
	return ga->a_objects[--ga->a_size];
}


int GrArray_Set(GrArray* ga,ssize_t index,GrObject* item)
{
	if(ga_outof_range(ga,index))
	{
		GrErr_OutOfRangeFormat("Array Set Index Out Of Range");
		return -1;
	}
	ga->a_objects[index]=item;
	return 0;
}


GrObject* GrArray_Get(GrArray* ga,ssize_t index)
{
	if(ga_outof_range(ga,index))
	{
		GrErr_OutOfRangeFormat("Array Get Index Out Of Range");
		return NULL;
	}
	return ga->a_objects[index];
}



int GrArray_Insert(GrArray* ga,ssize_t index,GrObject* item)
{
	if(index<0||index>ga->a_size)
	{
		GrErr_OutOfRangeFormat("Array Insert Index Out Of Range");
		return -1;
	}
	int ret;
	if(ga->a_size==ga->a_cap)
	{
		size_t enlarged=ga->a_cap*2;
		if(enlarged<ga->a_cap)
		{
			GrErr_MemFormat("Can't Alloc Memory For Array Object To Insert");
			return -1;
		}
		ret=ga_enlarge(ga,enlarged);
		if(ret<0)
		{
			return -1;
		}
	}

	ssize_t i;
	GrObject** obs=ga->a_objects;

	for(i=ga->a_size;i>index;i--)
	{
		obs[i]=obs[i-1];
	}
	obs[index]=item;
	ga->a_size++;
	return 0;
}
int GrArray_Remove(GrArray* ga,ssize_t index)
{
	if(ga_outof_range(ga,index))
	{
		GrErr_OutOfRangeFormat("Array Remove Index Out Of Range");
		return -1;
	}
	ssize_t i=index;
	GrObject** obs=ga->a_objects;
	ssize_t size=ga->a_size;

	for(;i<size-1;i++)
	{
		obs[i]=obs[i+1];
	}
	ga->a_size--;
	return 0;
}


GrArray* GrArray_Plus(GrArray* x ,GrArray* y)
{
	ssize_t x_size=x->a_size;
	GrObject** x_obs=x->a_objects;

	ssize_t y_size=y->a_size;
	GrObject** y_obs=y->a_objects;

	GrArray* m;
	ssize_t m_size=x_size+y_size;
	GrObject** m_obs;

	ssize_t i;
	if(m_size<0)
	{
		GrErr_MemFormat("Can't Alloc Memory For Array Object");
		return NULL;
	}

	m=GrArray_NewWithSize(m_size);
	if(m==NULL)
	{
		return NULL;
	}

	m_obs=m->a_objects;

	for(i=0;i<x_size;i++)
	{
		m_obs[i]=x_obs[i];
	}
	for(i=0;i<y_size;i++)
	{
		m_obs[i+x_size]=y_obs[i];
	}

	m->a_size=m_size;
	return m;
}

int GrArray_Bool(GrArray* ga)
{
	return ga->a_size!=0;
}
int GrArray_Print(GrArray* ga,FILE* f)
{

	if(ga->a_flags&GR_ARRAY_FLAG_PRINT)
	{
		fprintf(f,"[...]");
		return 0;
	}
	ga->a_flags|=GR_ARRAY_FLAG_PRINT;
	if(ga->a_size==0)
	{
		fprintf(f,"[ ]");
		return 0;
	}
	ssize_t size=ga->a_size;
	GrObject** obs=ga->a_objects;
	fprintf(f,"[");
	GrObject_Print(obs[0],f,0);
	ssize_t i=1;
	for(;i<size;i++)
	{
		fprintf(f,",");
		GrObject_Print(obs[i],f,0);
	}

	fprintf(f,"]");
	ga->a_flags&=(~GR_ARRAY_FLAG_PRINT);

	return 0;
}

static int ga_set_item(GrObject* ga,GrObject* index,GrObject* item)
{
	ssize_t pos;
	if(GrInt_Verify(index))
	{
		pos=GR_TO_I(index)->i_value;
		return GrArray_Set(GR_TO_A(ga),pos,item);
	}
	GrErr_IndexFormat("Array Index Must Ingeter, Not '%s'",
			GrObject_Name(index));
	return -1;
}


static GrObject* ga_get_item(GrObject* ga,GrObject* index)
{
	ssize_t pos;
	if(GrInt_Verify(index))
	{
		pos=GR_TO_I(index)->i_value;
		return GrArray_Get(GR_TO_A(ga),pos);
	}
	GrErr_IndexFormat("Array Index Must Ingeter, Not '%s'",
			GrObject_Name(index));
	return NULL;
}

static GrObject* ga_plus(GrObject* x,GrObject* y)
{
	if(GrArray_Verify(y))
	{
		return (GrObject*)GrArray_Plus(GR_TO_A(x),GR_TO_A(y));
	}
	GrErr_TypeFormat("Can't Connect Array Object And '%s'",
					GrObject_Name(y));
	return NULL;
}


static struct gr_operator_ops array_operator_ops=
{
	.t_get_item=ga_get_item,
	.t_set_item=ga_set_item,
	.t_plus=ga_plus,
	.t_bool=(GrBoolFunc)GrArray_Bool,
};

static struct gr_type_ops array_type_ops=
{
	.t_operator=&array_operator_ops,
	.t_hash=GrObject_NotSupportHash,
	.t_print=(GrPrintFunc)GrArray_Print,
};

struct gr_type_info Gr_Type_Array=
{
	.t_name="ArrayObject",
	.t_size=sizeof(GrArray),
	.t_ops=&array_type_ops,
};















