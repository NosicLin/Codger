#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ID_ERR 0
#define ID_DIGIT 1
#define ID_LETTER 2
#define ID_UNDERLINE 3
#define ID_S_AT 4

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
	int i;
	for(i=0;i<ASSIC_NUM;i++)
	{
		if(i>='0'&&i<='9')
		{
			id_array[i]=ID_DIGIT;
		}
		else if(i>='a'&&i<='z')
		{
			id_array[i]=ID_LETTER;
		}
		else if(i>='A'&&i<='Z')
		{
			id_array[i]=ID_LETTER;
		}
		else
		{
			id_array[i]=ID_ERR;
		}
	}
	id_array['@']=ID_S_AT ;
	id_array['_']=ID_UNDERLINE;
}

	
int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
