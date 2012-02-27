#include "lexical.h"
#include "token.h"
#include "sl_states.h"
enum FLOAT_INPUT_TYPES
{
	F_OTHER=0,
	F_DIGIT,
	F_POINT,
	F_SIGN,
	F_S_E,
	F_INPUT_NUM,
};

char float_type_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,3,0,3,2,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

/*ft_beign*/
struct state* ft_begin_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_int_part,		/*F_DIGIT*/
	&ft_frac_begin,		/*F_POINT*/
	&lex_state_err,		/*F_SIGN*/
	&lex_state_err,		/*F_S_E*/
};
struct state ft_begin=
{
	"ft_begin",
	TOKEN_UNKOWN,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_begin_targets,
	0,
};

/*ft_frac_begin*/
struct state* ft_frac_begin_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_fraction,		/*F_DIGIT*/
	&lex_state_err,		/*F_POINT*/
	&lex_state_err,		/*F_SIGN*/
	&lex_state_err,		/*F_S_E*/
};
struct state ft_frac_begin=
{
	"ft_fraction",
	TOKEN_UNKOWN,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_frac_begin_targets,
	0,
};

/*ft_int_part*/
struct state* ft_int_part_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_int_part,		/*F_DIGIT*/
	&ft_frac_begin,		/*F_POINT*/
	&lex_state_err,		/*F_SIGN*/
	&ft_exp_begin,		/*F_S_E*/
};
struct state ft_int_part=
{
	"ft_int_part",
	TOKEN_UNKOWN,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_int_part_targets,
	0,
};

/*ft_fraction*/
struct state* ft_fraction_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_fraction,		/*F_DIGIT*/
	&lex_state_err,		/*F_POINT*/
	&lex_state_err,		/*F_SIGN*/
	&ft_exp_begin,		/*F_S_E*/
};
struct state ft_fraction=
{
	"float",
	TOKEN_FLOAT,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_fraction_targets,
	1,
};

/*ft_exp_begin*/
struct state* ft_exp_begin_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_exponent,		/*F_DIGIT*/
	&lex_state_err,		/*F_POINT*/
	&ft_exp_sign,		/*F_SIGN*/
	&lex_state_err,		/*F_S_E*/
};
struct state ft_exp_begin=
{
	"ft_exp_beign",
	TOKEN_UNKOWN,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_exp_begin_targets,
	0,
};

/*ft_exponent*/
struct state* ft_exponent_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_exponent,		/*F_DIGIT*/
	&lex_state_err,		/*F_POINT*/
	&lex_state_err,		/*F_SIGN*/
	&lex_state_err,		/*F_S_E*/
};
struct state ft_exponent=
{
	"exp_float",
	TOKEN_EXP_FLOAT,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_exponent_targets,
	1,
};

/*ft_exp_sign*/
struct state* ft_exp_sign_targets[]=
{
	&lex_state_err,		/*F_OTHER*/
	&ft_exponent,		/*F_DIGIT*/
	&lex_state_err,		/*F_POINT*/
	&lex_state_err,		/*F_SIGN*/
	&lex_state_err,		/*F_S_E*/
};
struct state ft_exp_sign=
{
	"ft_exp_sign",
	TOKEN_UNKOWN,
	F_INPUT_NUM,
	float_type_map,
	0,
	ft_exp_begin_targets,
	0,
};






