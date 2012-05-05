#include"gr_string.h"
#include<memory/memory.h>
#include<memory/gc.h>
#include<string.h>
#include<engine/except.h>
#include"gr_int.h"

static size_t gs_str_hash(const char* str)
{
	size_t hash = 1315423911;
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	return hash ;
}	

static inline GrString* gs_malloc()
{
	GrString* val=GrGc_New(GrString,&Gr_Type_String);
	if(val==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For String Object");
	}
	val->s_value=NULL;
	return val;
}


static int gs_init(GrString* gs,const char* str,ssize_t length)
{
	char* val=(char*) GrMem_Alloc(length+1);
	if(val==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For String Object To Init");
		return -1;
	}
	memcpy(val,str,length);
	val[length]='\0';

	gs->s_length=length;
	gs->s_hash=-1;
	gs->s_value=val;
	return 0;
}
static inline int gs_outof_range(GrString* gs,ssize_t index)
{
	if(index<0||index>=gs->s_length)
	{
		return 1;
	}

	return 0;
}



GrString* GrString_GcNew(const char* str)
{
	ssize_t length=strlen(str);
	GrString* gs=gs_malloc();
	if(gs==NULL) return NULL;

	if(gs_init(gs,str,length)<0)
	{
		return  NULL;
	}
	return gs;
}

GrString* GrString_GcNewFlag(const char* str,long flags)
{

	ssize_t length=strlen(str);
	GrString* gs=GrGc_Alloc(GrString,&Gr_Type_String,flags);
	if(gs==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For String Object");
	}
	if(gs_init(gs,str,length)<0)
	{
		return  NULL;
	}
	return gs;
}

GrString* GrString_GcNewEscWithQuote(const char* str)
{
	ssize_t length=strlen(str);
	GrString* gs=gs_malloc();
	if(gs==NULL) return NULL;

	if(gs_init(gs,str+1,length-2)<0)
	{
		return NULL;
	}
	return gs;
}

int GrString_InitEscWithQuote(GrString* gs ,const char* str)
{
	ssize_t length=strlen(str);
	return gs_init(gs,str+1,length-2);
}

int GrString_Init(GrString* gs,const char* str)
{
	ssize_t length=strlen(str);
	return gs_init(gs,str,length);
}

GrString* GrString_Get(GrString* gs,ssize_t index)
{
	if(gs_outof_range(gs,index))
	{
		GrErr_IndexFormat("String Index Out Of Range");
		return NULL;
	}

	char* str=gs->s_value+index;
	
	GrString* ret=gs_malloc();
	if(ret==NULL) return NULL;

	if(gs_init(ret,str,1)<0) return NULL;

	return ret;
}
GrString* GrString_Plus(GrString* x,GrString* y)
{
	char* x_str=x->s_value;
	char* y_str=y->s_value;

	ssize_t x_len=x->s_length;
	ssize_t y_len=y->s_length;

	ssize_t z_len=x_len+y_len;

	GrString* z=GrGc_New(GrString,&Gr_Type_String);
	if(z==NULL) return NULL;

	char* z_str=GrMem_Alloc(z_len+1);
	if(z_str==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For String Object");
		return NULL;
	}

	memcpy(z_str,x_str,x_len);
	memcpy(z_str+x_len,y_str,y_len);
	z_str[z_len]='\0';

	z->s_hash=-1;
	z->s_length=z_len;
	z->s_value=z_str;
	return z;
}

int GrString_Cmp(GrString* x,GrString* y)
{
	return strcmp(x->s_value,y->s_value);
}

int GrString_Bool(GrString* gs)
{
	return gs->s_length!=0;
}

int GrString_Hash(GrString* gs)
{
	if(gs->s_hash!=-1)
	{
		return gs->s_hash;
	}
	ssize_t hash=gs_str_hash(gs->s_value);
	gs->s_hash=hash==-1?-2:hash;
	return hash;
}

int GrString_Print(GrString* gs,FILE* f)
{
	fprintf(f,"\"%s\"",gs->s_value);
	return 0;
}


static int gs_cmp(GrObject* x,GrObject* y)
{
	if(GrString_Verify(y))
	{
		return GrString_Cmp(GR_TO_S(x),GR_TO_S(y));
	}
	return GR_CMP_NOT_SUPPORT;
}
static int gs_rich_eq(GrObject* x,GrObject* y)
{
	if(GrString_Verify(y))
	{
		return strcmp(GR_TO_S(x)->s_value,GR_TO_S(y)->s_value)==0;
	}
	return GR_CMP_NOT_SUPPORT;
}

static GrObject* gs_plus(GrObject* x,GrObject* y)
{
	if(GrString_Verify(y))
	{
		return (GrObject*)GrString_Plus(GR_TO_S(x),GR_TO_S(y));
	}
	return GR_OPS_NOT_SUPPORT;
}

static GrObject* gs_get_item(GrObject* x,GrObject* y)
{
	ssize_t pos;
	if(GrInt_Verify(y))
	{
		pos=GrInt_GetValue(GR_TO_I(y));
		return (GrObject*)GrString_Get(GR_TO_S(x),pos);
	}
	GrErr_IndexFormat("String Index Must Int Object Not '%s'",
					GrObject_Name(y));
	return NULL;
}
					

static struct gr_type_ops string_type_ops=
{
	.t_hash=(GrHashFunc)GrString_Hash,
	.t_print=(GrPrintFunc)GrString_Print,
	.t_rich_eq=gs_rich_eq,

	.t_get_item=gs_get_item,
	.t_plus=gs_plus,
	.t_cmp=gs_cmp,
	.t_bool=(GrBoolFunc)GrString_Bool,
};

struct gr_type_info Gr_Type_String=
{
	.t_name="StringObject",
	.t_size=sizeof(GrString),
	.t_ops=&string_type_ops,
};







