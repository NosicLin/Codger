#ifndef _REDY_LEXICAL_H_
#define _REDY_LEXICAL_H_

struct keyword
{
	char* k_name;
	int k_token;
};
#define KEYWORD_NUM 28
extern struct keyword key_words[];

/*lexical.c*/
int symbol_type(char*);



#endif /*_REDY_LEXICAL_H_*/
	

