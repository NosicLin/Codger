#ifndef _REDY_LEXICAL_H_
#define _REDY_LEXICAL_H_

#define ASCII_NUM 256
typedef int (*input_map)(char); /*输入类型映射函数*/

struct state
{
	char* s_name;				/*状态名称*/

	int s_inputs_num;			/*输入类型的数量*/
	int s_targets_num;          /*后继状态的数量*/

	char* s_input_map;          /*输入类型的映射数组，如果该值为0,则用s_input_func函数指针来判断输入类型*/
	input_map s_input_func;     /*输入类型的函数指针*/

	struct state** s_targets;   /*后继状态数组*/
	int s_final;                /*该状态是否终态*/
};

/*返回状态s在识别字符c后，转移到的状态*/
static inline struct state* state_next(struct state* s,char c)
{
	int input_type;
	if(s->s_input_map)			/*如果该状态有输入类型映射数组，则用该忽略s_input_func*/
	{
		input_type=s->s_input_map[c];   /*得到输入类型*/
	}
	else                        /*如果类型映射数组不存在，则用该函数指针获取输入类型*/
	{
		input_type=s->s_input_func(c);  /*得到输入类型*/
	}
	return s->s_targets[input_type];    /*返回后继状态*/
}

/*判断该状态是否为终态*/
static inline state_final(struct state* s)
{
	return s->s_final;
}

/*返回该状态的名称*/
static inline char* state_name(struct state* s)
{
	return s->s_name;
}

int input_map_other(char);


extern struct state lex_state_err; 
extern struct state* lex_state_err_array[];
#define INIT_FINAL_STATE(name) {name,1,0,0,input_map_other,lex_state_err_array,1}


#endif /*_REDY_LEXICAL_H_*/
	

