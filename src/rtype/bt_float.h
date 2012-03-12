#ifndef _REDY_RTYPE_FLOAT_H_
#define _REDY_RTYPE_FLOAT_H_

struct bt_float
{
	struct robject f_base;
	float f_value;
};


BTFloat* bt_float_create(float value);


#endif /*_REDY_RTYPE_FLOAT_H_*/
