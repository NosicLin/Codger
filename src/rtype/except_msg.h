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

#include<object/robject.h>
static inline char* CMP_NAME(int op)
{
	switch(op)
	{
		case CMP_LT:
			return "<";
		case CMP_LE:
			return "<=";
		case CMP_GE:
			return ">=";
		case CMP_GT:
			return ">";
		case CMP_EQ:
			return "==";
		case CMP_NE:
			return "!=";
	}
	return "Unkown CMP";
}

	


#define MSG_BINARY_UNSUPPORT "unsupport operand(%s) for '%s' and '%s'"
#define MSG_LONG_OVERFLOW "long overflow integer"
#define MSG_STRING_INDEX_NEGATIVE "string index must be positive,not negative"
#define MSG_STRING_OUT_OF_RANGE "string index out of range"
#define MSG_SHIFT_NEGATIVE "negative shift count"
#define MSG_ARRAY_OUT_OF_RANGE "array index out of range"

#endif 


