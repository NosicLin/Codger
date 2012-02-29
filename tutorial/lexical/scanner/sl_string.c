#include "lexical.h"
#include "token.h"
#include "sl_states.h"

enum STRING_INPUT_TYPE
{
	ST_OTHER=0,
	ST_NEWLINE,
	ST_BACKSLASH,
	ST_QUOTE,
	ST_INPUT_NUM,
};
char st_input_map[ASCII_NUM]=
{

	0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

/*state st_begin*/
struct state* st_begin_targts[]=
{
	&lex_state_err,		/*ST_OTHER*/
	&lex_state_err,		/*ST_NEWLINE*/
	&lex_state_err,		/*ST_BACKSLASH*/
	&st_string,			/*ST_QUOTE*/    
};

struct state st_begin=
{
	"st_begin",
	TOKEN_UNKOWN,
	ST_INPUT_NUM,
	st_input_map,
	0,
	st_begin_targts,
	0,
};


/*state st_string*/
struct state* st_string_targets[]=
{
	&st_string,			/*ST_OTHER*/
	&lex_state_err,     /*ST_NEWLINE*/
	&st_esc,            /*ST_BACKSLASH*/
	&st_end,            /*ST_QUOTE*/    
};

struct state st_string=
{
	"st_string",
	TOKEN_UNKOWN,
	ST_INPUT_NUM,
	st_input_map,
	0,
	st_string_targets,
	0,
};


/*state st_esc*/
struct state* st_esc_targets[]=
{
	&st_string,		/*ST_OTHER*/
	&st_string,     /*ST_NEWLINE*/
	&st_string,     /*ST_BACKSLASH*/
	&st_string,     /*ST_QUOTE*/    
};
struct state st_esc=
{
	"st_esc",
	TOKEN_UNKOWN,
	ST_INPUT_NUM,
	st_input_map,
	0,
	st_esc_targets,
	0,
};

/*state st_end*/
struct state st_end=
{
	"st_end",
	TOKEN_STRING,
	ST_INPUT_NUM,
	input_map_other,
	0,
	lex_state_err_array,
	1,
};

