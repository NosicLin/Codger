#ifndef _REYD_LEIXCIAL_LEX_FILE_H_
#define _REYD_LEIXCIAL_LEX_FILE_H_
#include<stdio.h>
#include<stdlib.h>

struct lex_file
{
	FILE* l_file;
	char* l_buf;
	int l_buf_cap;
	int l_buf_size;
	int l_begin;
	int l_mark;
	int l_read_pos;
};
#define LEX_FILE_DEFAULT_SIZE 1024

/*location lexical.c*/
struct lex_file* lf_create(char* file_name);
struct lex_file* lf_stream_create(FILE* stream);
void lf_destory(struct lex_file* lf);

int lf_load_data(struct lex_file* lf);

static inline char lf_next_char(struct lex_file* lf)
{
	if(lf->l_read_pos>=lf->l_buf_size)
	{
		if(lf_load_data(lf)==0)
		{
			return EOF;
		}
	}
	return lf->l_buf[lf->l_read_pos++];
}
static inline void lf_mark(struct lex_file* lf)
{
	lf->l_mark=lf->l_read_pos;
}
static inline void lf_back_to_mark(struct lex_file* lf)
{
	lf->l_read_pos=lf->l_mark;
}
static inline void lf_reset_to_mark(struct lex_file* lf)
{
	lf->l_begin=lf->l_mark;
	lf->l_read_pos=lf->l_mark;
}

#endif 
