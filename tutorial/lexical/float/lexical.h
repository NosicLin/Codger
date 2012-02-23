#ifndef REDY_LEXICAL_H_
#define REDY_LEXICAL_H_

#define ASSIC_NUM 256
#define LEX_ERR -1
struct state 
{
	char* name;   /*状态名称*/
	int type;     /*状态类型*/
	int final;		/*是否为终态*/
};
struct automaton
{
	int states_num;  /*状态的数量*/
	int inputs_num;  /*输入类型的数量*/
	char* type_map;  /*字符映射到输入类型的数组*/
	int begin_state;	/*开始状态*/
	int* states_matrix;   /*状态矩阵*/
	struct state* states_info;    /*状态信息*/
};
extern struct automaton am_id;
extern struct automaton am_string;
extern struct automaton am_float;
#endif 


