#include<stdio.h>
#include<string.h>
#include "lexical.h"
#include "sl_states.h"
/*返回值－1则表示识别错误，其它值表示能识别的最大位置*/
int driver(struct state* s,char* str,struct state* info)
{
	int length=strlen(str);
	int i;
	struct state* cur_st=s;     /*当前状态*/
	struct state* next_st;      /*下一状态*/
	int last_final=-1;
	for(i=0;i<length;i++)
	{
		next_st=state_next(cur_st,str[i]);    /*获得下一状态*/
		//printf("%s->[%c]->%s ",cur_st->s_name,str[i],next_st->s_name);
		if(next_st==&lex_state_err)           /*如果返回状态为lex_state_err，则表明需要错误处理*/
		{
			return last_final;
		}
		else
		{
			cur_st=next_st;
			if(cur_st->s_final)              /*判继该状态是否为终态*/
			{
				last_final=i;                /*如果为终态，则保存识别的信息*/
				*info=*cur_st;
			}
		}
	}
	return last_final;
}

