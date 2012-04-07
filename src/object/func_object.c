#include"func_object.h"

#ifdef AST_MACHINE
#include<syntax/ast_machine.h>
static int func_ast_call(Robject* r)
{
	FuncObject* f=R_TO_FUNC(r);
	int ret=ast_execute(f->root);
	if(ret>0) return AST_EXE_SUCCESS;
	else return ret;
}
#endif





