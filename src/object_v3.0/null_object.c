#include"null_object.h"
#include"type_object.h"
#include<utility_c/marocs.h>

void nl_free(Robject* r)
{
	BUG("NULL Object Shouldn't Free");
}

static struct object_ops null_object_ops=
{
	.ro_free=nl_free,
};
static int  null_print(Robject* ro,FILE* f,int flags)
{
	printf("Null");
	if(flags&PRINT_FLAGS_NEWLINE)
	{
		printf("\n");
	}
	return 0;
}
static int null_bool(Robject* ro)
{
	return 0;
}
static struct expr_ops null_expr_ops=
{
	.ro_bool=null_bool,
};
static TypeObject type_null=
{
	.t_name="NULL",
	.t_type=TYPE_NULL,
	.t_expr_funcs=&null_expr_ops,
	.t_object_funcs=&null_object_ops,
	.t_print=null_print,
};

static Robject __robject_null=
{
	.r_ref=1,
	.r_type=&type_null,
};

Robject* ObjectNull=&__robject_null;

