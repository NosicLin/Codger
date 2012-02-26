#include<stdio.h>
#include<string.h>
#include<lexical.h>
#include<sl_states.h>
#include<token.h>
int driver(struct state* s,char* str,struct state* info);
int main()
{
	char buf[2048];
	char result[2048];
	struct state s;
	while(1)
	{
		scanf("%s",buf);
		if(strcmp(buf,"__quit__")==0)
			break;

		scanf("%s",result);

		int ret=driver(&ft_begin,buf,&s);
		if(ret==-1)   
		{
			if(strcmp(result,"err")!=0)
			{
				goto error;
				break;
			}
		}
		else
		{
			if(ret+1==strlen(buf))
			{
				if(s.s_token==TOKEN_FLOAT)
				{
					if(strcmp("f",result)!=0)
					{
						goto error;
					}
				}
				else if(s.s_token==TOKEN_EXP_FLOAT)
				{
					if(strcmp("ef",result)!=0)
					{
						goto error;
					}
				}
				else
				{
					goto error;
				}

			}
				
			else
			{
				if(strcmp(result,"err")!=0)
				{
					goto error;
					break;
				}

			}
		}
	}
	printf("ProgramOk\n");
	return 0;
error:
	printf("ProgramErr:%s,%s\n",buf,s.s_name);
	return 0;
}

