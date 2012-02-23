#include "lexical.h"

#define INT_OTHER 0
#define INT_D0 1
#define INT_D1 2
#define INT_D2_7 3
#define INT_D8_9 4
#define INT_S_a 5
#define INT_S_b 6
#define INT_S_c_f 7
#define INT_S_o 8
#define INT_S_x 9
#define INT_S_l 10
char int_type_map[ASSIC_NUM]=
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


enum INT_STATE_TYPE
{
	INT_BEGIN=0,
	INT_PREFIX,
	INT_BIN_BEGIN,
	INT_BIN ,
	INT_OCT_BEGIN,
	INT_OCT ,
	INT_DECIMAL ,
	INT_HEX_BEGIN,
	INT_HEX ,
	INT_LONG ,
	INT_STATE_NUM,
};

#define INT_STATE_TYPES  INT_STATE_NUM
#define INT_INPUT_TYPES 11   

#define INT_ERR LEX_ERR

/*Other | D0 | D1 |                | D2_7 | D8_9 | S_a |              |S_b | S_c_f | S_o |       |S_x | S_l */
int int_automaton[INT_STATE_TYPES*INT_INPUT_TYPES]=
{
	/*INT_BEGIN*/
	INT_ERR,INT_PREFIX,INT_DECIMAL,   INT_DECIMAL,INT_DECIMAL,INT_ERR,   INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_ERR,
	/*INT_PREFIX*/
	INT_ERR,INT_OCT,INT_OCT,          INT_OCT,INT_ERR,INT_ERR,           INT_BIN_BEGIN,INT_ERR,INT_OCT_BEGIN,   INT_HEX_BEGIN,INT_LONG,

	/*INT_BIN_BEGIN*/
	INT_ERR,INT_BIN,INT_BIN,          INT_ERR,INT_ERR,INT_ERR,           INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_ERR,
	/*INT_BIN*/
	INT_ERR,INT_BIN,INT_BIN,          INT_ERR,INT_ERR,INT_ERR,           INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_LONG,

	/*INT_OCT_BEGIN*/
	INT_ERR,INT_OCT,INT_OCT,          INT_OCT,INT_ERR,INT_ERR,           INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_ERR,
	/*INT_OCT*/
	INT_ERR,INT_OCT,INT_OCT,          INT_OCT,INT_ERR,INT_ERR,           INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_LONG,

	/*INT_DECIMAL*/
	INT_ERR,INT_DECIMAL,INT_DECIMAL,  INT_DECIMAL,INT_DECIMAL,INT_ERR,   INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_LONG,

	/*INT_HEX_BEGIN*/
	INT_ERR,INT_HEX,INT_HEX,          INT_HEX,INT_HEX,INT_HEX,           INT_HEX,INT_HEX,INT_ERR,   INT_ERR,INT_ERR,
	/*INT_HEX*/
	INT_ERR,INT_HEX,INT_HEX,          INT_HEX,INT_HEX,INT_HEX,           INT_HEX,INT_HEX,INT_ERR,   INT_ERR,INT_LONG,

	/*INT_LONG*/
	INT_ERR,INT_ERR,INT_ERR,          INT_ERR,INT_ERR,INT_ERR,           INT_ERR,INT_ERR,INT_ERR,   INT_ERR,INT_ERR
};
struct state int_state[INT_STATE_TYPES]=
{
	{"Begin",INT_BEGIN,0},{"Decimal",INT_PREFIX,1},{"BinaryBegin",INT_BIN_BEGIN,0},{"Binary",INT_BIN,1},
	{"OctBegin",INT_OCT_BEGIN,0},{"Oct",INT_OCT,1},{"Decimal",INT_DECIMAL,1},{"HexBegin",INT_HEX_BEGIN,0},{"Hex",INT_HEX,1},
	{"Long",INT_LONG,1}
};


struct automaton am_string=
{
	INT_STATE_TYPES,
	INT_INPUT_TYPES,
	int_type_map,
	INT_BEGIN,
	int_automaton,
	int_state
};

