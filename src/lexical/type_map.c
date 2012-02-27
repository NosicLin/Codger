#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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


enum OPER_INPUT_TYPE
{
	OPER_OTHER=0,
	OPER_COMMA,
	OPER_PERIOD,
	OPER_REVERSE,
	OPER_L_RB,
	OPER_R_RB,
	OPER_L_SB,
	OPER_R_SB,
	OPER_EXCLAMATION,
	OPER_AMPERSAND,
	OPER_BAR,
	OPER_CARET,
	OPER_STAR,
	OPER_PERCENT,
	OPER_MINUS,
	OPER_PLUS,
	OPER_DIVIDE,
	OPER_EQUAL,
	OPER_GREATER,
	OPER_LESS,
	OPER_INPUT_NUM
};

void id_array_create()
{
	memset(id_array,0,sizeof(id_array));
	id_array[',']=OPER_COMMA;
	id_array['.']=OPER_PERIOD;
	id_array['~']=OPER_REVERSE;
	id_array['(']=OPER_L_RB;
	id_array[')']=OPER_L_RB;
	id_array['[']=OPER_L_SB;
	id_array[']']=OPER_R_SB;
	id_array['!']=OPER_EXCLAMATION;
	id_array['&']=OPER_AMPERSAND;
	id_array['|']=OPER_BAR;
	id_array['^']=OPER_CARET;
	id_array['*']=OPER_STAR;
	id_array['%']=OPER_PERCENT;
	id_array['-']=OPER_MINUS;
	id_array['+']=OPER_PLUS;
	id_array['/']=OPER_DIVIDE;
	id_array['=']=OPER_EQUAL;
	id_array['>']=OPER_GREATER;
	id_array['<']=OPER_LESS;

}


void id_array_op_input_equal()
{
	memset(id_array,0,sizeof(id_array));
	id_array['=']=1;
}
void id_array_op_input_greater_than()
{
	memset(id_array,0,sizeof(id_array));
	id_array['=']=1;
	id_array['>']=2;
}

void id_array_op_input_less_than()
{
	memset(id_array,0,sizeof(id_array));
	id_array['=']=1;
	id_array['<']=2;
}
	
void input_map_other()
{
	memset(id_array,0,sizeof(id_array));
}
	
int main()
{
	id_array_op_input_less_than();
	print_array(id_array);
	return 0;
}
