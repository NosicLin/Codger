#ifndef _CODGER_OBJECT_TYPE_INFO_H_
#define _CODGER_OBJECT_TYPE_INFO_H_


struct gr_class;
struct gr_type_ops;
struct gr_operator_ops;
struct gr_type_cast;

struct gr_type_info
{
	struct gr_class* t_class; 

	const char* t_name;
	size_t t_size;  /* object size */

	struct gr_type_ops* t_ops;
};
typedef  struct gr_type_info GrTypeInfo;

typedef GrObject* (*GrBinaryFunc)(GrObject*,GrObject*);
typedef GrObject* (*GrUnaryFunc)(GrObject*);
typedef int (*GrCmpFunc)(GrObject*,GrObject*);
typedef int (*GrBoolFunc)(GrObject*);
typedef ssize_t (*GrHashFunc)(GrObject*);
typedef GrObject* (*GrNewFunc)(GrObject*);
typedef int (*GrPrintFunc)(GrObject*,FILE*);

struct gr_type_ops
{
	struct gr_operator_ops* t_operator;
	struct gr_operator_ops* t_operator_inverse;
	struct gr_type_cast* t_type_cast;

	GrHashFunc t_hash;

	GrPrintFunc t_print;

	GrObject* (*t_iter)(GrObject*);
	GrObject* (*t_iter_next)(GrObject*);

	int (*t_set_attr)(GrObject*,GrObject* s,GrObject* v,long flags);
	int (*t_get_attr)(GrObject*,GrObject* s,long flags);


	GrNewFunc t_new;

	int (*t_destruct)(GrObject*);
};
typedef struct gr_type_ops GrTypeOps;



struct gr_operator_ops 
{
	int (*t_set_item)(GrObject*,GrObject*,GrObject*);
	GrObject* (*t_get_item)(GrObject*,GrObject*);

	GrUnaryFunc t_negative;
	GrUnaryFunc t_positive;
	GrUnaryFunc t_negated;

	GrBinaryFunc t_mul;
	GrBinaryFunc t_div;
	GrBinaryFunc t_mod;

	GrBinaryFunc t_plus;
	GrBinaryFunc t_minus;

	GrBinaryFunc t_lshift;
	GrBinaryFunc t_rshift;

	GrBinaryFunc t_and;
	GrBinaryFunc t_xor;
	GrBinaryFunc t_or;

	GrCmpFunc t_cmp;

	GrBoolFunc t_bool;

};
typedef struct gr_operator_ops GrOperatorOps;

struct gr_type_cast
{
	GrObject* (*t_float)(GrObject*);
	GrObject* (*t_int)(GrObject*);
	GrObject* (*t_long)(GrObject*);
	GrObject* (*t_string)(GrObject*);
};
typedef struct gr_type_cast GrTypeCast;

#endif /*_CODGER_OBJECT_TYPE_INFO_H_*/
