#include"ast_machine.h"
#include<stdio.h>
#include<object/null_object.h>
#include"symbol_table.h"
#ifdef AST_MACHINE 
Robject* cup_reg0=0;
int ast_machine_init()
{
	robject_addref(NullObject);
	cup_reg0=NullObject;
	symbol_init();
	return 0;
}
int ast_machine_exit()
{
	robject_release(cup_reg0);
	cup_reg0=0;
	symbol_exit();
	return 0;
}

int ast_execute(AstObject* ab)
{
//	printf("execute AstObject(%s)\n",ab->a_name);
	if(ab->a_type)
	{
		if(ab->a_type->n_execute)
		{
			return ab->a_type->n_execute(ab);
		}
	}
	return AST_EXE_NO_FUNC;
}

int ast_set_value(AstObject* ab,Robject* value)
{
	if(ab->a_type)
	{
		if(ab->a_type->n_set_value)
		{
			return ab->a_type->n_set_value(ab,value);
		}
	}
	return AST_EXE_NO_FUNC;
}

#endif /*AST_MACHINE*/

