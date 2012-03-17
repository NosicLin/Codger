#include"robject.h"
#include<stdio.h>
#include"rtype.h"
#include<assert.h>

/* binary operator */
#define f_func(name) \
Robject* r_##name(Robject* l,Robject* r) \
{ \
	if(l->r_expr_ops->ro_##name) \
	{  \
		return l->r_expr_ops->ro_##name(l,r); \
	} \
	else \
	{ \
		robject_addref(robject_null); \
		return robject_null; \
	} \
} 

f_func(mul);
f_func(div);
f_func(mod);
f_func(plus);
f_func(minus);
f_func(lshift);
f_func(rshift);
f_func(bit_and);
f_func(bit_or);
f_func(bit_xor);

/* unary operator */

#define unary_func(name) \
Robject* r_##name(Robject* u)\
{ \
	if(u->r_expr_ops->ro_##name) \
	{  \
		return u->r_expr_ops->ro_##name(u); \
	} \
	else \
	{ \
		robject_addref(robject_null); \
		return robject_null; \
	} \
}



unary_func(positive);
unary_func(negative);
unary_func(bit_negated);


f_func(cmp)
#define L_INT_VAL 14
#define R_INT_VAL  9

#define test_int_oper_int(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	int l_val=R_TO_I(l)->i_value; \
	int r_val=R_TO_I(r)->i_value; \
	int u_val=R_TO_I(u)->i_value; \
	printf("%d %s %d = %d",l_val,#op,r_val,u_val); \
	if(u_val!=(l_val op r_val))  \
	{ \
		g_error++; \
		printf("(Error)"); \
	}  \
	else  \
	{ \
		g_correct++; \
		printf("(OK)") ; \
	} \
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_int_oper_long(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	int l_val=R_TO_I(l)->i_value; \
	int r_val=R_TO_L(r)->l_value->b_val[0]; \
	int u_val=R_TO_L(u)->l_value->b_val[0]; \
	printf("%d %s %d = %d",l_val,#op,r_val,u_val); \
	if(u_val!=(l_val op r_val))  \
	{ \
		g_error++; \
		printf("(Error)"); \
	}  \
	else  \
	{ \
		g_correct++; \
		printf("(OK)") ; \
	} \
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_int_oper_float(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	int l_val=R_TO_I(l)->i_value; \
	float r_val=R_TO_F(r)->f_value; \
	if(u!=robject_null) \
	{ \
		float u_val=R_TO_F(u)->f_value; \
		printf("%d %s %g = %g",l_val,#op,r_val,u_val); \
		if(abs(u_val-(l_val op r_val))>0.00001)  \
		{ \
			g_error++; \
			printf("(Error %g)",(l_val op r_val)); \
		}  \
		else  \
		{ \
			g_correct++; \
			printf("(OK)") ; \
		} \
	} \
	else \
	{ \
		printf("%d %s %g =NULL",l_val,#op,r_val); \
		g_ingor++; \
	}\
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_float_oper_float(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	float l_val=R_TO_F(l)->f_value; \
	float r_val=R_TO_F(r)->f_value; \
	if(u!=robject_null) \
	{ \
		float u_val=R_TO_F(u)->f_value; \
		printf("%g %s %g = %g",l_val,#op,r_val,u_val); \
		if(abs(u_val-(l_val op r_val))>0.00001)  \
		{ \
			g_error++; \
			printf("(Error %g)",(l_val op r_val)); \
		}  \
		else  \
		{ \
			g_correct++; \
			printf("(OK)") ; \
		} \
	} \
	else \
	{ \
		printf("%g %s %g =NULL",l_val,#op,r_val); \
		g_ingor++; \
	}\
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_float_oper_int(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	float l_val=R_TO_F(l)->f_value; \
	int r_val=R_TO_I(r)->i_value; \
	if(u!=robject_null) \
	{ \
		float u_val=R_TO_F(u)->f_value; \
		printf("%g %s %d = %g",l_val,#op,r_val,u_val); \
		if(abs(u_val-(l_val op r_val))>0.00001)  \
		{ \
			g_error++; \
			printf("(Error %g)",(l_val op r_val)); \
		}  \
		else  \
		{ \
			g_correct++; \
			printf("(OK)") ; \
		} \
	} \
	else \
	{ \
		printf("%g %s %d =NULL",l_val,#op,r_val); \
		g_ingor++; \
	}\
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_float_oper_long(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	float l_val=R_TO_F(l)->f_value; \
	int r_val=R_TO_L(r)->l_value->b_val[0]; \
	if(u!=robject_null) \
	{ \
		float u_val=R_TO_F(u)->f_value; \
		printf("%g %s %d = %g",l_val,#op,r_val,u_val); \
		if(abs(u_val-(l_val op r_val))>0.00001)  \
		{ \
			g_error++; \
			printf("(Error %g)",(l_val op r_val)); \
		}  \
		else  \
		{ \
			g_correct++; \
			printf("(OK)") ; \
		} \
	} \
	else \
	{ \
		printf("%g %s %d =NULL",l_val,#op,r_val); \
		g_ingor++; \
	}\
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_long_oper_long(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	int l_val=R_TO_L(l)->l_value->b_val[0]; \
	int r_val=R_TO_L(r)->l_value->b_val[0]; \
	int u_val=R_TO_L(u)->l_value->b_val[0]; \
	printf("%d %s %d = %d",l_val,#op,r_val,u_val); \
	if(u_val!=(l_val op r_val))  \
	{ \
		g_error++; \
		printf("(Error)"); \
	}  \
	else  \
	{ \
		g_correct++; \
		printf("(OK)") ; \
	} \
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_long_oper_int(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	int l_val=R_TO_L(l)->l_value->b_val[0]; \
	int r_val=R_TO_I(r)->i_value; \
	int u_val=R_TO_L(u)->l_value->b_val[0]; \
	printf("%d %s %d = %d",l_val,#op,r_val,u_val); \
	if(u_val!=(l_val op r_val))  \
	{ \
		g_error++; \
		printf("(Error)"); \
	}  \
	else  \
	{ \
		g_correct++; \
		printf("(OK)") ; \
	} \
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_long_oper_float(func,l,r, op) \
do{ \
	Robject* u=func(l,r); \
	int l_val=R_TO_L(l)->l_value->b_val[0]; \
	float r_val=R_TO_F(r)->f_value; \
	if(u!=robject_null) \
	{ \
		float u_val=R_TO_F(u)->f_value; \
		printf("%d %s %g = %g",l_val,#op,r_val,u_val); \
		if(abs(u_val-(l_val op r_val))>0.00001)  \
		{ \
			g_error++; \
			printf("(Error %g)",(l_val op r_val)); \
		}  \
		else  \
		{ \
			g_correct++; \
			printf("(OK)") ; \
		} \
	} \
	else \
	{ \
		printf("%d %s %g =NULL",l_val,#op,r_val); \
		g_ingor++; \
	}\
	printf("\n"); \
	robject_release(u); \
}while(0)

#define test_unary_int(func,l,op) \
	do{ \
		Robject* u=func(l); \
		int l_val=R_TO_I(l)->i_value; \
		int u_val=R_TO_I(u)->i_value; \
		printf("%s %d = %d",#op,l_val,u_val); \
		if(u_val!=(op l_val))  \
		{ \
			g_error++; \
			printf("(Error)"); \
		}  \
		else  \
		{ \
			g_correct++; \
			printf("(OK)") ; \
		} \
		printf("\n"); \
		robject_release(u); \
	}while(0)


int g_correct=0;
int g_error=0;
int g_ingor=0;


#define test_oper_arithmetic(l_type,r_type,l,r) \
	test_##l_type##_oper_##r_type(r_mul,l,r,*); \
	test_##l_type##_oper_##r_type(r_div,l,r,/); \
	test_##l_type##_oper_##r_type(r_plus,l,r,+); \
	test_##l_type##_oper_##r_type(r_minus,l,r,-); 

#define test_oper_mod(l_type,r_type,l,r) \
	test_##l_type##_oper_##r_type(r_mod,l,r,%); 

#define test_oper_bitwise(l_type,r_type,l,r) \
	test_##l_type##_oper_##r_type(r_lshift,l,r,<<); \
	test_##l_type##_oper_##r_type(r_rshift,l,r,>>); \
	test_##l_type##_oper_##r_type(r_bit_and,l,r,&); \
	test_##l_type##_oper_##r_type(r_bit_xor,l,r,^); \
	test_##l_type##_oper_##r_type(r_bit_or,l,r,|);

#define test_oper_all(l_type,r_type,l,r) \
	test_oper_arithmetic(l_type,r_type,l,r); \
	test_oper_mod(l_type,r_type,l,r); \
	test_oper_bitwise(l_type,r_type,l,r); 

Robject* l=0;
Robject* r=0;
int main()
{
	BtInt* l_int=bt_int_create(L_INT_VAL);
	BtInt* r_int=bt_int_create(R_INT_VAL);
	BtFloat* l_float=bt_float_create(L_INT_VAL);
	BtFloat* r_float=bt_float_create(R_INT_VAL);
	BtLong* l_long=bt_long_from_int(L_INT_VAL);
	BtLong* r_long=bt_long_from_int(R_INT_VAL);

	l=I_TO_R(l_int);
	r=I_TO_R(r_int);

	printf("----int oper int ---- \n");
	test_oper_all(int,int,l,r);

	printf("----unary int---- \n");
	test_unary_int(r_negative,l, -);
	test_unary_int(r_positive,l, + );
	test_unary_int(r_bit_negated, l,~);

	printf("----int oper float---- \n");
	r=F_TO_R(r_float);
	test_oper_arithmetic(int,float,l,r);

	printf("----int oper long ----\n");
	r=L_TO_R(r_long);
	test_oper_all(int,long,l,r);



	printf("----float oper float----\n");
	l=F_TO_R(l_float);
	r=F_TO_R(r_float);
	test_oper_arithmetic(float,float,l,r);

	printf("----float oper int----\n");
	r=I_TO_R(r_int);
	test_oper_arithmetic(float,int,l,r);

	printf("----float oper long----\n");
	r=L_TO_R(r_long);
	test_oper_arithmetic(float,long,l,r);

	printf("-----long oper long----\n");
	l=L_TO_R(l_long);
	r=L_TO_R(r_long);
	test_oper_all(long,long,l,r);

	printf("-----long oper int----\n");
	r=I_TO_R(r_int);
	test_oper_all(long,int,l,r);

	printf("-----long oper float----\n");
	r=F_TO_R(r_float);
	test_oper_arithmetic(long,float,l,r);

	printf("ErrorNum=%d,CorrectNum=%d\n",g_error,g_correct);

	printf("l->ref=%d,r->r_ref=%d\n",l->r_ref,r->r_ref);

	robject_release(I_TO_R(l_int));
	robject_release(I_TO_R(r_int));
	robject_release(F_TO_R(l_float));
	robject_release(F_TO_R(r_float));
	robject_release(L_TO_R(l_long));
	robject_release(L_TO_R(r_long));

	return 0;
}




