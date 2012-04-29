#include"gr_int.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory/memory.h>
#include<memory/gc.h>


int int_new()
{
	long val=rand();
	GrInt* gs=GrInt_New(val);
	if(gs->i_value!=val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_positive()
{
	long val=rand();
	GrInt* gs=GrInt_New(val);
	GrInt* gt=GrInt_Positive(gs);
	if(gt->i_value!=val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_negative()
{
	long val=rand();
	GrInt* gs=GrInt_New(val);
	GrInt* gt=GrInt_Negative(gs);
	if(gt->i_value!=-val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_negated()
{
	long val=rand();
	GrInt* gs=GrInt_New(val);
	GrInt* gt=GrInt_Negated(gs);
	if(gt->i_value!=~val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_mul()
{
	long l_val=rand();
	long r_val=rand();

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Mul(gl,gr);

	if(gt->i_value!=l_val*r_val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int int_div_not_zero()
{
	long l_val=rand();
	long r_val=rand();

	if(r_val==0) r_val=1;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Div(gl,gr);

	if(gt->i_value!=l_val/r_val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_div_zero()
{
	long l_val=rand();
	long r_val=0;


	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Div(gl,gr);

	if(gt!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_mod_not_zero()
{
	long l_val=rand();
	long r_val=rand();

	if(r_val==0) r_val=1;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Mod(gl,gr);
	if(gt->i_value!=l_val%r_val)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}
int int_mod_zero()
{
	long l_val=rand();
	long r_val=0;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Mod(gl,gr);

	if(gt!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_plus()
{
	long l_val=rand();
	long r_val=rand();
	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Plus(gl,gr);

	if(gt->i_value!=l_val+r_val)
	{
		return 0;
	}
	else
	{
		return 1;

	}
}

int int_minus()
{
	long l_val=rand();
	long r_val=rand();
	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Minus(gl,gr);
	if(gt->i_value!=l_val-r_val)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_lshift_not_negative()
{
	long l_val=rand();
	long r_val=rand();
	if(r_val<0) r_val*=-1;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_LShift(gl,gr);
	if(gt->i_value!=l_val<<r_val)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

int int_lshift_negative()
{
	long l_val=rand();
	long r_val=rand();
	if(r_val>0) r_val*=-1;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_LShift(gl,gr);

	if(gt!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

int int_rshift_not_negative()
{
	long l_val=rand();
	long r_val=rand();
	if(r_val<0) r_val*=-1;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_RShift(gl,gr);
	if(gt->i_value!=l_val>>r_val)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

int int_rshift_negative()
{
	long l_val=rand();
	long r_val=rand();
	if(r_val>0) r_val*=-1;

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_RShift(gl,gr);

	if(gt!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

int int_and()
{
	long l_val=rand();
	long r_val=rand();

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_And(gl,gr);
	if(gt->i_value!=(l_val&r_val))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int int_or()
{
	long l_val=rand();
	long r_val=rand();

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Or(gl,gr);
	if(gt->i_value!=(l_val|r_val))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_xor()
{
	long l_val=rand();
	long r_val=rand();

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	GrInt* gt=GrInt_Xor(gl,gr);
	if(gt->i_value!=(l_val^r_val))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int int_cmp()
{
	long l_val=rand();
	long r_val=rand();

	GrInt* gl=GrInt_New(l_val);
	GrInt* gr=GrInt_New(r_val);

	int gt=GrInt_Cmp(gl,gr);

	int ret=l_val-r_val;
	if(ret<0) ret=-1;
	if(ret==0) ret=0;
	if(ret>0) ret=1;

	if(gt!=ret)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int int_bool()
{
	long l_val=0;
	while(l_val==0)
	{
		l_val=rand();
	}

	GrInt* gs=GrInt_New(l_val);
	int gt=GrInt_Bool(gs);

	if(gt!=1)
	{
		return 0;
	}


	gs=GrInt_New(0);

	gt=GrInt_Bool(gs);

	if(gt!=0)
	{
		return 0;

	}
	return 1;
}
#define TEST_TIMES 1000000

#define Func_Test(func) \
	do{ \
		printf("Unit_Test(%s)---",#func); \
		int i=0; \
		int ret; \
		while(i++<TEST_TIMES) \
		{ \
			ret=func(); \
			if(!ret) \
			{  \
				break; \
			} \
		} \
		if(ret) \
		{  \
			printf("(Ok)"); \
			g_corret++; \
		} \
		else \
		{  \
			printf("(Falied)");  \
			g_error++; \
		} \
		printf("\n"); \
	} while(0) 


int g_corret=0;
int g_error=0;

int main()
{
	GrModule_MemInit();
	GrModule_GcInit();
	srand((unsigned int)time(NULL));

	Func_Test(int_new);
	Func_Test(int_positive);
	Func_Test(int_negative);
	Func_Test(int_negated);
	Func_Test(int_mul);
	Func_Test(int_div_not_zero);
	Func_Test(int_div_zero);
	Func_Test(int_mod_not_zero);
	Func_Test(int_mod_zero);
	Func_Test(int_plus);
	Func_Test(int_minus);
	Func_Test(int_lshift_not_negative);
	Func_Test(int_lshift_negative);
	Func_Test(int_rshift_not_negative);
	Func_Test(int_rshift_negative);
	Func_Test(int_and);
	Func_Test(int_or);
	Func_Test(int_xor);
	Func_Test(int_cmp);
	Func_Test(int_bool);

	printf("Result: Ok(%d),Falied(%d)\n",g_corret,g_error);
	GrModule_GcExit();
	GrModule_MemExit();
	return 0;
}








