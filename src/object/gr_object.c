#include"gr_object.h"
#include<engine/except.h>
#include<assert.h>

static GrObject __gr_ops_not_support;
GrObject* GR_OPS_NOT_SUPPORT=&__gr_ops_not_support;


int GrObject_Cmp(GrObject*,GrObject*,int op);

int GrObject_RichEq(GrObject* x,GrObject* y)
{
	return GrObject_Eq(x,y);
	/*
	int ret;
	GrTypeInfo* t_x=GrObject_Type(x);
	GrTypeInfo* t_y=GrObject_Type(y);
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
	*/
}




ssize_t GrObject_Hash(GrObject* x)
{
	assert(x);
	GrTypeInfo* t_x=GrObject_Type(x);
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
	GrTypeInfo* t_x=GrObject_Type(x);
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
	return GrObject_Type(x)->t_name;
}
	



struct gr_type_ops GR_TYPE_OPS_NOT_SUPPORT=
{
	
};


GrObject* GrObject_Positive(GrObject* gs)
{
	GrObject* ret;
	struct gr_type_ops* t_ops=GrObject_Type(gs)->t_ops;
	if(!t_ops->t_positive)
	{
		goto defalut_action;
	}
	ret=t_ops->t_positive(gs);
	if(ret==NULL)
	{
		if(!GrExcept_Happened())
		{
			GrErr_BugFromat("Interal Bug For %s Positive Func",
					GrObject_Name(gs));
		}

	}
	return ret;
defalut_action:
	GrErr_TypeFormat("%s Not Support Operand '+'",GrObject_Name(gs));
	return NULL;
}


GrObject* GrObject_Negative(GrObject* gs)
{
	GrObject* ret;
	struct gr_type_ops* t_ops=GrObject_Type(gs)->t_ops;
	if(!t_ops->t_negative)
	{
		goto defalut_action;
	}
	ret=t_ops->t_negative(gs);
	if(ret==NULL)
	{
		if(!GrExcept_Happened())
		{
			GrErr_BugFromat("Interal Bug For %s Positive Func",
					GrObject_Name(gs));
		}

	}
	return ret;
defalut_action:
	GrErr_TypeFormat("%s Not Support Operand '-'",GrObject_Name(gs));
	return NULL;
}

GrObject* GrObject_Negated(GrObject* gs)
{
	GrObject* ret;
	struct gr_type_ops* t_ops=GrObject_Type(gs)->t_ops;
	if(!t_ops->t_negated)
	{
		goto defalut_action;
	}
	ret=t_ops->t_negated(gs);
	if(ret==NULL)
	{
		if(!GrExcept_Happened())
		{
			GrErr_BugFromat("Interal Bug For %s Positive Func",
					GrObject_Name(gs));
		}

	}
	return ret;
defalut_action:
	GrErr_TypeFormat("%s Not Support Operand '~'",GrObject_Name(gs));
	return NULL;
}


/*FIXME not suggest to use marocs,but for quick build */

#define Gr_OBJECT_BINARY_OPS(H,M,L,S) \
GrObject* GrObject_##M(GrObject* x,GrObject* y) \
{ \
	GrObject* ret; \
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops; \
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops; \
	if(!x_ops->t_##L) \
	{ \
		goto reverse; \
	} \
	ret=x_ops->t_##L(x,y); \
	if(ret==NULL)  \
	{ \
		if(!GrExcept_Happened()) \
		{ \
			GrErr_BugFromat("Interal Bug For %s and %s"#M"Func", \
					GrObject_Name(x),GrObject_Name(y)); \
		} \
		return NULL; \
	} \
	if(ret==GR_OPS_NOT_SUPPORT) \
	{\
		goto reverse; \
	} \
	return ret; \
reverse: \
	if(!y_ops->t_##L##_reverse) \
	{ \
		goto defalut_action; \
	} \
	ret=y_ops->t_##L##_reverse(y,x); \
	if(ret==NULL) \
	{ \
		if(!GrExcept_Happened()) \
		{ \
			GrErr_BugFromat("Interal Bug For %s and %s"#M"Reverse Func", \
					GrObject_Name(x),GrObject_Name(y)); \
			return NULL; \
		} \
	} \
	if(ret==GR_OPS_NOT_SUPPORT) \
	{ \
		goto defalut_action; \
	}\
	return ret; \
defalut_action: \
	GrErr_TypeFormat("Not Support Operand '"#S"' For '%s' and '%s'", \
				GrObject_Name(x),GrObject_Name(y)); \
	return NULL; \
}


Gr_OBJECT_BINARY_OPS(MUL,Mul,mul,*);
Gr_OBJECT_BINARY_OPS(DIV,Div,div,/);
Gr_OBJECT_BINARY_OPS(MOD,Mod,mod,%%);
Gr_OBJECT_BINARY_OPS(PLUS,Plus,plus,+);
Gr_OBJECT_BINARY_OPS(MINUS,Minus,minus,-);
Gr_OBJECT_BINARY_OPS(LSHIFT,LShift,lshift,<<);
Gr_OBJECT_BINARY_OPS(RSHIFT,RShift,rshift,>>);
Gr_OBJECT_BINARY_OPS(AND,And,and,&);
Gr_OBJECT_BINARY_OPS(XOR,Xor,xor,^);
Gr_OBJECT_BINARY_OPS(OR,Or,or,|);

int GrObject_Lt(GrObject* x,GrObject* y)
{
	int ret;
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops;
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops;
	if(!x_ops->t_cmp)
	{
		goto  reverse;
	}
	ret=x_ops->t_cmp(x,y);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto reverse;
	}
	return ret==-1;
reverse:
	if(!y_ops->t_cmp_reverse(y,x))
	{
		goto defalut_action;
	}
	ret=y_ops->t_cmp_reverse(y,x);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto defalut_action;
	}
	return ret==-1;
defalut_action:
	GrErr_TypeFormat("Not Support Operand '<' For '%s' and '%s'",
			GrObject_Name(x),GrObject_Name(y));
	return GR_CMP_NOT_SUPPORT;
}


int GrObject_Le(GrObject* x,GrObject* y)
{
	int ret;
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops;
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops;
	if(!x_ops->t_cmp)
	{
		goto  reverse;
	}
	ret=x_ops->t_cmp(x,y);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto reverse;
	}
	return ret==-1||ret==0;
reverse:
	if(!y_ops->t_cmp_reverse(y,x))
	{
		goto defalut_action;
	}
	ret=y_ops->t_cmp_reverse(y,x);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto defalut_action;
	}
	return ret==-1||ret==0;
defalut_action:
	GrErr_TypeFormat("Not Support Operand '<=' For '%s' and '%s'",
			GrObject_Name(x),GrObject_Name(y));
	return GR_CMP_NOT_SUPPORT;
}

int GrObject_Ge(GrObject* x,GrObject* y)
{
	int ret;
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops;
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops;
	if(!x_ops->t_cmp)
	{
		goto  reverse;
	}
	ret=x_ops->t_cmp(x,y);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto reverse;
	}
	return ret==1||ret==0;
reverse:
	if(!y_ops->t_cmp_reverse(y,x))
	{
		goto defalut_action;
	}
	ret=y_ops->t_cmp_reverse(y,x);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto defalut_action;
	}
	return ret==1||ret==0;
defalut_action:
	GrErr_TypeFormat("Not Support Operand '>=' For '%s' and '%s'",
			GrObject_Name(x),GrObject_Name(y));
	return GR_CMP_NOT_SUPPORT;
}

int GrObject_Gt(GrObject* x,GrObject* y)
{
	int ret;
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops;
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops;
	if(!x_ops->t_cmp)
	{
		goto  reverse;
	}
	ret=x_ops->t_cmp(x,y);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto reverse;
	}
	return ret==1;
reverse:
	if(!y_ops->t_cmp_reverse(y,x))
	{
		goto defalut_action;
	}
	ret=y_ops->t_cmp_reverse(y,x);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto defalut_action;
	}
	return ret==1;
defalut_action:
	GrErr_TypeFormat("Not Support Operand '>' For '%s' and '%s'",
			GrObject_Name(x),GrObject_Name(y));
	return GR_CMP_NOT_SUPPORT;
}



int GrObject_Eq(GrObject* x,GrObject* y)
{
	int ret;
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops;
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops;
	if(!x_ops->t_cmp)
	{
		goto  reverse;
	}
	ret=x_ops->t_cmp(x,y);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto reverse;
	}
	return ret==0;
reverse:
	if(!y_ops->t_cmp_reverse(y,x))
	{
		goto defalut_action;
	}
	ret=y_ops->t_cmp_reverse(y,x);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto defalut_action;
	}
	return ret==0;
defalut_action:
	return x==y;
}

int GrObject_Ne(GrObject* x,GrObject* y)
{
	int ret;
	struct gr_type_ops* x_ops=GrObject_Type(x)->t_ops;
	struct gr_type_ops* y_ops=GrObject_Type(y)->t_ops;
	if(!x_ops->t_cmp)
	{
		goto  reverse;
	}
	ret=x_ops->t_cmp(x,y);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto reverse;
	}
	return ret==-1||ret==1;
reverse:
	if(!y_ops->t_cmp_reverse(y,x))
	{
		goto defalut_action;
	}
	ret=y_ops->t_cmp_reverse(y,x);
	if(ret==GR_CMP_NOT_SUPPORT)
	{
		goto defalut_action;
	}
	return ret==-1||ret==1;
defalut_action:
	return x!=y;
}










