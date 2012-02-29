#include"scanner.h"
#include"sl_states.h"
#include"lexical.h"
#include<string.h>

static void sc_set_cur_literial(struct scanner* sc,char* buf,int length)
{
	if(sc->s_literial_size<length+1)
	{
		char* new_space=(char*)malloc(length+1);
		free(sc->s_cur_literal);
		sc->s_cur_literal=new_space;
	}
	memcpy(sc->s_cur_literal,buf,length);
	sc->s_cur_literal[length]='\0';
}

int sc_next_token(struct scanner* sc)
{
	struct lex_file* lf=sc->s_lf;

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

	sc_set_cur_literial(sc,lf->l_buf+lf->l_begin,lf->l_mark-lf->l_begin);
	lf_reset_to_mark(lf);

	return sc->s_cur_token;
}



static void sc_init(struct scanner* sc,struct lex_file* lf)
{
	sc->s_lf=lf;
	sc->s_cur_token=TOKEN_UNKOWN;
	sc->s_line=1;
	sc->s_cur_literal=(char*)malloc(SCANNER_DEFALUT_LITERIAL_SIZE);
	sc->s_literial_size=SCANNER_DEFALUT_LITERIAL_SIZE;
}


struct scanner* sc_create(char* filename)
{
	struct lex_file* lf=lf_create(filename);
	if(lf==NULL)
	{
		return NULL;
	}
	struct scanner* sc=(struct scanner*)malloc(sizeof(*sc));
	sc_init(sc,lf);
	return sc;

}
struct scanner* sc_stream_create(FILE* file)
{
	struct lex_file* lf=lf_stream_create(file);
	if(lf==NULL)
	{
		return NULL;
	}
	struct scanner* sc=(struct scanner*)malloc(sizeof(*sc));
	sc_init(sc,lf);
	return sc;
}
void sc_destory(struct scanner* sc)
{
	lf_destory(sc->s_lf);
	free(sc->s_cur_literal);
	free(sc);

}

