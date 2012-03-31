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

static TypeObject type_null=
{
	.t_name="NULL",
	.t_type=TYPE_NULL,
	.t_object_funcs=&null_object_ops,
};

static Robject __robject_null=
{
	.r_ref=1,
	.r_type=&type_null,
};

Robject* NullObject=&__robject_null;

