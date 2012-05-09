#ifndef _REDY_RTYPE_BT_BOOL_H_
#define _REDY_RTYPE_BT_BOOL_H_
#include"bt_int.h"
typedef BtInt BtBool;

#define B_TO_R(x) I_TO_R(x)
#define R_TO_B(x) R_TO_I(x)

/*implement in bt_int.c*/
BtBool* btbool_create(int value);
BtBool* btbool_false();
BtBool* btbool_true();
int  btbool_bool(BtBool* bb);

BtBool* ObjectFalse;
BtBool* ObjectTrue;


#endif 

