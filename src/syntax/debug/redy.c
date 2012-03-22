#include<stdio.h>
#include"parser.h"
#include"yylex.h"
#include"ast_machine.h"

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
	ast_machine_init();
	yl_set_scanner(sc);
	int ret;
	ret=yyparse();
	AstObject* root=0;
	if(ret!=0)
	{
		printf("parse <%s> failed\n",argv[1]);
		goto error;
	}
	else
	{
		printf("parse <%s> success\n",argv[1]);
		root=parser_get_root();
		ast_execute(root);
	}
	
	sc_destory(sc);
	ast_machine_exit();
	ast_free(root);
	return 0;

error:
	sc_destory(sc);
	ast_machine_exit();
	return -1;
}




