#ifndef _REDY_LEXICAL_H_
#define _REDY_LEXICAL_H_


#define ASCII_NUM 256
typedef int (*input_map)(char c);
struct state
{
	char* s_name;			
	int s_token;

	int s_inputs_num;	

	char* s_input_map; 
	input_map s_input_func;  

	struct state** s_targets;
	int s_final;
};

static inline struct state* state_next(struct state* s,int c)
{
	int input_type;
	if(s->s_input_map)			
	{
		input_type=s->s_input_map[c]; 
	}
	else                       
	{
		input_type=s->s_input_func(c); 
	}
	return s->s_targets[input_type];  
}

static inline int state_final(struct state* s)
{
	return s->s_final;
}

static inline char* state_name(struct state* s)
{
	return s->s_name;
}



extern struct state lex_state_err; 
extern struct state* lex_state_err_array[];
extern char input_map_other[];


#endif /*_REDY_LEXICAL_H_*/
	

