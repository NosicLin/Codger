#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum WS_INPUT_TYPE
{
	WS_OTHER=0,
	WS_ITEM,
	WS_INPUT_NUM,
};

char ws_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};


struct state* ws_begin_targets[]=
{
	&lex_state_err,
	&ws_ws,
};
struct state  ws_begin=
{
	"ws_begin",
	TOKEN_UNKOWN,
	WS_INPUT_NUM,
	ws_input_map,
	0,
	ws_begin_targets,
	0,
};

struct state* ws_ws_targets[]=
{
	&lex_state_err,
	&ws_ws,
};

struct state ws_ws=
{
	"ws_ws",
	TOKEN_WS,
	WS_INPUT_NUM,
	ws_input_map,
	0,
	ws_ws_targets,
	1,
};
