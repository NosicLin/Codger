#include<stdio.h>
#include<string.h>
#include "lexical.h"
int driver(struct state* s,char* str,struct state* info)
{
	int length=strlen(str);
	int i;
	struct state* cur_st=s;    
	struct state* next_st;    
	int last_final=-1;
	for(i=0;i<length;i++)
	{
		next_st=state_next(cur_st,str[i]); 
		if(next_st==&lex_state_err)       
		{
			return last_final;
		}
		else
		{
			cur_st=next_st;
			if(cur_st->s_final)          
			{
				last_final=i;           
				*info=*cur_st;
			}
		}
	}
	return last_final;
};

