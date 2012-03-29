#include "robject.h"
#include<utility_c/marocs.h>
#include<rstd/redy_std.h>
#include<stdio.h>
#include<assert.h>

void robject_init(Robject* r);
void* __robject_new(ssize_t size,TypeObject* t)
{
	Robject* ret=(Robject*)ry_malloc(size);
	if(ret==NULL)
	{
		ryerr_nomemory();
		return NULL;
	}
	robject_init(ret);
	ret->r_type=t;
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







void robject_print(Robject* rt,FILE* f,int flags)
{
	TypeObject* t=rt->r_type;
	assert(t);
	if(!t->t_expr_funcs)
	{
		goto default_action;
	}
	if(!t->t_expr_funcs->ro_print)
	{
		goto default_action;
	}
	t->t_expr_funcs->ro_print(rt,f,flags);
	printf("\n");
	return ;
default_action:
	printf("Object At %ld\n",(long)rt);
	return ;

}





