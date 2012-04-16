#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum MERGE_INPUT_TYPE
{
	ME_OTHER=0,
	ME_TO_ID,
	ME_D0,
	ME_D1_9,
	ME_QUOTE,
	ME_WS,
	ME_NEWLINE,
	ME_SEMICOLON,
	ME_ANNO,

	ME_DOLLAR,
	ME_COMMA,
	ME_PERIOD,
	ME_REVERSE,
	ME_L_RB,
	ME_R_RB,
	ME_L_SB,
	ME_R_SB,
	ME_EXCLAMATION,
	ME_AMPERSAND,
	ME_BAR,
	ME_CARET,
	ME_STAR,
	ME_PERCENT,
	ME_MINUS,
	ME_PLUS,
	ME_DIVIDE,
	ME_EQUAL,
	ME_GREATER,
	ME_LESS,
	ME_INPUT_NUM
};

char merge_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	5,17,4,8,9,22,18,0,13,14,21,24,10,23,11,25,2,3,3,3,3,3,3,3,3,3,0,7,28,26,27,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,15,0,16,20,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,19,0,12,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};

struct state* me_begin_targets[]=
{
	&lex_state_err,		/*ME_OTHER*/
	&id_identifier,		/*ME_TO_ID*/
	&nu_zero,			/*ME_D0*/
	&nu_number,			/*ME_D1_9*/
	&st_string,			/*ME_QUOTE*/
	&ws_ws,				/*ME_WS*/
	&sb_newline,		/*ME_NEWLINE*/
	&sb_semicolon,		/*ME_SEMICOLON*/
	&an_annotate,		/*ME ANNO*/

	&sp_dollar,			/*ME_DOLLAR*/
	&op_comma,			/*ME_COMMA*/
	&me_period,			/*ME_PERIOD*/
	&op_reverse,		/*ME_REVERSE*/
	&op_l_rb,			/*ME_L_RB*/
	&op_r_rb,			/*ME_R_RB*/
	&op_l_sb,			/*ME_L_SB*/
	&op_r_sb,			/*ME_R_SB*/
	&op_not_equal_begin,/*ME_EXCLAMATION*/
	&op_bits_and,		/*ME_AMPERSAND*/
	&op_bits_or,		/*ME_BAR*/
	&op_bits_xor,		/*ME_CARET*/
	&op_multiply,		/*ME_STAR*/
	&op_mod,			/*ME_PERCENT*/
	&op_minus,			/*ME_MINUS*/
	&op_plus,			/*ME_PLUS*/
	&op_divide,			/*ME_DIVIDE*/
	&op_assign,			/*ME_EQUAL*/
	&op_greater_than,	/*ME_GREATER*/
	&op_less_than,		/*ME_LESS*/

};

struct state me_begin=
{
	"me_begin",
	TOKEN_UNKOWN,
	ME_INPUT_NUM,
	merge_input_map,
	0,
	me_begin_targets,
	0,
};


/*state megerdivide*/
struct state* me_period_targtes[]=
{
	&lex_state_err,
	&ft_fraction,
};

char me_period_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

struct state me_period=
{
	"me_period",
	TOKEN_PERIOD,
	2,
	me_period_input_map,
	0,
	me_period_targtes,
	1,
};

struct state sp_dollar=
{
	"sp_dollar",
	TOKEN_DOLLAR,
	1,
	input_map_other,
	0,
	lex_state_err_array,
	1,
};






