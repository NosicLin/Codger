#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum ANNO_INPUT_TYPTE
{
	ANNO_OTHER=0,
	ANNO_NEWLINE,
	ANNO_POUND,
	ANNO_INPUT_NUM,
};

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
	memset(id_array,0,sizeof(id_array));
	id_array['\n']=ANNO_NEWLINE;
	id_array['#']=ANNO_POUND;


}

	
int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
