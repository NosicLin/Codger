#include"except.h"
#include<stdio.h>
#include<stdarg.h>
#include<utility_c/marocs.h>
#define FORMAT_BUF_SIZE 1024
static char s_format_buf[FORMAT_BUF_SIZE];
static int except_flags=0;

static int s_except_type=0;

/* exception interface*/
int vm_except_happened()
{
	return except_flags;
}
void vm_clear_except()
{
	except_flags=0;
}
void vm_set_except(int flags)
{
	except_flags=flags;
}


/*FIXME use for temp*/
void except_divzero_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_DIV_ZERO;
	printf("DivZeroErr:%s\n",s_format_buf);
}


void except_type_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_TYPE_ERR;
	printf("TypeErr:%s\n",s_format_buf);
}
void except_value_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_VALUE_ERR;
	printf("ValueErr:%s\n",s_format_buf);
}
void except_overflow_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_OVER_FLOW;
	printf("OverFlowErr:%s\n",s_format_buf);
}
void except_index_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_INDEX_ERROR;
	printf("IndexErr:%s\n",s_format_buf);
}
void except_key_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_KEY_ERR;
	printf("KeyErr:%s\n",s_format_buf);
}

void except_unkown_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_UNKOWN;
	printf("UnkownErr:%s\n",s_format_buf);
}

void except_name_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_NAME_ERR;
	printf("NameErr:%s\n",s_format_buf);
}
void except_syntax_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_SYNTAX_ERR;
	printf("SyntaxErr:%s\n",s_format_buf);
}

void except_iter_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_ITER_ERR;
	printf("IterErr:%s\n",s_format_buf);
}
void except_args_err_format(const char* s,...)
{
	int n;
	va_list ap;
	va_start(ap,s);
	n=vsnprintf(s_format_buf,FORMAT_BUF_SIZE,s,ap);
	va_end(ap);
	if(n>=FORMAT_BUF_SIZE||n<0)
	{
		WARN("format message failed(%d)",n);
		s_format_buf[0]='\0';
	}
	except_flags=1;
	s_except_type=E_ARGS;
	printf("ArgsErr:%s\n",s_format_buf);
}

void except_iter_stop()
{
	s_except_type=E_ITER_STOP;
	except_flags=1;
}
int vm_except_type(){return s_except_type;}
