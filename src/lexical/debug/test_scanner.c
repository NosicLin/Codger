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
	while(1)
	{

		token=sc_next_token(sc);
		if(token==TOKEN_EOF)
		{
			break;
		}
		if(token==TOKEN_ERR)
		{
			goto err;
		}
		printf("%s\n",token_name(token));
	};

	return 0;
err:
	printf("err token at line %d\n",sc->s_line);
	return -1;
}
