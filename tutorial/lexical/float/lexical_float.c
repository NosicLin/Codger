#include "lexical.h"

enum FLOAT_INPUT_TYPE
{
	F_OTHER=0,
	F_DIGIT,
	F_POINT,
	F_SIGN,
	F_S_E,
	F_INPUT_NUM
};

char float_type_map[ASSIC_NUM]=
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

enum FLOAT_STATE_TYPE
{
	F_F_BEGIN=0,
	F_FRAC_BEGIN,
	F_INTPART,
	F_FRACTION,
	F_EXP_BEGIN,
	F_EXP_SYMBOL,
	F_EXPONENT,
	F_STATE_NUM,
};

#define F_STATE_TYPES  F_STATE_NUM
#define F_INPUT_TYPES  F_INPUT_NUM  

#define F_ERR LEX_ERR

/* Other | Digit | Point | Sign | S_e */
int float_automaton[F_STATE_TYPES*F_INPUT_TYPES]=
{
	/* 0 F_F_BEGIN*/
	F_ERR,F_INTPART,    F_FRAC_BEGIN,F_ERR,    F_ERR,
	/*F_FRAC_BEGIN*/
	F_ERR,F_FRACTION,   F_ERR,F_ERR,           F_ERR,
	/* 2 F_INTPART*/
	F_ERR,F_INTPART,    F_FRAC_BEGIN,F_ERR,    F_EXP_BEGIN,
	/*F_FRACTION*/
	F_ERR,F_FRACTION,   F_ERR,F_ERR,           F_EXP_BEGIN,
	/* 4 F_EXP_BEGIN*/
	F_ERR,F_EXPONENT,   F_ERR,F_EXP_SYMBOL,    F_ERR,
	/*F_EXP_SYMBOL*/
	F_ERR,F_EXPONENT,   F_ERR,F_ERR,           F_ERR,
	/* 6 F_EXPONENT*/
	F_ERR,F_EXPONENT,   F_ERR,F_ERR,           F_ERR,
};

struct state float_state[F_STATE_TYPES]=
{
	{"F_F_BEGIN",F_F_BEGIN,0},
	{"F_FRAC_BEGIN",F_FRAC_BEGIN,0},
	{"F_INTPART",F_INTPART,0},
	{"float",F_FRACTION,1},
	{"F_EXP_BEGIN",F_EXP_BEGIN,0},
	{"F_EXP_SYMBOL",F_EXP_SYMBOL,0},
	{"exp_float",F_EXPONENT,1}
};


struct automaton am_float=
{
	F_STATE_TYPES,
	F_INPUT_TYPES,
	float_type_map,
	F_F_BEGIN,
	float_automaton,
	float_state
};

