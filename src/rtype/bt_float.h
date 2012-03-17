#ifndef _REDY_RTYPE_FLOAT_H_
#define _REDY_RTYPE_FLOAT_H_
#include<stdlib.h>
struct bt_float
{
	struct robject f_base;
	float f_value;
};
typedef struct bt_float BtFloat;


/* default constructor*/
BtFloat* bt_float_malloc();
/*constructor */
BtFloat* bt_float_create(float value);
BtFloat* bt_float_from_str(char* str);

/*deconstructor*/
static inline void bt_float_free(BtFloat* btf)
{
	free(btf);
}

static inline int bt_float_is_zero(BtFloat* bf)
{
	return bf->f_value==0;
}

/*setter and getter */
static inline float bt_float_get(BtFloat* bf)
{
	return bf->f_value;
}
static inline void bt_float_set(BtFloat* bf,float value)
{
	bf->f_value=value;
}

#endif /*_REDY_RTYPE_FLOAT_H_*/
