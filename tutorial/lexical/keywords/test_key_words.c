#include"lexical.h"
#include<stdio.h>
#include<string.h>
#include"token.h"
int main()
{
	char buf[1024];
	printf("input __quit__ exit\n");
	printf("input:");
	scanf("%s",buf);
	while(strcmp(buf,"__quit__")!=0)
	{
		int token=symbol_type(buf);
		printf("it's %s\n\n",token_info[token]);
		printf("input:");
		scanf("%s",buf);
	}
	return 0;
}

