#ifndef _REDY_RTYPE_STRING_H_
#define _REDY_RTYPE_STRING_H_

#include"rtype.h"
#include<string.h>
#include"rstd/redy_std.h"
struct bt_string
{
	INHERIT_ROBJECT;	
	int s_length;
	ssize_t s_hash;
	char s_value[0];
};
typedef struct bt_string BtString;

#ifdef RTYPE_DEBUG 

static inline BtString* R_TO_S(Robject* rt)
{
	assert(rt_type(rt)==RT_STRING);
	return (BtString*) rt;
}
static inline Robject* S_TO_R(BtString* bt)
{
	assert(rt_type((Robject*)bt)==RT_STRING);
	return (Robject*)bt;
}

#else 

#define R_TO_S(bt) ((BtString*)bt)
#define S_TO_R(btl) ((Robject*)btl)

#endif /*RTYPE_DEBUG*/


/* implement in bt_string.c */ 
/* constructor */
BtString* btstring_malloc(int length);
BtString* btstring_create(char* str);
BtString* btstring_create_empty();
BtString* btstring_from_char(char c);
BtString* btstring_create_no_esc(char* str);

/* expr*/
BtString* btstring_get_item(BtString* bs,int index);
BtString* btstring_plus(BtString* x,BtString* y);
int btstring_cmp(BtString* x,BtString* y,int op);

static inline int btstring_lt(BtString* x,BtString* y)
{
	return strcmp(x->s_value,y->s_value)<0;
}
static inline int btstring_le(BtString* x,BtString* y)
{
	return strcmp(x->s_value,y->s_value)<=0;
}
static inline int btstring_gt(BtString* x,BtString* y)
{
	return strcmp(x->s_value,y->s_value)>0;
}
static inline int btstring_ge(BtString* x,BtString* y)
{
	return strcmp(x->s_value,y->s_value)>=0;
}
static inline int btstring_eq(BtString* x,BtString* y)
{
	return strcmp(x->s_value,y->s_value)==0;
}
static inline int btstring_ne(BtString* x,BtString* y)
{
	return strcmp(x->s_value,y->s_value)!=0;
}

static inline int btstring_bool(BtString* bs)
{
	return bs->s_length!=0;
}

static inline ssize_t btstring_hash(BtString* bs)
{
	ssize_t ret=bs->s_hash;
	return ret==-1?-2:ret;
}
int btstring_print(BtString* bs,FILE* f,int flags);



/* destructor */
static inline void bt_string_free(BtString* bs)
{
	ry_free(bs);
}

static inline char* bt_string_str(BtString* bts)
{
	return  bts->s_value;
}


#endif 
