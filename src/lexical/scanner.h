#ifndef _REDY_LEXICAL_SCANNER_H_
#define _REDY_LEXICAL_SCANNER_H_
#include"lex_file.h"
#include"token.h"
#include"lexical.h"
#define SCANNER_DEFALUT_LITERIAL_SIZE 128
struct scanner
{
	struct lex_file* s_lf;
	int s_cur_token;
	int s_line;
	char* s_cur_literal;
	int s_literial_size;

};
typedef struct scanner Scanner;


int sc_next_token(struct scanner* sc);
static inline char* sc_token_string(struct scanner* sc)
{
	return sc->s_cur_literal;
}

struct scanner* sc_create(char* filename);
struct scanner* sc_stream_create(FILE* file);
void sc_destory(struct scanner* sc);



#endif 




