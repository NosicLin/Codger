#include"sl_states.h"

int input_map_abegin(char c)
{
	if(c>='0'&&c<='7') return 1;
	else return 0;
}
struct state* Abegin_targets[]= {&lex_state_err,&A1};
struct state Abegin= { "Abegin",2,1,0, input_map_abegin, Abegin_targets, 0, };

int input_map_a1(char c)
{
	if(c=='a')return 1;
	if(c>='0'&&c<='7') return 2;
	else return 0;
}
struct state* A1_targets[]= {&lex_state_err,&A2,&A1};
struct state A1= { "A1",2,1,0, input_map_a1, A1_targets, 0, };



int input_map_a2(char c)
{
	if(c=='b')return 1;
	else return 0;
}
struct state* A2_targets[]= {&lex_state_err,&A3};
struct state A2= { "A2",2,1,0, input_map_a2, A2_targets, 0, };

int input_map_a3(char c)
{
	if(c=='f')return 1;
	else return 0;
}
struct state* A3_targets[]= {&lex_state_err,&A4};
struct state A3= { "A3",2,1,0, input_map_a3, A3_targets, 0, };

int input_map_a4(char c)
{
	return 0;
}
struct state* A4_targets[]= {&lex_state_err};
struct state A4= { "[0-7]+abf",2,1,0, input_map_a4, A4_targets, 1, };

