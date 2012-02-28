#include"scanner.h"
#include"sl_states.h"
#include"lexical.h"
#include<utility_c/marocs.h>

int sc_next_token(struct scanner* sc)
{
	struct lex_file* lf=sc->s_lf;
	lf_reset_to_mark(lf);

	char cur;
	char next=lf_next_char(lf);
	struct state* cur_state=&me_begin;
	struct state* next_state;
	struct state* finnal_state=NULL;
	while(1)
	{
		cur=next;


		if(cur==EOF)
		{
			sc->s_cur_token=TOKEN_EOF;
			break;
		}
		if(cur=='\n')
		{
			sc->s_line++;
		}
		next_state=state_next(cur_state,cur);
		if(next_state==&lex_state_err)
		{
			if(finnal_state==NULL)
			{
				sc->s_cur_token=TOKEN_ERR;
			}
			else
			{
				sc->s_cur_token=finnal_state->s_token;
			}
			break;
		}


		if(state_final(next_state))
		{
			finnal_state=next_state;
			lf_mark(lf);
		}
		next=lf_next_char(lf);
		cur_state=next_state;
	}
	return sc->s_cur_token;
}



struct scanner* sc_create(char* filename)
{
	struct lex_file* lf=lf_create(filename);
	if(lf==NULL)
	{
		WARN("Open file[%s] Failed",filename);
		return NULL;
	}
	struct scanner* sc=(struct scanner*)malloc(sizeof(*sc));
	sc->s_lf=lf;
	sc->s_cur_token=TOKEN_UNKOWN;
	sc->s_line=1;
	return sc;
}
struct scanner* sc_stream_create(FILE* file)
{
	struct lex_file* lf=lf_stream_create(file);
	if(lf==NULL)
	{
		WARN("Create Scanner Failed");
		return NULL;
	}
	struct scanner* sc=(struct scanner*)malloc(sizeof(*sc));
	sc->s_lf=lf;
	sc->s_cur_token=TOKEN_UNKOWN;
	sc->s_line=1;
	return sc;
}
void sc_destory(struct scanner* sc)
{
	lf_destory(sc->s_lf);
	free(sc);
}

