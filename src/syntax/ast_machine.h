#ifndef _REDY_SYNTAX_AST_MACHINE_H_
#define _REDY_SYNTAX_AST_MACHINE_H_
#include"ast_object.h"
#include<object/robject.h>
#ifdef AST_MACHINE

enum AST_EXE_INFO
{
	AST_EXE_FALIED=-1,
	AST_EXE_UNKOWN=-2,
	AST_EXE_NO_FUNC=-3,
	AST_EXE_EXCEPTION=-4,
	AST_EXE_SUCCESS=0,
};

/* execute the AstObject */
/* if return negative value, meaning error happend */
int ast_execute(AstObject* ab);

/* init the ast machine system */
int ast_machine_init();
/* exit the ast machine system */
int ast_machine_exit();

/* general register used to save result*/
extern Robject* cup_reg0;

static inline void set_reg0(Robject* r)
{
	robject_addref(r);
	robject_release(cup_reg0);
	cup_reg0=r;
}
static inline Robject* get_reg0()
{
	robject_addref(cup_reg0);
	return cup_reg0;
}


#endif  /*AST_MACHINE*/
#endif /*_REDY_SYNTAX_AST_MACHINE_H_*/

