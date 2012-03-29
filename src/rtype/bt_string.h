#ifndef _REDY_RTYPE_STRING_H_
#define _REDY_RTYPE_STRING_H_

#include"rtype.h"
struct bt_string
{
	INHERIT_ROBJECT;	
	int s_length;
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
BtString* bt_string_malloc(int length);
BtString* bt_string_create(char* str);
BtString* bt_string_create_empty();
BtString* bt_string_from_char(char c);

/* destructor */
static inline void bt_string_free(BtString* bs)
{
	free(bs);
}

static inline char* bt_string_str(BtString* bts)
{
	return  bts->s_value;
}


#endif 
