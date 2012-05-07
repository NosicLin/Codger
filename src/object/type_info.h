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
typedef int (*GrSetItemFunc)(GrObject*,GrObject*,GrObject*);
typedef GrObject* (*GrGetItemFunc)(GrObject*,GrObject*);
typedef GrObject* (*GrCallFunc)(GrObject*,GrObject*,GrObject*);
typedef GrObject* (*GrIterFunc)(GrObject*);
typedef GrObject* (*GrIterNextFunc)(GrObject*);

typedef int (*GrSetAttrFunc)(GrObject*,GrObject*,GrObject* v,long);
typedef GrObject* (*GrGetAttrFunc)(GrObject*,GrObject*,long);

typedef int (*GrDestructFunc)(GrObject*);
struct gr_type_ops
{
	GrHashFunc t_hash;
	GrCmpFunc t_rich_eq;

	GrPrintFunc t_print;

	GrIterFunc t_iter;
	GrIterNextFunc t_iter_next;

	GrGetAttrFunc t_get_attr;
	GrSetAttrFunc t_set_attr;



	GrNewFunc t_new;

	GrDestructFunc t_destruct;


	GrCallFunc t_call;
	GrSetItemFunc t_set_item;
	GrGetItemFunc t_get_item;

	GrUnaryFunc t_negative;
	GrUnaryFunc t_positive;
	GrUnaryFunc t_negated;
	GrBoolFunc t_bool;

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

	/* for reverse  */
	GrBinaryFunc t_mul_reverse;
	GrBinaryFunc t_div_reverse;
	GrBinaryFunc t_mod_reverse;

	GrBinaryFunc t_plus_reverse;
	GrBinaryFunc t_minus_reverse;

	GrBinaryFunc t_lshift_reverse;
	GrBinaryFunc t_rshift_reverse;

	GrBinaryFunc t_and_reverse;
	GrBinaryFunc t_xor_reverse;
	GrBinaryFunc t_or_reverse;

	GrCmpFunc t_cmp_reverse;

};
typedef struct gr_type_ops GrTypeOps;

#endif /*_CODGER_OBJECT_TYPE_INFO_H_*/
