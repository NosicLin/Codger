#include "lexical.h"
#include<stdio.h>
#include<string.h>
/*返回值－1则表示识别错误，其它值表示能识别的最大位置*/
void print_automaton(struct automaton* am)
{
	printf("automaton{\n");
	printf("\tstates:%d\n",am_float.states_num);
	printf("\tinput_type:%d\n",am_float.inputs_num);
	printf("\tstate_martix{\n");
	int i,j;
	for(i=0;i<am->states_num;i++)
	{
		printf("\t\t");
		for(j=0;j<am->inputs_num;j++)
		{
			printf("%d\t",am->states_matrix[i*am->inputs_num+j]);
		}
		printf("\n");
	}
	printf("\t}\n");
	printf("}\n");
}

int driver(struct automaton* am,char* str,struct state* s)
{
	int length=strlen(str);   /*字符串长度*/
	int i;
	int cur_state=am->begin_state;   /*得到开始状态*/
	int last_final=-1;
	
	//printf("\n");
	for(i=0;i<length;i++)
	{
//		printf("%d ",cur_state);

		int input_type=am->type_map[str[i]];     /*根据当前字符得到输入类型*/
		
		/*根据当前状态和输入类型，查状态转换表，得到下一个状态*/
		int next_state=am->states_matrix[cur_state*am->inputs_num+input_type]; 
		
		//printf("[%d]->%c(%d)->[%d]  ",cur_state,str[i],am->type_map[str[i]],next_state);
		/*当前状态是否能识别当前输入类型*/
		if(next_state==LEX_ERR)
		{
			return last_final;
		}
		else
		{
			cur_state=next_state;
			/*如果当前状态为终态，则记录下来识别位置*/
			if(am->states_info[cur_state].final==1)
			{
				last_final=i;
				/*得到该终态的信息*/
				*s=am->states_info[cur_state];
			}
		}
	}
	return last_final;
}

int main()
{
	char buf[2048];
	char buf_copy[2048];
	print_automaton(&am_float);
	printf("input:__quit__ exit\n");
	printf("input:");
	scanf("%s",buf);
	struct state s;
	while(strcmp(buf,"__quit__")!=0)
	{
		int ret=driver(&am_float,buf,&s);
		if(ret==-1)   
		{
			printf("Sorry,Not Float\n");
		}
		else
		{
			memcpy(buf_copy,buf,ret+1);
			buf_copy[ret+1]='\0';
			printf("%s: %s\n",s.name,buf_copy);
			if(ret+1==strlen(buf))
			{
				printf("It's %s\n",s.name);
			}
			else
			{
				printf("It's Not Float\n");
			}
		}
		printf("\ninput:");
		scanf("%s",buf);
	}
	return 0;
}




		
