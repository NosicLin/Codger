#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum FLOAT_INPUT_TYPE
{
	F_OTHER=0,
	F_DIGIT,
	F_POINT,
	F_SIGN,
	F_S_E,
	F_INPUT_NUM
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
	int i;
	for(i='0';i<='9';i++)
	{
		id_array[i]=F_DIGIT;
	}
	id_array['E']=F_S_E;
	id_array['e']=F_S_E;

	id_array['+']=F_SIGN;
	id_array['-']=F_SIGN;

	id_array['.']=F_POINT;

}

	
int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
