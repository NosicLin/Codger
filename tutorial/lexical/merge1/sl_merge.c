#include"sl_states.h"

int input_map_cbegin(char c)
{
	if(c>='0'&&c<='3') return 1;
	else if(c>='4'&&c<='7') return 2;
	else if(c>='8'&&c<'9') return 3;
	else return 0;
}

struct state* cbegin_targets[]= { &lex_state_err,&A1,&C1,&B1};
struct state Cbegin= {"Cbegin",4,3,0,input_map_cbegin,cbegin_targets,0};


int input_map_c1(char c)
{
	if(c>='0'&&c<='3') return 1;
	else if(c>='4'&&c<='7') return 2;
	else if(c>='8'&&c<'9') return 3;
	else if(c=='a') return 4;
	else return 0;
}
struct state* C1_targets[]={&lex_state_err,&A1,&C1,&B1,&C2};
struct state C1={"C1",5,4,0,input_map_c1,C1_targets,0};


int input_map_c2(char c)
{
	if(c=='b') return 1;
	else if(c=='c') return 2;
	else return 0;
}

struct state* C2_targets[]={&lex_state_err,&A3,&B3};
struct state C2={"C2",3,2,0,input_map_c2,C2_targets,0};
