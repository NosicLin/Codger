#ifndef _REDY_RTYPE_STRING_H_
#define _REDY_RTYPE_STRING_H_
#include"robject.h"
struct bt_string
{
	struct robject s_base;
	int s_length;
	char s_value[0];
};
typedef struct bt_string BtString;

#define S_TO_R(bts) ((Robject*)bts)
#define R_TO_S(rt) ((BTString*)rt) 

/* implement in bt_string.c */ 
void bg_string_malloc(int length);
BtString* bt_string_create(char* str);
BtString* bt_string_create_empty();
BtString* bt_string_from_char(char c);

static inline char* bt_string_str(BtString* bts)
{
	return  bts->s_value;
}

#endif 
