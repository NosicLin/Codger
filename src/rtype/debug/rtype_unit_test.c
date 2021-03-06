#include<stdio.h>
#include"rtype.h"
#include<assert.h>
#include"bt_string.h"
#include"bt_int.h"
#include"bt_float.h"
#include"bt_long.h"


/* binary operator */
#define f_func(name) \
Robject* r_##name(Robject* l,Robject* r) \
{ \
	if(l->r_type->t_expr_funcs->ro_##name) \
	{  \
		return l->r_type->t_expr_funcs->ro_##name(l,r); \
	} \
	else \
	{ \
		return NULL;\
	} \
} 

#define RT_NULL 0
f_func(mul);
f_func(div);
f_func(mod);
f_func(plus);
f_func(minus);
f_func(lshift);
f_func(rshift);
f_func(and);
f_func(or);
f_func(xor);

/* unary operator */

#define unary_func(name) \
Robject* r_##name(Robject* u)\
{ \
	if(u->r_type->t_expr_funcs->ro_##name) \
	{  \
		return u->r_type->t_expr_funcs->ro_##name(u); \
	} \
	else \
	{ \
		return NULL; \
	} \
}

unary_func(positive);
unary_func(negative);
unary_func(negated);



#define  L_VAL 4
#define R_VAL 7
#define  test_binary_type(func,l,r, S) \
	do{ \
		Robject* result=func(l,r);  \
		if(result!=NULL) \
		printf("%s %s %s = %s",l->r_type->t_name,#func,r->r_type->t_name,result->r_type->t_name); \
		else  \
		printf("%s %s %s= NULL",l->r_type->t_name,#func,r->r_type->t_name); \
		if(result) \
		{ \
			if(result->r_type->t_type==S)  { \
				g_correct++; \
				printf("(OK)") ; \
			} else { \
				g_error++; \
				printf("(Error!!)"); \
			} \
			robject_release(result);\
		} \
		else \
		{ \
			if(S==0) \
			{ \
				g_correct++; \
				printf("(OK)") ; \
			} else { \
				g_error++; \
				printf("(Error!!)"); \
			} \
		} \
		printf("\n"); \
	}while(0) 

#define  test_unary(func,l, S) \
	do{ \
		Robject* result=func(l);  \
		if(result==NULL) \
		{ \
			printf("%s %s = NULL",#func,l->r_type->t_name); \
		} \
		else  \
		{ \
			printf("%s %s = %s",#func,l->r_type->t_name,result->r_type->t_name); \
		} \
		if(result) \
		{ \
			if(result->r_type->t_type==S)  { \
				g_correct++; \
				printf("(OK)") ; \
			} else { \
				g_error++; \
				printf("(Error!!)"); \
			} \
			robject_release(result);\
		} \
		else \
		{ \
			if(S==0) \
			{ \
				g_correct++; \
				printf("(OK)") ; \
			} else { \
				g_error++; \
				printf("(Error!!)"); \
			} \
		} \
		printf("\n"); \
	}while(0) 

int g_correct=0;
int g_error=0;

Robject* l_int=0;
Robject* r_int=0;

Robject* r_float=0;
Robject* l_float=0;

Robject* l_long=0;
Robject* r_long=0;


TypeObject _type_other=
{
	.t_name="Other",
	.t_type=1000,
};
Robject _other=
{
	1,
	&_type_other,
};
Robject*  other=&_other;



Robject* int_zero=0;
Robject* float_zero=0;
Robject* long_zero=0;

int main()
{
	l_int=I_TO_R(btint_create(L_VAL));
	r_int=I_TO_R(btint_create(R_VAL));
	int_zero=I_TO_R(btint_create(0));

	l_float=F_TO_R(btfloat_create(L_VAL));
	r_float=F_TO_R(btfloat_create(R_VAL));
	float_zero=F_TO_R(btfloat_create(0));

	l_long=L_TO_R(btlong_from_int(L_VAL));
	r_long=L_TO_R(btlong_from_int(R_VAL));
	long_zero=L_TO_R(btlong_from_int(0));


	/*--------------int part-----------------*/
	/* int oper int */
	printf("----int oper int----\n");
	test_binary_type(r_mul,l_int,r_int,RT_INT);
	test_binary_type(r_div,l_int,r_int,RT_INT);
	test_binary_type(r_mod,l_int,r_int,RT_INT);
	test_binary_type(r_plus,l_int,r_int,RT_INT);
	test_binary_type(r_minus,l_int,r_int,RT_INT);
	test_binary_type(r_lshift,l_int,r_int,RT_INT);
	test_binary_type(r_rshift,l_int,r_int,RT_INT);
	test_binary_type(r_and,l_int,r_int,RT_INT);
	test_binary_type(r_or,l_int,r_int,RT_INT);
	test_binary_type(r_xor,l_int,r_int,RT_INT);

	/* int oper float*/

	printf("----int oper float----\n");
	test_binary_type(r_mul,l_int,r_float,RT_FLOAT);
	test_binary_type(r_div,l_int,r_float,RT_FLOAT);
	test_binary_type(r_mod,l_int,r_float,RT_NULL);
	test_binary_type(r_plus,l_int,r_float,RT_FLOAT);
	test_binary_type(r_minus,l_int,r_float,RT_FLOAT);
	test_binary_type(r_lshift,l_int,r_float,RT_NULL);
	test_binary_type(r_rshift,l_int,r_float,RT_NULL);
	test_binary_type(r_and,l_int,r_float,RT_NULL);
	test_binary_type(r_or,l_int,r_float,RT_NULL);
	test_binary_type(r_xor,l_int,r_float,RT_NULL);

	/* int oper long */
	printf("----int oper long----\n");
	test_binary_type(r_mul,l_int,r_long,RT_LONG);
	test_binary_type(r_div,l_int,r_long,RT_LONG);
	test_binary_type(r_mod,l_int,r_long,RT_LONG);
	test_binary_type(r_plus,l_int,r_long,RT_LONG);
	test_binary_type(r_minus,l_int,r_long,RT_LONG);
	test_binary_type(r_lshift,l_int,r_long,RT_LONG);
	test_binary_type(r_rshift,l_int,r_long,RT_LONG);
	test_binary_type(r_and,l_int,r_long,RT_LONG);
	test_binary_type(r_xor,l_int,r_long,RT_LONG);
	test_binary_type(r_or,l_int,r_long,RT_LONG);

	/* int oper other */
	printf("----int oper other ----\n");
	test_binary_type(r_mul,l_int,other,RT_NULL);
	test_binary_type(r_div,l_int,other,RT_NULL);
	test_binary_type(r_mod,l_int,other,RT_NULL);
	test_binary_type(r_plus,l_int,other,RT_NULL);
	test_binary_type(r_minus,l_int,other,RT_NULL);
	test_binary_type(r_lshift,l_int,other,RT_NULL);
	test_binary_type(r_rshift,l_int,other,RT_NULL);
	test_binary_type(r_and,l_int,other,RT_NULL);
	test_binary_type(r_or,l_int,other,RT_NULL);
	test_binary_type(r_xor,l_int,other,RT_NULL);

	/* unary int */
	test_unary(r_negative,l_int,RT_INT);
	test_unary(r_positive,l_int,RT_INT);
	test_unary(r_negated,l_int,RT_INT);

	/* test divmod zero */
	printf("---- int divmod zero ----\n");
	test_binary_type(r_div,l_int,int_zero,RT_NULL);
	test_binary_type(r_div,l_int,float_zero,RT_NULL);
	test_binary_type(r_div,l_int,long_zero,RT_NULL);
	test_binary_type(r_mod,l_int,int_zero,RT_NULL);
	test_binary_type(r_mod,l_int,float_zero,RT_NULL);
	test_binary_type(r_mod,l_int,long_zero,RT_NULL);

	/*--------------float part ----------*/
	printf("----float oper float ----\n");
	test_binary_type(r_mul,l_float,r_float,RT_FLOAT);
	test_binary_type(r_div,l_float,r_float,RT_FLOAT);
	test_binary_type(r_mod,l_float,r_float,RT_NULL);
	test_binary_type(r_plus,l_float,r_float,RT_FLOAT);
	test_binary_type(r_minus,l_float,r_float,RT_FLOAT);
	test_binary_type(r_lshift,l_float,r_float,RT_NULL);
	test_binary_type(r_rshift,l_float,r_float,RT_NULL);
	test_binary_type(r_and,l_float,r_float,RT_NULL);
	test_binary_type(r_or,l_float,r_float,RT_NULL);
	test_binary_type(r_xor,l_float,r_float,RT_NULL);

	printf("----float oper int ----\n");
	test_binary_type(r_mul,l_float,r_int,RT_FLOAT);
	test_binary_type(r_div,l_float,r_int,RT_FLOAT);
	test_binary_type(r_mod,l_float,r_int,RT_NULL);
	test_binary_type(r_plus,l_float,r_int,RT_FLOAT);
	test_binary_type(r_minus,l_float,r_int,RT_FLOAT);
	test_binary_type(r_lshift,l_float,r_int,RT_NULL);
	test_binary_type(r_rshift,l_float,r_int,RT_NULL);
	test_binary_type(r_and,l_float,r_int,RT_NULL);
	test_binary_type(r_or,l_float,r_int,RT_NULL);
	test_binary_type(r_xor,l_float,r_int,RT_NULL);

	printf("----float oper long----\n");
	test_binary_type(r_mul,l_float,r_long,RT_FLOAT);
	test_binary_type(r_div,l_float,r_long,RT_FLOAT);
	test_binary_type(r_mod,l_float,r_long,RT_NULL);
	test_binary_type(r_plus,l_float,r_long,RT_FLOAT);
	test_binary_type(r_minus,l_float,r_long,RT_FLOAT);
	test_binary_type(r_lshift,l_float,r_long,RT_NULL);
	test_binary_type(r_rshift,l_float,r_long,RT_NULL);
	test_binary_type(r_and,l_float,r_long,RT_NULL);
	test_binary_type(r_or,l_float,r_long,RT_NULL);
	test_binary_type(r_xor,l_float,r_long,RT_NULL);

	printf("----float oper other ----\n");
	test_binary_type(r_mul,l_float,other,RT_NULL);
	test_binary_type(r_div,l_float,other,RT_NULL);
	test_binary_type(r_mod,l_float,other,RT_NULL);
	test_binary_type(r_plus,l_float,other,RT_NULL);
	test_binary_type(r_minus,l_float,other,RT_NULL);
	test_binary_type(r_lshift,l_float,other,RT_NULL);
	test_binary_type(r_rshift,l_float,other,RT_NULL);
	test_binary_type(r_and,l_float,other,RT_NULL);
	test_binary_type(r_or,l_float,other,RT_NULL);
	test_binary_type(r_xor,l_float,other,RT_NULL);


	printf("----unary float ----\n");
	test_unary(r_negative,l_float,RT_FLOAT);
	test_unary(r_positive,l_float,RT_FLOAT);
	test_unary(r_negated,l_float,RT_NULL);

	printf("---- float divmod zero ----\n");
	test_binary_type(r_div,l_float,int_zero,RT_NULL);
	test_binary_type(r_div,l_float,float_zero,RT_NULL);
	test_binary_type(r_div,l_float,long_zero,RT_NULL);
	test_binary_type(r_mod,l_float,int_zero,RT_NULL);
	test_binary_type(r_mod,l_float,float_zero,RT_NULL);
	test_binary_type(r_mod,l_float,long_zero,RT_NULL);


	/*------long parts---------------*/
	printf("----long oper long----\n");
	test_binary_type(r_mul,l_long,r_long,RT_LONG);
	test_binary_type(r_div,l_long,r_long,RT_LONG);
	test_binary_type(r_mod,l_long,r_long,RT_LONG);
	test_binary_type(r_plus,l_long,r_long,RT_LONG);
	test_binary_type(r_minus,l_long,r_long,RT_LONG);
	test_binary_type(r_lshift,l_long,r_long,RT_LONG);
	test_binary_type(r_rshift,l_long,r_long,RT_LONG);
	test_binary_type(r_and,l_long,r_long,RT_LONG);
	test_binary_type(r_or,l_long,r_long,RT_LONG);
	test_binary_type(r_xor,l_long,r_long,RT_LONG);

	printf("----long oper float ----\n");
	test_binary_type(r_mul,l_long,r_float,RT_FLOAT);
	test_binary_type(r_div,l_long,r_float,RT_FLOAT);
	test_binary_type(r_mod,l_long,r_float,RT_NULL);
	test_binary_type(r_plus,l_long,r_float,RT_FLOAT);
	test_binary_type(r_minus,l_long,r_float,RT_FLOAT);
	test_binary_type(r_lshift,l_long,r_float,RT_NULL);
	test_binary_type(r_rshift,l_long,r_float,RT_NULL);
	test_binary_type(r_and,l_long,r_float,RT_NULL);
	test_binary_type(r_or,l_long,r_float,RT_NULL);
	test_binary_type(r_xor,l_long,r_float,RT_NULL);

	printf("----long oper long----\n");
	test_binary_type(r_mul,l_long,r_int,RT_LONG);
	test_binary_type(r_div,l_long,r_int,RT_LONG);
	test_binary_type(r_mod,l_long,r_int,RT_LONG);
	test_binary_type(r_plus,l_long,r_int,RT_LONG);
	test_binary_type(r_minus,l_long,r_int,RT_LONG);
	test_binary_type(r_lshift,l_long,r_int,RT_LONG);
	test_binary_type(r_rshift,l_long,r_int,RT_LONG);
	test_binary_type(r_and,l_long,r_int,RT_LONG);
	test_binary_type(r_or,l_long,r_int,RT_LONG);
	test_binary_type(r_xor,l_long,r_int,RT_LONG);

	printf("----long oper other ----\n");
	test_binary_type(r_mul,l_long,other,RT_NULL);
	test_binary_type(r_div,l_long,other,RT_NULL);
	test_binary_type(r_mod,l_long,other,RT_NULL);
	test_binary_type(r_plus,l_long,other,RT_NULL);
	test_binary_type(r_minus,l_long,other,RT_NULL);
	test_binary_type(r_lshift,l_long,other,RT_NULL);
	test_binary_type(r_rshift,l_long,other,RT_NULL);
	test_binary_type(r_and,l_long,other,RT_NULL);
	test_binary_type(r_or,l_long,other,RT_NULL);
	test_binary_type(r_xor,l_long,other,RT_NULL);

	printf("----unary float ----\n");
	test_unary(r_negative,l_long,RT_LONG);
	test_unary(r_positive,l_long,RT_LONG);
	test_unary(r_negated,l_long,RT_LONG);

	printf("---- float divmod zero ----\n");
	test_binary_type(r_div,l_long,int_zero,RT_NULL);
	test_binary_type(r_div,l_long,float_zero,RT_NULL);
	test_binary_type(r_div,l_long,long_zero,RT_NULL);
	test_binary_type(r_mod,l_long,int_zero,RT_NULL);
	test_binary_type(r_mod,l_long,float_zero,RT_NULL);
	test_binary_type(r_mod,l_long,long_zero,RT_NULL);

	robject_release(l_int);
	robject_release(r_int);
	robject_release(l_float);
	robject_release(r_float);
	robject_release(r_long);
	robject_release(l_long);
	robject_release(int_zero);
	robject_release(long_zero);
	robject_release(float_zero);
	printf("ErrorNum=%d,CorrectNum=%d\n",g_error,g_correct);
	return 0;
}


