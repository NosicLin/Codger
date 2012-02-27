#include "lexical.h"
#include "token.h"
#include "sl_states.h"

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
char number_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,1,2,2,2,2,2,2,2,3,3,0,0,0,0,0,0,
	0,0,4,0,0,5,0,0,0,0,0,0,6,0,0,7,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
	0,0,4,0,0,5,0,0,0,0,0,0,6,0,0,7,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/*NumberBegin*/
struct state* nu_begin_targets[]=
{
	&lex_state_err,		/*NU_OTHER*/
	&nu_zero,			/*NU_D0*/
	&nu_number,			/*NU_D1_7*/
	&nu_number,			/*NU_D8_9*/
	&lex_state_err,		/*NU_S_B*/
	&lex_state_err,		/*NU_S_E*/
	&lex_state_err,		/*NU_S_L*/
	&lex_state_err,		/*NU_S_O*/
	&lex_state_err,		/*NU_S_X*/
	&ft_frac_begin,		/*NU_POINT*/
};
struct state nu_begin=
{
	"nu_begin",
	TOKEN_UNKOWN,
	NU_INPUT_NUM,
	number_input_map,
	0,
	nu_begin_targets,
	0,
};

/*NumberZero*/
struct state* nu_zero_targets[]=
{
	&lex_state_err,		/*NU_OTHER*/
	&nu_oct,			/*NU_D0*/
	&nu_oct,			/*NU_D1_7*/
	&ft_int_part,		/*NU_D8_9*/
	&ist_bin_begin,		/*NU_S_B*/
	&ft_exp_begin,		/*NU_S_E*/
	&ist_long,			/*NU_S_L*/
	&ist_oct_begin,		/*NU_S_O*/
	&ist_hex_begin,		/*NU_S_X*/
	&ft_frac_begin,		/*NU_POINT*/
};
struct state nu_zero=
{
	"nu_zero(demical)",
	TOKEN_DEC,
	NU_INPUT_NUM,
	number_input_map,
	0,
	nu_zero_targets,
	1,
};

/*NUMBER*/
struct  state* nu_number_targtes[]=
{
	&lex_state_err,		/*NU_OTHER*/  
	&nu_number,			/*NU_D0*/
	&nu_number,			/*NU_D1_7*/
	&nu_number,			/*NU_D8_9*/
	&lex_state_err,		/*NU_S_B*/
	&ft_exp_begin,		/*NU_S_E*/
	&ist_long,			/*NU_S_L*/
	&lex_state_err,		/*NU_S_O*/
	&lex_state_err,		/*NU_S_X*/
	&ft_frac_begin,		/*NU_POINT*/
};
struct state nu_number=
{
	"nu_number(demical)",
	TOKEN_DEC,
	NU_INPUT_NUM,
	number_input_map,
	0,
	nu_number_targtes,
	1,
};
/*NumberOct	*/
struct state* nu_oct_targtes[]=
{
	&lex_state_err,		/*NU_OTHER*/ 
	&nu_oct,			/*NU_D0*/
	&nu_oct,			/*NU_D1_7*/  
	&ft_int_part,		/*NU_D8_9*/
	&lex_state_err,		/*NU_S_B*/
	&ft_exp_begin,		/*NU_S_E*/
	&ist_long,			/*NU_S_L*/
	&lex_state_err,		/*NU_S_O*/
	&lex_state_err,		/*NU_S_X*/
	&ft_frac_begin,		/*NU_POINT*/
};
struct state nu_oct=
{
	"nu_oct(oct)",
	TOKEN_OCT,
	NU_INPUT_NUM,
	number_input_map,
	0,
	nu_oct_targtes,
	1,
};




