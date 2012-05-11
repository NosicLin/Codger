#include<stdio.h>
#include"lexical.h"
#include"token.h"
#include<string.h>

extern struct keyword key_words[];
int main()
{

	int err=0;
	int i=0;
	for(i=0;i<KEYWORD_NUM-2;i++)
	{
		if(strcmp(key_words[i].k_name,key_words[i+1].k_name)<0)
		{
			continue;
		}
		else
		{
			err=1;
			printf("key words err (%s,%s)\n",key_words[i].k_name,
					key_words[i+1].k_name);
		}
	}
	if(err)
	{
		printf("key words err\n");
	}
	else
	{
		printf("key ok\n");
	}
	return 0;
}


