#include<stdio.h>
#include<string.h>
#include<lexical.h>
#include<sl_states.h>
int driver(struct state* s,char* str,struct state* info);
int main()
{
	char buf[2048];
	char buf_copy[2048];
	printf("input:__quit__ exit\n");
	printf("input:");
	scanf("%s",buf);
	struct state s;
	while(strcmp(buf,"__quit__")!=0)
	{
		int ret=driver(&nu_begin,buf,&s);
		if(ret==-1)   
		{
			printf("Sorry,Not Token\n");
		}
		else
		{
			memcpy(buf_copy,buf,ret+1);
			buf_copy[ret+1]='\0';
			printf("%s: %s\n",s.s_name,buf_copy);
			if(ret+1==strlen(buf))
			{
				printf("It's %s\n",s.s_name);
			}
			else
			{
				printf("It's Not Token\n");
			}
		}
		printf("\ninput:");
		scanf("%s",buf);
	}
	return 0;
}

