#ifndef _REDY_RTYPE_BT_LONG_H_
#define _REDY_RTYPE_BT_LONG_H_
#include"robject.h"
#include"big_integer.h"
#include"stdlib.h"
struct bt_long
{
	struct robject l_base;
	struct big_integer* l_value;
};

typedef struct bt_long BtLong;

/* constructor */
BtLong* bt_long_malloc();
BtLong* bt_long_create(BGInteger* bg);
BtLong* bt_long_from_int(int value);
BtLong* bt_long_from_str(char* str);

/* deconstructor */
static inline void bt_long_free(BtLong* btl)
{
	bg_free(btl->l_value);
	free(btl);
}


/* other interface */
static inline int bt_long_is_zero(BtLong* bl)
{
	return bl->l_value->b_len==0;
}

static inline int bt_long_overflow_int(BtLong* bl)
{
	return bg_overflow_int(bl->l_value);
}
static inline int bt_long_to_int(BtLong* bl)
{
	return  bg_to_int(bl->l_value);
}

#endif



	
