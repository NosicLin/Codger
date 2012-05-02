#include"gr_object.h"
#include<engine/except.h>
#include<assert.h>

static GrObject __gr_ops_not_support;
GrObject* GR_OPS_NOT_SUPPORT=&__gr_ops_not_support;


int GrObject_Cmp(GrObject*,GrObject*,int op);

int GrObject_RichEq(GrObject* x,GrObject* y)
{
	int ret;
	GrTypeInfo* t_x=x->g_type;
	GrTypeInfo* t_y=y->g_type;
	if(t_x->t_ops->t_rich_eq!=0)
	{
		ret=t_x->t_ops->t_rich_eq(x,y);
		if(ret!=GR_CMP_NOT_SUPPORT)
		{
			return ret;
		}
	}
	if(t_y->t_ops->t_rich_eq!=0)
	{
		ret=t_y->t_ops->t_rich_eq(y,x);
		if(ret!=GR_CMP_NOT_SUPPORT)
		{
			return ret;
		}
	}
	return x==y;
}




ssize_t GrObject_Hash(GrObject* x)
{
	assert(x);
	GrTypeInfo* t_x=x->g_type;
	ssize_t ret;
	if(t_x->t_ops->t_hash!=0)
	{
		ret=t_x->t_ops->t_hash(x);
		if(ret==-1)
		{
			if(!GrExcept_Happened())
			{
				GrErr_BugFromat("Interal Bug For %s Hash Func",
						GrObject_Name(x));
			}
		}
		return ret;
	}
	else
	{
		return ((ssize_t) x)==-1?-2:(ssize_t) x;
	}
}

ssize_t GrObject_NotSupportHash(GrObject* x)
{
	GrErr_HashFormat("%s Not Support Hash");
	return -1;
}
int GrObject_Print(GrObject* x,FILE* f,long flags)
{
	GrTypeInfo* t_x=x->g_type;
	int ret=0;
	if(t_x->t_ops->t_print!=0)
	{
		ret=t_x->t_ops->t_print(x,f);
		if(ret<0)
		{
			if(!GrExcept_Happened())
			{
				GrErr_BugFromat("Interal Bug For %s Print Func",
								GrObject_Name(x));
				return ret;
			}
		}
	}
	else 
	{
		fprintf(f,"%s At %x",GrObject_Name(x),(size_t)x);
	}

	if(flags&GR_PRINT_SPACE)
	{
		fprintf(f," ");
	}
	if(flags&GR_PRINT_TAB)
	{
		fprintf(f,"\t");
	}
	if(flags&GR_PRINT_NEWLINE)
	{
		fprintf(f,"\n");
	}
	return ret;
}

const char* GrObject_Name(GrObject* x)
{
	return x->g_type->t_name;
}
	













