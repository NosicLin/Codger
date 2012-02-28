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
	ME_OTHER=0,
	ME_TO_ID,
	ME_D0,
	ME_D1_9,
	ME_QUOTE,
	ME_WS,
	ME_NEWLINE,
	ME_SEMICOLON,

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
	id_array['@']=ME_TO_ID;
	id_array['-']=ME_TO_ID;
	int i;
	for (i='a';i<='z';i++)
	{
		id_array[i]=ME_TO_ID;
	}
	for (i='A';i<='Z';i++)
	{
		id_array[i]=ME_TO_ID;
	}
	id_array['0']=ME_D0;
	for (i='1';i<='9';i++)
	{
		id_array[i]=ME_D1_9;
	}
	id_array['"']=ME_QUOTE;
	id_array[' ']=ME_WS;
	id_array['\t']=ME_WS;
	id_array['\n']=ME_NEWLINE;
	id_array[';']=ME_SEMICOLON;


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

int main()
{
	id_array_create();
	print_array(id_array);
	return 0;
}
