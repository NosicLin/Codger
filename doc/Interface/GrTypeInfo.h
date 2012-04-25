struct GrTypeInfo
{
	GrClass   t_class;
	GrString  t_name;
	GrTypeOps t_ops;
};


struct GrTypeOps
{
	GrOperatorOps* o_operator;
	GrOperatorOps* o_operator_inverse;
	GrTypeCast* o_type_cast;

	ssize_t (*t_hash)(GrObject*);

	int (*t_print)(GrObject*,FILE*,long);
	int (*t_rich_cmp)(GrObject*,GrObject*);

	GrObject* (*t_iter)(GrObject*);
	GrObject* (*t_iter_next)(GrObject*);

	int (*t_set_attr)(GrObject*,GrObject* s,GrObject* v,long flags);
	int (*t_get_attr)(GrObject*,GrObject* s,long flags);


	GrObject* (*t_new)(GrObject*);

	int (*t_destruct)(GrObject*);
	int (*t_dealloc)(GrObject*);
};


typedef GrObject* (*GrBinaryOps)(GrObject*,GrObject*);
typedef GrObject* (*GrUnaryOps)(GrObject*);
typedef int (*GrCmpOps)(GrObject*,GrObject*,int op);

struct GrOperatorOps
{
	int (*oo_set_item)(GrObject*,GrObject*,GrObject*);
	GrObject* (*oo_get_item)(GrObject*,GrObject*);

	GrUnaryOps oo_negative;
	GrUnaryOps oo_positive;
	GrUnaryOps oo_negated;

	GrBinaryOps oo_mul;
	GrBinaryOps oo_div;
	GrBinaryOps oo_mod;

	GrBinaryOps oo_plus;
	GrBinaryOps oo_minus;

	GrBinaryOps oo_lshift;
	GrBinaryOps oo_rshift;

	GrBinaryOps oo_and;
	GrBinaryOps oo_xor
	GrBinaryOps oo_or;

	GrCmpOps oo_cmp;



	int (*oo_bool)(Robject* );
};

struct GrTypeCast
{
	GrObject* tc_to_float(GrObject*);
	GrObject* tc_to_int(GrObject*);
	GrObject* tc_to_long(GrObject*);
	GrObject* tc_to_string(GrObject*);
};










