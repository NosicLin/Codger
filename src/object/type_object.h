#ifndef _REDY_OBJECT_TYPE_OBJECT_H_
#define _REDY_OBJECT_TYPE_OBJECT_H_
#include<stdio.h>
struct robject;
struct expr_ops;
struct object_ops;
struct type_object
{
	const char* t_name;
	const int  t_type;
	struct expr_ops* t_expr_funcs;
	struct object_ops* t_object_funcs;
	int (*t_rich_cmp)(struct robject*,struct robject* ,int);
	ssize_t (*t_hash)(struct robject*);
};
typedef struct type_object TypeObject;

struct object_ops
{
	void (*ro_free)(struct robject*);
	void (*ro_init)(struct robject*);
};

struct expr_ops
{
	/*posifix operator '[]' */
	struct robject* (*ro_get_item)(struct robject*,struct robject* );
	int (*ro_set_item)(struct robject*,struct robject* index,struct robject* item);

	/* unary operator + and - */
	struct robject* (*ro_negative)(struct robject* );
	struct robject* (*ro_positive)(struct robject* );

	/*multiply(*), divide(/) ,mod(%)*/
	struct robject* (*ro_mul)(struct robject* ,struct robject*);
	struct robject* (*ro_div)(struct robject* ,struct robject*);
	struct robject* (*ro_mod)(struct robject* ,struct robject*);

	/*plus (+) and minus(-)*/
	struct robject* (*ro_plus)(struct robject*, struct robject*);
	struct robject* (*ro_minus)(struct robject* ,struct robject*);

	/* left shift(<<) and right shift(>>) */
	struct robject* (*ro_lshift)(struct robject* , struct robject*);
	struct robject* (*ro_rshift)(struct robject* , struct robject*);

	/* less than(lt <), less equal(le <=) */
	int (*ro_lt)(struct robject* ,struct robject*);
	int (*ro_le)(struct robject* ,struct robject*);

	/* equal (==), not equal(ne !=)*/
	int (*ro_eq)(struct robject* ,struct robject*);
	int (*ro_ne)(struct robject* ,struct robject*);

	/* greater than( gt,>), greater equal (ge, <=)*/
	int (*ro_gt)(struct robject* ,struct robject*);
	int (*ro_ge)(struct robject* ,struct robject*);

	/*bit_and(&), bit_or(|) bit_xor(^) bit_negated*/
	struct robject* (*ro_and)(struct robject*,struct robject*);
	struct robject* (*ro_or)(struct robject* ,struct robject*);
	struct robject* (*ro_xor)(struct robject*,struct robject*);
	struct robject* (*ro_negated)(struct robject*);

	/*logic and ,logic_or */
	int (*ro_bool)(struct robject*);

	/*used for print sentence */
	int (*ro_print)(struct robject*,FILE* f,int flags);

	/*get iterator */
	struct robject* (*ro_iter)(struct robject*);
};

enum KnowObjectType
{
	TYPE_UNKOWN=0,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_LONG,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_ITER,
	TYPE_NULL,
	TYPE_HASH,
};


#endif /*_REDY_OBJECT_TYPE_OBJECT_H_*/
