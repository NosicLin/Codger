#include "lexical.h"
struct state lex_state_err=
{
	"lex_state_err",
	0,
	0,
	0,
	0,
};
struct state* lex_state_err_array[]={&lex_state_err};
int input_map_other(char c)
{
	return 0;
}
