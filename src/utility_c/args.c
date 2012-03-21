#include"args.h"
#include<stdlib.h>

static inline int is_in_str(char c,const char* str)
{
	while(*str)
		if(c==*(str++)) return 1 ;
	return 0;
}
int cal_args_num(const char* buffer,const char* divide)
{
	int args_num=0;
	int now_word=0;
	while(*buffer)
	{
		if(now_word)
		{
			if(is_in_str(*buffer,divide))
			{
				now_word=0;
			}
		}
		else
		{
			if(!is_in_str(*buffer,divide))
			{
				now_word=1;
				args_num++;
			}
		}
		buffer++;
	}
	return args_num;
}



struct args* create_args(char* buffer,const char* divide)
{
	int args_num=0;
	int now_word=0;
	int in_str;
	args_num=cal_args_num(buffer,divide);
	struct args* arg=(struct args*)malloc(sizeof(struct args)+sizeof(char*)*args_num);
	arg->num=args_num;
	arg->parg=(char**)(((char*)arg)+sizeof(struct args));

	int pos=0;
	while(*buffer)
	{

		in_str=is_in_str(*buffer,divide);
		if(now_word)
		{
			if(in_str)
			{
				now_word=0;
				*buffer='\0';
			}
		}
		else
		{
			if(!in_str)
			{
				arg->parg[pos++]=buffer;
				now_word=1;
			}
		}
		buffer++;
	}
	return arg;
}

void free_args(struct args* arg)
{
	free(arg);
}


