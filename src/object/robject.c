#include "robject.h"
#include"type_object.h"
#include<utility_c/marocs.h>
#include<rstd/redy_std.h>
#include<stdio.h>
#include<assert.h>
#include<vm/except.h>

#define OPER_NAME_MUL "*"
#define OPER_NAME_DIV "/"
#define OPER_NAME_MOD "%"
#define OPER_NAME_PLUS "+"
#define OPER_NAME_MINUS "-"
#define OPER_NAME_LSHIFT "<<"
#define OPER_NAME_RSHIFT ">>"
#define OPER_NAME_CMP "cmp"
#define OPER_NAME_LE "<="
#define OPER_NAME_LT "<"
#define OPER_NAME_GE ">="
#define OPER_NAME_GT ">"
#define OPER_NAME_NE "!="
#define OPER_NAME_EQ "=="
#define OPER_NAME_AND "&"
#define OPER_NAME_OR "|"
#define OPER_NAME_XOR "^"
#define OPER_NAME_NEGATIVE "-"
#define OPER_NAME_NEGATED "~"
#define OPER_NAME_POSITIVE "+"
#define OPER_NAME_GET_ITEM "[ ]"

static inline char* EXPR_NAME_CMP(int op)
{
	switch(op)
	{
		case CMP_LT:
			return "<";
		case CMP_LE:
			return "<=";
		case CMP_GE:
			return ">=";
		case CMP_GT:
			return ">";
		case CMP_EQ:
			return "==";
		case CMP_NE:
			return "!=";
	}
	return "Unkown CMP";
}

static inline int print_set_newline(flags)
{
	return flags & PRINT_FLAGS_NEWLINE;
}
static inline void __robject_init(Robject* r)
{
	r->r_ref=1;
}
void robject_init(Robject* r,TypeObject* t)
{
	__robject_init(r);
	r->r_type=t;
}
void* __robject_new(ssize_t size,TypeObject* t)
{
	Robject* ret=(Robject*)ry_malloc(size);
	if(ret==NULL)
	{
		ryerr_nomemory();
		return NULL;
	}
	robject_init(ret,t);

	return ret;
}
static int s_swap_op[]={CMP_GT,CMP_GE,CMP_NE,CMP_EQ,CMP_LE,CMP_LT};

int robject_richcmp(Robject* x,Robject* y,int op)
{
	int ret;
	TypeObject* t_x=x->r_type;
	TypeObject* t_y=y->r_type;

	if(t_x->t_rich_cmp!=0)
	{
		ret=t_x->t_rich_cmp(x,y,op);
		if(ret!=CMP_NOT_SUPPORT)
		{
			return ret;
		}
	}
	if(t_y->t_rich_cmp!=0)
	{
		ret=t_y->t_rich_cmp(y,x,s_swap_op[op]);
		if(ret!=CMP_NOT_SUPPORT)
		{
			return ret;
		}
	}
	switch(op)
	{
		case CMP_EQ:
			ret=(x==y)?1:0;
			break;
		case CMP_NE:
			ret=(x!=y)?1:0;
			break;
		default:
			ret=CMP_NOT_SUPPORT;
	}
	return ret;
}

void robject_release(Robject* r)
{
	r->r_ref--;
	BUG_ON(r->r_ref<0," Object '%s'  Release Error,RefNum=%d",
						robject_name(r),r->r_ref);
	if(r->r_ref==0)
	{
		if(!r->r_type->t_object_funcs)
			goto default_action;

		if(!r->r_type->t_object_funcs->ro_free)
			goto default_action;

		r->r_type->t_object_funcs->ro_free(r);
	}
	return ;

default_action:
	WARN("Object %s No ro_free Method",robject_name(r));
	ry_free(r);
}


void robject_print(Robject* rt,FILE* f,int flags)
{
	TypeObject* t=rt->r_type;
	assert(t);
	if(!t->t_print)
	{
		goto default_action;
	}
	t->t_print(rt,f,flags&~PRINT_FLAGS_NEWLINE);
	if(print_set_newline(flags))
	{
		printf("\n");
	}
	return ;
default_action:
	printf("Object At %ld",(long)rt);
	if(print_set_newline(flags))
	{
		printf("\n");
	}
	return ;

}


/*FIXME should we provide defalut hash func by using object address? */
ssize_t robject_hash(Robject* rt)
{
	TypeObject* t=rt->r_type;
	if(t==NULL)
	{
		BUG("TypeObject Error");
		except_unkown_err_format("TypeObject Not Find");
		return -1;
	}
	if(!t->t_hash)
		goto default_action;

	ssize_t hash=t->t_hash(rt);
	return hash;
default_action:
	except_type_err_format("unhashed type:'%s'",robject_name(rt));
	return -1;
}

Robject* robject_get_item(Robject* r,Robject* index)
{
	TypeObject* t=r->r_type;
	if(t==NULL)
	{
		BUG("TypeObject Error");
		except_unkown_err_format("TypeObject Not Find");
		return NULL;
	}
	if(!t->t_expr_funcs)
		goto default_action;
	if(!t->t_expr_funcs->ro_get_item)
		goto default_action;

	Robject* ret=t->t_expr_funcs->ro_get_item(r,index);
	if(ret==NULL)
	{
		if(!vm_except_happened())
		{
			except_unkown_err_format("Bug Interal");
		}
	}
	return ret;
default_action:

	except_type_err_format("unsupport operand([]) for '%s'",
							robject_name(r));
	return NULL;
}
int robject_set_item(Robject* r,Robject* index,Robject* value)
{
	TypeObject* t=r->r_type;
	if(t==NULL)
	{
		BUG("TypeObject Error");
		except_unkown_err_format("TypeObject Not Find");
		return -1;
	}
	if(!t->t_expr_funcs)
		goto default_action;
	if(!t->t_expr_funcs->ro_set_item)
		goto default_action;

	int ret=t->t_expr_funcs->ro_set_item(r,index,value);
	if(ret<0)
	{
		if(!vm_except_happened())
		{
			except_unkown_err_format("Bug Interal");
		}
	}
	return ret;
default_action:
	except_type_err_format("unsupport item set for '%s'",
						robject_name(r));
	return -1;
}



#define ROBJECT_UNARY(H,l) \
Robject* robject_##l(Robject* r)  \
{ \
	TypeObject* t=r->r_type; \
	if(t==NULL) \
	{ \
		BUG("TypeObject Error"); \
		goto error; \
	} \
	if(!t->t_expr_funcs)  \
		goto default_action; \
	if(!t->t_expr_funcs->ro_##l) \
		goto default_action;  \
	Robject* ret=t->t_expr_funcs->ro_##l(r); \
	if(ret==NULL) \
	{ \
		if(!vm_except_happened()) \
		{ \
			except_unkown_err_format("Bug Interal"); \
		} \
	} \
	return ret;  \
default_action:  \
	except_type_err_format("unsupport operand(%s) for '%s'", \
					OPER_NAME_##H,robject_name(r));  \
	return NULL;  \
error: \
	except_unkown_err_format("Not Find TypeObject"); \
	return NULL; \
}

ROBJECT_UNARY(POSITIVE,positive);
ROBJECT_UNARY(NEGATED,negated);
ROBJECT_UNARY(NEGATIVE,negative);


#define ROBJECT_BINARY(H,l) \
Robject* robject_##l(Robject* x,Robject* y) \
{ \
	TypeObject* t_x=x->r_type; \
	TypeObject* t_y=x->r_type; \
	if(t_x==NULL||t_y==NULL) \
	{ \
		BUG("TypeObject Error"); \
		goto error; \
	} \
	if(!t_x->t_expr_funcs) \
	{ \
		goto default_action; \
	} \
	if(!t_x->t_expr_funcs->ro_##l) \
	{ \
		goto default_action; \
	}  \
	Robject* ret= t_x->t_expr_funcs->ro_##l(x,y); \
	if(ret==NULL) \
	{  \
		if(!vm_except_happened())  \
		{ \
			except_unkown_err_format("Internal Bug"); \
		} \
	}  \
	return ret; \
default_action: \
	except_type_err_format("unsupport operand(%s) for '%s' and '%s'",  \
			OPER_NAME_##H,robject_name(x),robject_name(y)); \
	return NULL; \
error: \
	except_unkown_err_format("Not Find TypeObject"); \
	return NULL; \
}

ROBJECT_BINARY(MUL,mul);
ROBJECT_BINARY(DIV,div);
ROBJECT_BINARY(MOD,mod);
ROBJECT_BINARY(PLUS,plus);
ROBJECT_BINARY(MINUS,minus);
ROBJECT_BINARY(LSHIFT,lshift);
ROBJECT_BINARY(RSHIFT,rshift);
ROBJECT_BINARY(AND,and);
ROBJECT_BINARY(XOR,xor);
ROBJECT_BINARY(OR,or);




#define ROBJECT_CMP(H,l) \
int robject_##l(Robject* x,Robject* y) \
{ \
	TypeObject* t_x=x->r_type; \
	TypeObject* t_y=x->r_type; \
	if(t_x==NULL||t_y==NULL) \
	{ \
		BUG("TypeObject Error"); \
		goto error; \
	} \
	if(!t_x->t_expr_funcs) \
	{ \
		goto default_action; \
	} \
	if(!t_x->t_expr_funcs->ro_##l) \
	{ \
		goto default_action; \
	}  \
	int ret= t_x->t_expr_funcs->ro_##l(x,y); \
	if(ret==-1) \
	{  \
		if(!vm_except_happened())  \
		{ \
			except_unkown_err_format("Internal Bug"); \
		} \
	}  \
	return ret; \
default_action: \
	except_type_err_format("unsupport operand(%s) for '%s' and '%s'",  \
			OPER_NAME_##H,robject_name(x),robject_name(y)); \
	return -1; \
error: \
	except_unkown_err_format("Not Find TypeObject"); \
	return -1; \
}

ROBJECT_CMP(LT,lt);
ROBJECT_CMP(LE,le);
ROBJECT_CMP(GT,gt);
ROBJECT_CMP(GE,ge);
ROBJECT_CMP(EQ,eq);
ROBJECT_CMP(NE,ne);


int robject_bool(Robject* rt)
{
	TypeObject* t=rt->r_type;
	if(t==NULL)
	{
		BUG("TypeObject Error"); 
		goto error; 
	}
	if(!t->t_expr_funcs)
	{
		goto default_action;
	}
	if(!t->t_expr_funcs->ro_bool)
	{
		goto default_action;
	}

	int ret=t->t_expr_funcs->ro_bool(rt);
	if(ret==-1)
	{
		if(!vm_except_happened())
		{
			except_unkown_err_format("Internal Bug");
		}
	}
	return ret;
default_action:
	return 1;
error:
	except_unkown_err_format("Not Find TypeObject"); 
	return -1; 
}




