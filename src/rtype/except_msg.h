#ifndef _REDY_EXCEPTION_EXCEPT_MSG_H_
#define _REDY_EXCEPTION_EXCEPT_MSG_H_

#define OPER_MUL "*"
#define OPER_DIV "/"
#define OPER_MOD "%"
#define OPER_PLUS "+"
#define OPER_MINUS "-"
#define OPER_LSHIFT "<<"
#define OPER_RSHIFT ">>"
#define OPER_CMP "cmp"
#define OPER_LE "<="
#define OPER_LT "<"
#define OPER_GE ">="
#define OPER_GT ">"
#define OPER_NE "!="
#define OPER_EQ "=="
#define OPER_AND "&"
#define OPER_OR "|"
#define OPER_XOR "^"
#define OPER_NEGATIVE "-"
#define OPER_NEGATED "~"
#define OPER_POSITIVE "+"


#define MSG_BINARY_UNSUPPORT "unsupport operand(%s) for '%s'"
#define MSG_LONG_OVERFLOW "long overflow integer"
#define MSG_STRING_INDEX_NEGATIVE "string index must be positive,not negative"
#define MSG_STRING_OUT_OF_RANGE "string index out of range"
#define MSG_SHIFT_NEGATIVE "negative shift count"
#define MSG_ARRAY_OUT_OF_RANGE "array index out of range"

char* MSG_STRING_PLUS(char*);
char* MSG_CMP(char* ,char* );
char* MSG_STRING_INDEX_TYPE(char* name);
char* MSG_ARRAY_INDEX_TYPE(char* name);
char* MSG_OPER(char* l,char* r ,char* ops);
char* MSG_DIV(char* type);
char* MSG_UEXPR(char* name,char* ops);


#endif 


