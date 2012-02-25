#include"sl_states.h"

int input_map_bbegin(char c)
{
	if(c>='4'&&c<='9')return 1;
	else return 0;
}

struct state* Bbegin_targets[]= {&lex_state_err,&B1};
struct state Bbegin= { "Bbegin",2,1,0, input_map_bbegin, Bbegin_targets, 0, };


int input_map_b1(char c)
{
	if(c=='a')return 1;
	if(c>='4'&&c<='9') return 2;
	else return 0;
}
struct state* B1_targets[]= {&lex_state_err,&B2,&B1};
struct state B1= { "B1",2,1,0, input_map_b1, B1_targets, 0, };

int input_map_b2(char c)
{
	if(c=='c')return 1;
	else return 0;
}
struct state* B2_targets[]= {&lex_state_err,&B3};
struct state B2= { "B2",2,1,0, input_map_b2, B2_targets, 0, };

int input_map_b3(char c)
{
	if(c=='d')return 1;
	else return 0;
}
struct state* B3_targets[]= {&lex_state_err,&B4};
struct state B3= { "B3",2,1,0, input_map_b3, B3_targets, 0, };

int input_map_b4(char c)
{
	return 0;
}
struct state* B4_targets[]= {&lex_state_err};
struct state B4= { "[4-9]+acd",2,1,0, input_map_b4, B4_targets, 1, };

