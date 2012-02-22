#include<lexical.h>
#include<stdio.h>
#include<string.h>
/*返回值－1则表示识别错误，其它值表示能识别的最大位置*/

int driver(struct automaton* am,char* str)
{
	int length=strlen(str);   /*字符串长度*/
	int i;
	int cur_state=am->begin_state;   /*得到开始状态*/
	int last_final=-1;
	for(i=0;i<length;i++)
	{
		int input_type=am->type_map[str[i]];     /*根据当前字符得到输入类型*/
		
		/*根据当前状态和输入类型，查状态转换表，得到下一个状态*/
		int next_state=am->states_matrix[cur_state*am->inputs_num+input_type]; 
		
		/*当前状态是否能识别当前输入类型*/
		if(next_state==LEX_ERR)
		{
			return last_final;
		}
		else
		{
			cur_state=next_state;
			/*如果当前状态为终态，则记录下来识别位置*/
			if(am->states_info[cur_state]==1)
			{
				last_final=i;
			}
		}
	}
	return last_final;
}

int main()
{
	char buf[2048];
	char buf_copy[2048];
	printf("input:__quit__ exit\n");
	printf("input:");
	scanf("%s",buf);
	while(strcmp(buf,"__quit__")!=0)
	{
		int ret=driver(&am_string,buf);
		if(ret==-1)   
		{
			printf("Sorry,Not String\n");
		}
		else
		{
			memcpy(buf_copy,buf,ret+1);
			buf_copy[ret+1]='\0';
			printf("Recongise: %s\n",buf_copy);
			if(ret+1==strlen(buf))
			{
				printf("It's String\n");
			}
			else
			{
				printf("It's Not String\n");
			}
		}
		printf("\ninput:");
		scanf("%s",buf);
	}
	return 0;
}




		
