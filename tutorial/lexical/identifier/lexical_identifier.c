#include  "lexical.h"

#define ID_ERR 0
#define ID_DIGIT 1
#define ID_LETTER 2
#define ID_UNDERLINE 3
#define ID_S_AT 4
char identifier_type_map[ASSIC_NUM]=
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

#define ID_STATE_TYPES 2
#define ID_INPUT_TYPES 5

#define ID_STATE_BEGIN 0
#define ID_STATE_IDENTIFIER 1
#define ID_STATE_ERROR -1

/*Other  |  Digit  |  Letter  |  Underline  | S_AT  */
int identifier_automaton[ID_STATE_TYPES*ID_INPUT_TYPES]=
{
	/*ID_STATE_BEGIN*/  
	ID_STATE_ERROR,ID_STATE_ERROR,ID_STATE_IDENTIFIER,ID_STATE_IDENTIFIER,ID_STATE_IDENTIFIER,
	/* ID_STATE_IDENTIFIER*/
	ID_STATE_ERROR,ID_STATE_IDENTIFIER,ID_STATE_IDENTIFIER,ID_STATE_IDENTIFIER,ID_STATE_ERROR
};

char id_state[ID_STATE_TYPES]={0,1};


struct automaton am_id=
{
	ID_STATE_TYPES,
	ID_INPUT_TYPES,
	identifier_type_map,
	ID_STATE_BEGIN,
	identifier_automaton,
	id_state
};

