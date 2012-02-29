#include"token.h"
#include"lexical.h"
#include"sl_states.h"

#define INIT_FINAL_STATE(name,token) {#name,token,1,input_map_other,0,lex_state_err_array,1}

#define OP_FINAL_STATE(name,token) \
	struct state name=INIT_FINAL_STATE(name,token)  


OP_FINAL_STATE(op_comma,TOKEN_COMMA);
OP_FINAL_STATE(op_period,TOKEN_PERIOD);
OP_FINAL_STATE(op_l_rb,TOKEN_L_RB);
OP_FINAL_STATE(op_r_rb,TOKEN_R_RB);
OP_FINAL_STATE(op_l_sb,TOKEN_L_SB);
OP_FINAL_STATE(op_r_sb,TOKEN_R_SB);
OP_FINAL_STATE(op_reverse,TOKEN_REVERSE);



static char op_input_map_equal[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};


#define __INIT_OPERATOR_ASSIGN_TRANSLATE(name,token,target_array,final) \
	struct state name= \
{ \
#name, \
	token,2,op_input_map_equal,0,target_array,final,\
}\

#define INIT_OPERATOR_ASSIGN_TRANSLATE(first,token1,final,last,token2) \
	static struct state* operator_private_name_state_array_##first[]=\
	{&lex_state_err,&last}; \
	__INIT_OPERATOR_ASSIGN_TRANSLATE(first,token1,operator_private_name_state_array_##first,final); \
	OP_FINAL_STATE(last,token2) 



INIT_OPERATOR_ASSIGN_TRANSLATE(op_not_equal_begin,TOKEN_UNKOWN,0,op_not_equal,TOKEN_NOT_EQUAL);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_bits_and,TOKEN_BITS_AND,1,op_assign_bits_and,TOKEN_A_BITS_AND);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_bits_or,TOKEN_BITS_OR,1,op_assign_bits_or,TOKEN_A_BITS_OR);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_bits_xor,TOKEN_BITS_XOR,1,op_assign_bits_xor,TOKEN_A_BITS_XOR);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_multiply,TOKEN_MUL,1,op_assign_multiply,TOKEN_A_MUL);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_mod,TOKEN_MOD,1,op_assign_mod,TOKEN_A_MOD);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_minus,TOKEN_MINUS,1,op_assign_minus,TOKEN_A_MINUS);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_plus,TOKEN_PLUS,1,op_assign_plus,TOKEN_A_PLUS);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_divide,TOKEN_DIVIDE,1,op_assign_divide,TOKEN_A_DIVIDE);
INIT_OPERATOR_ASSIGN_TRANSLATE(op_assign,TOKEN_ASSIGN,1,op_equal,TOKEN_EQUAL);



INIT_OPERATOR_ASSIGN_TRANSLATE(op_right_shift,TOKEN_RS,1,op_assign_right_shift,TOKEN_A_RS);
OP_FINAL_STATE(op_greater_equal,TOKEN_GE);
static struct state* op_greater_than_targets[]=
{
	&lex_state_err,
	&op_greater_equal,
	&op_right_shift,
};

static char op_input_map_greater_than[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
struct state op_greater_than=
{
	"op_greater_than",
	TOKEN_GT,
	3,
	op_input_map_greater_than,
	0,
	op_greater_than_targets,
	1,
};

INIT_OPERATOR_ASSIGN_TRANSLATE(op_left_shift,TOKEN_LS,1,op_assign_left_shift,TOKEN_A_LS);
OP_FINAL_STATE(op_less_equal,TOKEN_LE);

static struct state* op_less_than_targets[]=
{
	&lex_state_err,
	&op_less_equal,
	&op_left_shift,
};
static char op_input_map_less_than[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};
struct  state op_less_than=
{
	"op_less_than",
	TOKEN_LT,
	3,
	op_input_map_less_than,
	0,
	op_less_than_targets,
	1,
};

/*op_begin*/
enum OP_INPUT_TYPE
{
	OP_OTHER=0,
	OP_COMMA,
	OP_PERIOD,
	OP_REVERSE,
	OP_L_RB,
	OP_R_RB,
	OP_L_SB,
	OP_R_SB,
	OP_EXCLAMATION,
	OP_AMPERSAND,
	OP_BAR,
	OP_CARET,
	OP_STAR,
	OP_PERCENT,
	OP_MINUS,
	OP_PLUS,
	OP_DIVIDE,
	OP_EQUAL,
	OP_GREATER,
	OP_LESS,
	OP_INPUT_NUM
};

char op_input_map_begin[ASCII_NUM]=
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

struct state* op_begin_targets[]=
{
	&lex_state_err,
	&op_comma,
	&op_period,
	&op_reverse,
	&op_l_rb,
	&op_r_rb,
	&op_l_sb,
	&op_r_sb,
	&op_not_equal_begin,
	&op_bits_and,
	&op_bits_or,
	&op_bits_xor,
	&op_multiply,
	&op_mod,
	&op_minus,
	&op_plus,
	&op_divide,
	&op_assign,
	&op_greater_than,
	&op_less_than,
};
struct state op_begin=
{
	"oper_begin",
	TOKEN_UNKOWN,
	OP_INPUT_NUM,
	op_input_map_begin,
	0,
	op_begin_targets,
	0
};


