#ifndef _REDY_RTYPE_BOOLEAN_H_
#define _REDY_RTYPE_BOOLEAN_H_

/*boolean is a type of integer*/
#include"bt_int.h"

typedef BtInt BtBoolean;
#define B_TO_R I_TO_R
#define R_TO_B R_TO_I

/*implement in bt_int.c*/
BtBoolean* bt_boolean_create(int value);
int bt_boolean_is_false(Robject* value);
int bt_boolean_is_true(Robject* value);


#endif 
