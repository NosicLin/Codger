#include"ast_machine.h"
#include<object/null_object.h>
#ifdef AST_MACHINE 
Robject* cup_reg0=0;
int ast_machine_init()
{
	robject_addref(NullObject);
	cup_reg0=NullObject;
	return 1;
}
int ast_machine_exit()
{
	robject_release(cup_reg0);
	cup_reg0=0;
	return 1;
}

int ast_execute(AstObject* ab)
{
	if(ab->a_ops)
	{
		if(ab->a_ops->ao_execute)
		{
			return ab->a_ops->ao_execute(ab);
		}
	}
	return AST_EXE_NO_FUNC;
}


#endif /*AST_MACHINE*/

