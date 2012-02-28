#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum SB_INPUT_TYPE
{
	SB_OTHER=0,
	SB_SEMICOLON,
	SB_NEWLINE,
	SB_INPUT_NUM,
};
char sb_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};

struct state* sb_begin_targets[]=
{
	&lex_state_err,
	&sb_semicolon,
	&sb_newline
};
struct state sb_begin=
{
	"sb_begin",
	TOKEN_UNKOWN,
	SB_INPUT_NUM,
	sb_input_map,
	0,
	sb_begin_targets,
	0,
};

struct state sb_semicolon=
{
	"sb_semicolon",
	TOKEN_SEMI,
	SB_INPUT_NUM,
	input_map_other,
	0,
	lex_state_err_array,
	1,
};


struct state sb_newline=
{
	"sb_newline",
	TOKEN_NEWLINE,
	SB_INPUT_NUM,
	input_map_other,
	0,
	lex_state_err_array,
	1,
};


