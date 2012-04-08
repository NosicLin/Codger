#include"stack_frame.h"
#include<rstd/gr_std.h>

#define MAX_CACHE_NUM 200

static int s_cache_nu=0;
static StackFrame* s_stack_frame_cache[MAX_CACHE_NUM];

static inline StackFrame* sf_malloc()
{
	StackFrame* sf=0;
	HashTable* h=0;
	if(s_cache_nu>0)
	{
		sf=s_stack_frame_cache[--s_cache_nu];
	}
	else
	{
		sf=gr_malloc(sizeof(*sf));
		if(sf==NULL)
		{
			grerr_nomemory();
			goto error;
		}
	}
	memset(sf,0,sizeof(*sf));

	h=hash_new();
	if(h==NULL)
	{
		goto error;
	}
	sf->sf_symbols=h;
	return sf;
error:
	if(sf) sframe_free(sf);
	return NULL;
}

StackFrame* sframe_new()
{
	StackFrame* ret=sf_malloc();
	if(ret==0)
	{
		return NULL;
	}
	return ret;
}

void sframe_free(StackFrame* sf)
{
	robject_release(S_TO_R(sf->sf_name));
	robject_release(HASH_TO_R(sf->sf_symbols));
	robject_release(M_TO_R(sf->sf_modules));
	robject_release(sf->sf_origin);

	if(s_cache_nu>=MAX_CACHE_NUM)
	{

		gr_free(sf);
		return ;
	}
	s_stack_frame_cache[s_cache_nu++]=sf;
}
void sframe_clear_cache()
{
	while(s_cache_nu)
	{
		gr_free(s_stack_frame_cache[--s_cache_nu]);
	}
}
StackFrame* sframe_from_func(FuncObject* f)
{
	StackFrame* sf=sf_malloc();
	if(sf==NULL)
	{
		return NULL;
	}
	robject_addref(FUNC_TO_R(f));
	robject_addref(S_TO_R(f->f_name));
	robject_addref(M_TO_R(f->f_module));

	sf->sf_name=f->f_name;
	sf->sf_modules=f->f_module;
	sf->sf_codes=f->f_codes;
	sf->sf_origin=FUNC_TO_R(f);
	return sf;
}
StackFrame* sframe_from_module(ModuleObject* m)
{
	StackFrame* sf=sf_malloc();
	if(sf==NULL)
	{
		return NULL;
	}
	robject_addref(M_TO_R(m));
	robject_addref(M_TO_R(m));
	robject_addref(S_TO_R(m->m_name));

	sf->sf_name=m->m_name;
	sf->sf_modules=m;
	sf->sf_origin=M_TO_R(m);
	sf->sf_codes=m->m_codes;
	return sf;
}









