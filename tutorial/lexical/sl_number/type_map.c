#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum NUMBER_INPUT_TYPES
{
	NU_OTHER=0,
	NU_D0,
	NU_D1_7,
	NU_D8_9,
	NU_S_B,
	NU_S_E,
	NU_S_L,
	NU_S_O,
	NU_S_X,
	NU_POINT,
	NU_INPUT_NUM,
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
	id_array['0']=NU_D0;
	char c;
	for(c='1';c<='7';c++)
	{
		id_array[c]=NU_D1_7;
	}
	id_array['8']=NU_D8_9;
	id_array['9']=NU_D8_9;

	id_array['b']=NU_S_B;
	id_array['B']=NU_S_B;

	id_array['e']=NU_S_E;
	id_array['E']=NU_S_E;

	id_array['l']=NU_S_L;
	id_array['L']=NU_S_L;

	id_array['o']=NU_S_O;
	id_array['O']=NU_S_O;

	id_array['x']=NU_S_X;
	id_array['X']=NU_S_X;

	id_array['.']=NU_POINT;
}






	
int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
