#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum INT_INPUT_TYPES
{
	INT_OTHER=0,
	INT_D0,
	INT_D1,
	INT_D2_7,
	INT_S_A,
	INT_S_B,
	INT_S_C_F,
	INT_S_O,
	INT_S_X,
	INT_S_L,
	INT_INPUT_NUM
};
char int_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,3,3,3,3,4,4,0,0,0,0,0,0,
	0,5,6,7,7,7,7,0,0,0,0,0,10,0,0,8,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,
	0,5,6,7,7,7,7,0,0,0,0,0,10,0,0,8,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};
/*state long*/
struct state ist_long=
{
	"long",
	TOKEN_LONG,
	1,
	int_input_map,
	0,
	lex_state_err_array,
	1,
};


/*state bin*/
struct state* ist_bin_targets[]=
{
	&lex_state_err,
	&ist_bin,
	&ist_bin,
	&lex_state_err,
	&lex_state_err,

	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,

	&ist_long,
};

struct state ist_bin=
{
	"ist_bin",
	TOKEN_BIN,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_bin_targets,
	1,
};


/*state hex*/
struct state* ist_hex_targets[]=
{
	&lex_state_err,
	&ist_hex,
	&ist_hex,
	&ist_hex,
	&ist_hex,

	&ist_hex,
	&ist_hex,
	&ist_hex,
	&lex_state_err,
	&lex_state_err,
	&ist_long,
};
struct state ist_hex=
{
	"ist_hex",
	TOKEN_HEX,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_hex_targets,
	1,
};

/*state oct*/
struct state* ist_oct_targets[]=
{
	&lex_state_err,
	&ist_oct,
	&ist_oct,
	&ist_oct,
	&lex_state_err,

	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,

	&ist_long,
};
struct state ist_oct=
{
	"ist_oct",
	TOKEN_OCT,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_oct_targets,
	1,
};

/*state state oct_begin*/
struct state* ist_oct_begin_targets[]=
{
	&lex_state_err,
	&ist_oct,
	&ist_oct,
	&ist_oct,
	&lex_state_err,

	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	
	&lex_state_err,
};
struct state ist_oct_begin=
{
	"ist_oct_begin",
	TOKEN_UNKOWN,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_oct_begin_targets,
	0,
};

/*state  bin_begin*/
struct state* ist_bin_begin_targets[]=
{
	&lex_state_err,
	&ist_bin,
	&ist_bin,
	&lex_state_err,
	&lex_state_err,

	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,

	&lex_state_err,
};
struct state ist_bin_begin=
{
	"ist_bin_begin",
	TOKEN_UNKOWN,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_bin_begin_targets,
	0,
};

/*state hex_begin*/
struct state* ist_hex_begin_targets[]=
{
	&lex_state_err,
	&ist_hex,
	&ist_hex,
	&ist_hex,
	&ist_hex,

	&ist_hex,
	&ist_hex,
	&ist_hex,
	&lex_state_err,
	&lex_state_err,

	&lex_state_err,
};
struct state ist_hex_begin=
{
	"ist_hex_begin",
	TOKEN_UNKOWN,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_hex_begin_targets,
	0,
};

/*state dec*/
struct state* ist_dec_targets[]=
{
	&lex_state_err,
	&ist_dec,
	&ist_dec,
	&ist_dec,
	&ist_dec,

	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,

	&ist_long,
};
struct state ist_dec=
{
	"ist_dec",
	TOKEN_DEC,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_dec_targets,
	1,
};

/*state IntegerPrefix*/
struct state* ist_int_prefix_targets[]=
{
	&lex_state_err,
	&ist_oct,
	&ist_oct,
	&ist_oct,
	&lex_state_err,

	&lex_state_err,
	&ist_bin_begin,
	&lex_state_err,
	&ist_oct_begin,
	&ist_hex_begin,

	&ist_long,
};

struct state ist_int_prefix=
{
	"ist_int_prefix",
	TOKEN_DEC,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_int_prefix_targets,
	1,
};

/*state integer_begin*/
struct state* ist_begin_targets[]=
{
	&lex_state_err,
	&ist_int_prefix,
	&ist_dec,
	&ist_dec,
	&ist_dec,

	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,
	&lex_state_err,

	&lex_state_err,
};
struct state ist_begin=
{
	"ist_begin",
	TOKEN_UNKOWN,
	INT_INPUT_NUM,
	int_input_map,
	0,
	ist_begin_targets,
	0,
};


