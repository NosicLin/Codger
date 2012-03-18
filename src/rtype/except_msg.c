#include<stdio.h>
#include"except_msg.h"
static char msg_buf[1024];

char* MSG_STRING_PLUS(char* l)
{
	sprintf(msg_buf,"cann't concatenate 'str' and '%s' objects",l);
	return msg_buf;
}
char* MSG_CMP(char* l ,char* r )
{
	sprintf(msg_buf,"unsupported compare for '%s' and '%s'",l,r);
	return msg_buf;
}

char* MSG_STRING_INDEX_TYPE(char* name)
{
	sprintf(msg_buf,"string index must be integer, not '%s'",name);
	return msg_buf;
}
char* MSG_ARRAY_INDEX_TYPE(char* name)
{
	sprintf(msg_buf,"array index must be integer, not '%s'",name);
	return msg_buf;
}

char* MSG_OPER(char* l,char* r ,char* ops)
{
	sprintf(msg_buf,"unsupported operand %s for '%s' and '%s'",ops,l,r);
	return msg_buf;
}

char* MSG_DIV(char* type)
{
	sprintf(msg_buf,"%s division or module by zero",type);
	return 0;
}
