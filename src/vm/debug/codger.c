#include"engine.h"
#include<syntax/parser.h>
#include<syntax/yylex.h>
#include<object/module_object.h>
#include"stack_frame.h"
#include<stdio.h>
#include"op_code.h"
int main(int argc,char** argv)
{


	Scanner* sc=0;
	AstObject* root=0;
	ModuleObject* module=0;
	StackFrame* sf=0;
	BtString* module_name=0;
	int ret=0;
	engine_init();
	if(argc!=2)
	{
		fprintf(stderr,"usage %s <filename>\n",argv[0]);
		exit(-1);
	}
	sc=sc_create(argv[1]);
	if(sc==NULL)
	{
		fprintf(stderr,"Open file %s failed\n",argv[1]);
		exit(-1);
	}
	yl_set_scanner(sc);
	ret=yyparse();
	if(ret!=0)
	{
		fprintf(stderr,"parser <%s> failed\n",argv[1]);
		goto error;
	}
	ast_clear_pending();
	root=parser_get_root();

	module=ast_to_module(root);
	module_name=btstring_create_no_esc("main");

	if(module==NULL||module_name==NULL)
	{
		goto error;
	}
	module->m_name=module_name;
	module_name=NULL;
	sf=sframe_from_module(module);
	if(sf==NULL)
	{
		goto error;
	}
	engine_push(sf);
	sf=0;
	ret=engine_run();
error:
	if(sf) sframe_free(sf);
	if(module) robject_release(M_TO_R(module));
	if(module_name) robject_release(S_TO_R(module_name));
	if(root) ast_tree_free(root);
	if(sc) sc_destory(sc);
	engine_exit();
	return ret;
}


	
