#ifndef _REDY_RTYPE_INT_H_
#define  _REDY_RTYPE_INT_H_
#include"robject.h"
#include"stdlib.h"

/* prefix bt short for base type*/
struct bt_int
{
	struct robject i_base;
	int i_value;
};
typedef struct bt_int BtInt;


/*constructor*/
BtInt* bt_int_create(int value);
BtInt* bt_int_from_str(char* str);
BtInt* bt_int_malloc();


/*deconstructor*/
static inline void bt_int_free(BtInt* bi)
{
	free(bi);
}

/*value getter and setter */
static inline int bt_int_get(BtInt* bti)
{
	return bti->i_value;
}
static inline void bt_int_set(BtInt* bti,int value)
{
	bti->i_value=value;
}

/*other interface*/
static inline int bt_int_is_zero(BtInt* bi)
{
	return bi->i_value==0;
}

#endif /*_REDY_RTYPE_INT_H_*/

