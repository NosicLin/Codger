#include<stdio.h>
#include"parser.h"
#include"yylex.h"

int main(int argc ,char** argv)
{
	if(argc!=2)
	{
		printf("usage %s <filename>\n",argv[0]);
		exit(-1);
	}

	Scanner* sc=sc_create(argv[1]);
	if(sc==NULL)
	{
		printf("open file %s failed\n",argv[1]);
		exit(-1);
	}
	yl_set_scanner(sc);
	int ret;
	ret=yyparse();
	if(ret!=0)
	{
		printf("parse <%s> failed\n",argv[1]);
	}
	else
	{
		printf("parse <%s> success\n",argv[1]);
	}

	sc_destory(sc);
	return 0;
}




