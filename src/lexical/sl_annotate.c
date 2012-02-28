#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum ANNO_INPUT_TYPTE
{
	ANNO_OTHER=0,
	ANNO_NEWLINE,
	ANNO_POUND,
	ANNO_INPUT_NUM,
};

char annotate_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};

struct state* an_begin_targets[]=
{
	&lex_state_err,
	&lex_state_err,
	&an_annotate,
};
struct state an_begin=
{
	"an_begin",
	TOKEN_UNKOWN,
	ANNO_INPUT_NUM,
	annotate_input_map,
	0,
	an_begin_targets,
	0,
};

struct state* an_annotate_targets[]=
{
	&an_annotate,
	&an_end,
	&an_annotate,
};
struct state an_annotate=
{
	"an_annotate",
	TOKEN_UNKOWN,
	ANNO_INPUT_NUM,
	annotate_input_map,
	0,
	an_annotate_targets,
	0,
};


struct state an_end=
{
	"an_end",
	TOKEN_ANNO,
	ANNO_INPUT_NUM,
	input_map_other,
	0,
	lex_state_err_array,
	1,
};


