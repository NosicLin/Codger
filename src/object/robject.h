#ifndef _REDY_RTYPE_ROBJECT_H_
#define _REDY_RTYPE_ROBJECT_H_
#include"type_object.h"
#include<stdio.h>
struct  robject 
{
	ssize_t r_ref;
	struct type_object* r_type;
};
typedef struct robject Robject;
#define INHERIT_ROBJECT struct robject r_base 
#define TO_ROBJECT(x) ((Robject*)x)
#define robject_new(TYPE,type_ops) \
	((TYPE*)__robject_new(sizeof(TYPE),type_ops))

void* __robject_new(ssize_t size,TypeObject* t);
void robject_init(Robject* r,TypeObject* t);

static inline void robject_addref(Robject* r){r->r_ref++;}
void robject_release(Robject* r);
static inline ssize_t robject_refcnt(Robject* r){ return r->r_ref;}
static inline void robject_initref(Robject* r){r->r_ref=1;}

static inline const char* robject_name(Robject* r)
{
	return r->r_type->t_name;
}
static inline TypeObject* robject_type(Robject* r){return r->r_type;}
static inline int robject_typeid(Robject* r){return r->r_type->t_type;}

/* robject expr */
Robject* robject_get_item(Robject* r,Robject* index);
int robject_set_item(Robject* r,Robject* index,Robject* value);
/*unary expr*/
Robject* robject_positive(Robject* r);
Robject* robject_negative(Robject* r);
Robject* robject_negated(Robject* r);
/*binary expr*/

/*multiply_expr*/
Robject* robject_mul(Robject* x,Robject* y);
Robject* robject_div(Robject* x,Robject* y);
Robject* robject_mod(Robject* x,Robject* y);

/*additive_expr*/
Robject* robject_plus(Robject* x,Robject* y);
Robject* robject_minus(Robject* x,Robject* y);

/*shift_expr*/
Robject* robject_lshift(Robject* x,Robject* y);
Robject* robject_rshift(Robject* x,Robject* y);

/*relational_expr*/
int robject_lt(Robject* x,Robject* y);
int robject_le(Robject* x,Robject* y);
int robject_gt(Robject* x,Robject* y);
int robject_ge(Robject* x,Robject* y);

/*equal_expr*/
int robject_ne(Robject* x,Robject* y);
int robject_eq(Robject* x,Robject* y);

/*bitwise_expr*/
Robject* robject_or(Robject* x,Robject* y);
Robject* robject_and(Robject* x,Robject* y);
Robject* robject_xor(Robject* x,Robject* y);

/*logic_expr*/
int robject_bool(Robject* rt);

/*iter expr*/
Robject* robject_iter(Robject* r);
Robject* robject_next(Robject* r);

ssize_t robject_hash(Robject* rt);
#define CMP_LT  0  /*<*/
#define CMP_LE  1  /*<=*/
#define CMP_NE  2  /*!=*/
#define CMP_EQ  3  /*==*/
#define CMP_GE  4  /*>=*/
#define CMP_GT  5  /*>*/
#define CMP_NOT_SUPPORT -2


/* -2 CMP_NOT_SUPPORT
 * -1 error 
 *  0 false
 *  1 other
 */
int robject_richcmp(Robject* x,Robject* y,int op);

/* print flags*/
#define PRINT_FLAGS_NEWLINE 0x1
void robject_print(Robject* rt,FILE* f,int flags);
#endif 

