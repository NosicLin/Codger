#ifndef _REDY_RTYPE_STRING_H_
#define _REDY_RTYPE_STRING_H_


struct bt_string
{
	struct robject s_base;
	char* s_value;
	int s_length;
};
typedef struct bt_string BTString;

/* implement in bt_string.c */ 
BTString* bt_string_create(char* str);
BTString* bt_string_create_with_length(char* s,int length)
BTString* bt_string_create_empty();
BTString* bt_string_create_from_char(char c);

static inline char* bt_string_str(BTString* bts)
{
	return  bts->s_value;
}

#endif 
