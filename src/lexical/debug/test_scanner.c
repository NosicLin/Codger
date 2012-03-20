#include"scanner.h"
#include<stdio.h>
#include"token.h"
#include"sl_states.h"
#include"lexical.h"

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("usage %s [filename]\n",argv[0]);
		exit(0);
	}
	struct scanner* sc=sc_create(argv[1]);

	int token;
	int i=0;
	while(1)
	{
		i++;
		token=sc_next_token(sc);
		if(token==EOF)
		{
			break;
		}
		if(token==TOKEN_ERR)
		{
			goto err;
		}
		if(token==TOKEN_ID)
		{
			if(symbol_type(sc_token_string(sc))==TOKEN_ID)
			{
				printf("{variable,%s}  ",sc_token_string(sc));
			}
			else
			{
				printf("{keyword,%s}  ",sc_token_string(sc));
			}
			continue;
		}
		if(token==TOKEN_ANNO)
		{
			continue;

		}
		if(token==TOKEN_WS)
		{
			continue;
		}
		if(token==TOKEN_NEWLINE)
		{
			printf("{newline}\n");
			continue;
		}
		printf("{%s,%s}  ",token_name(token),sc_token_string(sc));
	};

	sc_destory(sc);
	printf("\n");
	return 0;
err:
	sc_destory(sc);
	printf("err token at line %d\n",sc->s_line);
	return -1;
	
}
