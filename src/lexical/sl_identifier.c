#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum ID_INPUT_TYPES
{
	ID_OTHER=0,
	ID_DIGIT,
	ID_LETTER,
	ID_UNDERLINE,
	ID_S_AT,
	ID_INPUT_NUM,
};

static char id_input_map[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,3,
	0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
/*state id_begin*/
struct state* id_begin_targets[]=
{
	&lex_state_err,		/*ID_OTHER*/
	&lex_state_err,		/*ID_DIGIT*/
	&id_identifier,		/*ID_LETTER*/
	&id_identifier,		/*ID_UNDERLINE*/
	&id_identifier,		/*ID_S_AT*/     
};

struct state id_begin=
{
	"id_begin",
	TOKEN_UNKOWN,
	ID_INPUT_NUM,
	id_input_map,
	0,
	id_begin_targets,
	0,
};


/*state id_identifier*/
struct state* id_identifier_targets[]=
{
	&lex_state_err,		/*ID_OTHER*/
	&id_identifier,     /*ID_DIGIT*/
	&id_identifier,     /*ID_LETTER*/
	&id_identifier,     /*ID_UNDERLINE*/
	&lex_state_err,     /*ID_S_AT*/     
};

struct state id_identifier=
{
	"id_identifier",
	TOKEN_ID,
	ID_INPUT_NUM,
	id_input_map,
	0,id_identifier_targets,
	0,
};
