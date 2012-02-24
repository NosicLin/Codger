#include "lexical.h"

#define input_type_other 0

int operator_input_map_other(char c)
{
	return input_type_other;
}




#define OPERATOR_FINAL_STATE(name) \
	struct state oper_##name=INIT_FINAL_STATE(#name) 


OPERATOR_FINAL_STATE(comma);
OPERATOR_FINAL_STATE(period);
OPERATOR_FINAL_STATE(l_rb);
OPERATOR_FINAL_STATE(r_rb);
OPERATOR_FINAL_STATE(l_sb);
OPERATOR_FINAL_STATE(r_sb);
OPERATOR_FINAL_STATE(reverse);




int operator_input_map_equal(char c)
{
	if(c=='=') return 1;
	else return input_type_other;
}

#define __INIT_OPERATOR_ASSIGN_TRANSLATE(name,target_array,final) \
	struct state oper_##name= \
	{ \
		#name,\
		2,1,0,operator_input_map_equal,\
		target_array, \
		final \
	}

#define INIT_OPERATOR_EQUAL(name) \
	INIT_OPERATOR_ASSIGN_TRANSLATE(name,1,assign_##name)

#define INIT_OPERATOR_ASSIGN_TRANSLATE(first,final,last) \
	OPERATOR_FINAL_STATE(last); \
	static struct state* operater_private_name_state_array_##first[]=\
	{&lex_state_err,&oper_##last}; \
	__INIT_OPERATOR_ASSIGN_TRANSLATE(first,operater_private_name_state_array_##first,final);\


INIT_OPERATOR_ASSIGN_TRANSLATE(not_equal_begin,0,not_equal);

INIT_OPERATOR_EQUAL(bits_and);
INIT_OPERATOR_EQUAL(bits_or);
INIT_OPERATOR_EQUAL(bits_xor);
INIT_OPERATOR_EQUAL(multiply);
INIT_OPERATOR_EQUAL(mod);
INIT_OPERATOR_EQUAL(minus);
INIT_OPERATOR_EQUAL(plus);
INIT_OPERATOR_EQUAL(divide);
INIT_OPERATOR_ASSIGN_TRANSLATE(assign,1,equal);


INIT_OPERATOR_EQUAL(right_shift);
OPERATOR_FINAL_STATE(greater_equal);
int oper_greater_than_input_type(char c)
{
	if(c=='=') return 1;
	else if(c=='>') return 2;
	else return 0;
}
static struct state* oper_greater_than_targets_array[]=
{&lex_state_err,&oper_greater_equal,&oper_right_shift};
struct state oper_greater_than=
{
	"greater_than",
	3,
	2,
	0,
	oper_greater_than_input_type,
	oper_greater_than_targets_array,
	1,
};

INIT_OPERATOR_EQUAL(left_shift);
OPERATOR_FINAL_STATE(less_equal);
int oper_less_than_input_type(char c)
{
	if(c=='=') return 1;
	else if (c=='<') return 2;
	else return 0;
}
static struct state* oper_less_than_input_targets_array[]=
{&lex_state_err,&oper_less_equal,&oper_left_shift};
struct state oper_less_than=
{
	"less_than",
	3,2,0,
	oper_less_than_input_type,
	oper_less_than_input_targets_array,
	1
};


		



/*operator_begin*/

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

char oper_input_type_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,8,0,0,0,13,9,0,4,4,12,15,1,14,2,16,0,0,0,0,0,0,0,0,0,0,0,0,19,17,18,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,7,11,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,3,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

struct state* oper_begin_state_targets_array[]=
{
	&lex_state_err,
	&oper_comma,
	&oper_period,
	&oper_reverse,
	&oper_l_rb,
	&oper_r_rb,
	&oper_l_sb,
	&oper_r_sb,
	&oper_not_equal_begin,
	&oper_bits_and,
	&oper_bits_or,
	&oper_bits_xor,
	&oper_multiply,
	&oper_mod,
	&oper_minus,
	&oper_plus,
	&oper_divide,
	&oper_assign,
	&oper_greater_than,
	&oper_less_than,
};
struct state oper_begin_state=
{
	"oper_begin_state",
	OPER_INPUT_NUM,
	OPER_INPUT_NUM-1,
	oper_input_type_map,
	0,
	oper_begin_state_targets_array,
	0
};












