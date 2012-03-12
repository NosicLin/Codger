#ifndef _REDY_RTYPE_INT_H_'
#define  _REDY_RTYPE_INT_H_
#include"robject.h"
/* prefix bt short for base type*/

struct bt_int
{
	struct robject i_base;
	int i_value;
};

typedef struct bt_int BTInt;

BTInt* bt_int_create();

static inline void bt_int_init(BTInt* bti, int value)
{
	bti->i_value=value;
}
static inline void bt_int_get(BTInt* bti)
{
	return bti->i_value;
}
static inline void bt_int_set(BTInt* bti,int value)
{
	bti->i_value=value;
};


#endif /*_REDY_RTYPE_INT_H_*/

