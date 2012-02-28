#ifndef _REDY_LEXICAL_SCANNER_H_
#define _REDY_LEXICAL_SCANNER_H_
#include"lex_file.h"
#include"token.h"
#include"lexical.h"
struct scanner
{
	struct lex_file* s_lf;
	int s_cur_token;
	int s_line;

};

int sc_next_token(struct scanner* sc);
char* sc_token_string(struct scanner* sc);
struct scanner* sc_create(char* filename);
struct scanner* sc_stream_create(FILE* file);
void sc_destory(struct scanner* sc);


#endif 




