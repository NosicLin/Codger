#include<stdlib.h>
#include<stdio.h>
#include<args.h>

int main()
{
	char buffer1[1024];
	char* buffer=buffer1;
	size_t length=0;
	char divide[1024];
	int i;
	while(1)
	{
		printf("input  some world:\n");
		int read=-1;
		if((read=getline(&buffer,&length,stdin))!=-1)
		{
			printf("input divide chars:\n");
			scanf("%s",divide);
			getc(stdin);
			buffer[read-1]=0;

			struct  args* arg=create_args(buffer,divide);
			printf("args->num=%d\n",arg->num);
			for(i=0;i<arg->num;i++)
			{
				printf("[%s] ",arg->parg[i]);
			}
			printf("\n");
			free_args(arg);
		}
		else
		{
			break;
		}
	}
	return 0;
}


