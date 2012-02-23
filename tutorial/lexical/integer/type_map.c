#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_OTHER 0
#define INT_D0 1
#define INT_D1 2
#define INT_D2_7 3
#define INT_D8_9 4
#define INT_S_a 5
#define INT_S_b 6
#define INT_S_c_f 7
#define INT_S_o 8
#define INT_S_x 9
#define INT_S_l 10


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

	id_array['a']=INT_S_a;
	id_array['A']=INT_S_a;

	id_array['b']=INT_S_b;
	id_array['B']=INT_S_b;
	
	char i;
	for(i='c';i<='f';i++)
	{
		id_array[i]=INT_S_c_f;
	}
	for(i='C';i<='F';i++)
	{
		id_array[i]=INT_S_c_f;
	}

	id_array['0']=INT_D0;
	id_array['1']=INT_D1;
	int j;
	for(j='2';j<='7';j++)
	{
		id_array[j]=INT_D2_7;
	}
	id_array['8']=INT_D8_9;
	id_array['9']=INT_D8_9;
	
	id_array['o']=INT_S_o;
	id_array['O']=INT_S_o;

	id_array['x']=INT_S_x;
	id_array['X']=INT_S_x;


	id_array['l']=INT_S_l;
	id_array['L']=INT_S_l;


}

	
int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
