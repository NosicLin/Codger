#include"yylex.h"
#include<utility_c/marocs.h>
#include<lexical/token.h>
#include<lexical/lexical.h>
#define TOKEN_BASE 258
static struct scanner* yl_scanner=0;
static int ignore_newline=0;
void yl_set_scanner(struct scanner* sc)
{
	yl_scanner=sc;
}
struct scanner* yl_get_scanner()
{
	return yl_scanner;
}

char* yl_cur_string()
{
	BUG_ON(yl_scanner==0,"NULL Scanner");
	return sc_token_string(yl_scanner);
}
void  yyerror(char* error)
{
	printf("SyntaxError At Line %d\n",yl_scanner->s_line);
}
/* used for parser */
int yylex()
{
	BUG_ON(yl_scanner==0,"NULL Scanner");
	int token=TOKEN_WS;
	while(1)
	{
		token=sc_next_token(yl_scanner);

		/*replace TOKEN_ANNO by TOKEN_NEWLINE*/
		if(token==TOKEN_ANNO)
		{
			token=TOKEN_NEWLINE;
		}
		if(token==TOKEN_ID)
		{
			token=symbol_type(sc_token_string(yl_scanner));
		}

		if(token==TOKEN_NEWLINE)
		{
			if(ignore_newline)
			{
				continue;
			}
		}
		if(token==TOKEN_WS)
		{
			continue;
		}
		break;
	}
	if(token!=EOF)
	{
//		printf("token_name=%s\n",token_name(token));
		token+=TOKEN_BASE;
	}
	return token;
}


void yl_ignore_newline()
{
	ignore_newline+=1;
}
void yl_restore_newline()
{
	ignore_newline-=1;
}



