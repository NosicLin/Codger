#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_OTHER 0
#define STRING_NEWLINE 1
#define STRING_BACKSLASH 2
#define STRING_QUITE 3

#define ASSIC_NUM 256
char id_array[ASSIC_NUM];
void print_array(char* array)
{
	int i;
	for(i=0;i<ASSIC_NUM;i++)
	{
		if(i%32==0&&i!=0)
		{
			printf("\n");
		}
		if(i!=ASSIC_NUM-1)
		{
			printf("%d,",array[i]);
		}
		else
		{
			printf("%d\n",array[i]);

		}
	}
}




void id_array_create()
{
	//printf("%d\n",sizeof(id_array));
	memset(id_array,0,sizeof(id_array));
	id_array['\\']=STRING_BACKSLASH;
	id_array['"']=STRING_QUITE;
	id_array['\n']=STRING_NEWLINE;


}

	
int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
