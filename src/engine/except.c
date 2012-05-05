#include"except.h"
#include<stdio.h>
#include<utility_c/marocs.h>
#include<stdarg.h>

#define FORMAT_BUF_SIZE 1024
static char s_format_buf[FORMAT_BUF_SIZE];

static long s_except_happed=0;


int GrExcept_SetException(const char* name,const char* msg)
{
	s_except_happed=1;
	printf("%s:%s\n",name,msg);
	return 0;
}
#define GR_EXCEPT_FORMAT_MSG \
	do{ \
		int n; \
		va_list ap; \
		va_start(ap,s); \
		n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap); \
		va_end(ap); \
		if(n>=FORMAT_BUF_SIZE||n<0) \
		{ \
			WARN("format message failed(%d)",n); \
			s_format_buf[0]='\0'; \
		} \
	}while(0)


void GrErr_DiveZeroFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("DivZeroErr",s_format_buf);
}


void GrErr_NegitiveShift(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("TypeErr",s_format_buf);
}


void GrErr_BugFromat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("BUG",s_format_buf);
}
void GrErr_HashFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("TypeErr",s_format_buf);
}
void GrErr_MemFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("MemErr",s_format_buf);
}
void GrErr_KeyFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("TypeErr",s_format_buf);
}
void GrErr_TypeFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("TypeErr",s_format_buf);
}
void GrErr_IndexFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("IndexErr",s_format_buf);
}
void GrErr_OutOfRangeFormat(const char* s,...)
{
	GR_EXCEPT_FORMAT_MSG;
	GrExcept_SetException("OutOfRangeErr",s_format_buf);
}

int GrExcept_Happened()
{
	return s_except_happed;
}

void GrExcept_Clr()
{
	s_except_happed=0;

}

