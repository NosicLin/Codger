#include  "lexical.h"

enum ANNO_INPUT_TYPTE
{
	ANNO_OTHER=0,
	ANNO_NEWLINE,
	ANNO_POUND,
	ANNO_INPUT_NUM,
};

char annotate_type_map[ASSIC_NUM]=
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

#define ANNO_STATE_NUM 3
#define ANNO_BEGIN 0
#define ANNO_ANNOTATE 1
#define ANNO_END 2
/* Other | Newlin | Pound */
int annotate_automaton[ANNO_STATE_NUM*ANNO_INPUT_NUM]=
{
	LEX_ERR,LEX_ERR,ANNO_ANNOTATE,
	ANNO_ANNOTATE,ANNO_END,ANNO_ANNOTATE,
	LEX_ERR,LEX_ERR,LEX_ERR,
};


char anno_state[ANNO_STATE_NUM]={0,0,1};


struct automaton am_anno=
{
	ANNO_STATE_NUM,
	ANNO_INPUT_NUM,
	annotate_type_map,
	ANNO_BEGIN,
	annotate_automaton,
	anno_state
};

