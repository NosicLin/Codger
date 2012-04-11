#ifndef _CODGER_VM_STACK_FRAME_H_
#define _CODGER_VM_STACK_FRAME_H_
#include<rtype/bt_string.h>
#include<object/module_object.h>
#include<object/symbol_table.h>
#include<object/func_object.h>
#include<vm/op_code.h>

struct stack_frame
{
	struct stack_frame* sf_link;

	Robject* sf_origin;
	BtString* sf_name; /* stack frame name */

	ModuleObject* sf_modules;

	SymbolTable* sf_scope; /* local variable */


	OpCode* sf_codes;    /* execute byte code */

	/* program counter */
	ssize_t sf_pc;

	/* stack register */
	ssize_t sf_sp;
};

typedef struct stack_frame StackFrame;

StackFrame* sframe_new();
void sframe_free(StackFrame* sf);

void sframe_clear_cache();

StackFrame* sframe_from_func(FuncObject* f);
StackFrame* sframe_from_module(ModuleObject* m);

#endif /*_CODGER_VM_STACK_FRAME_H_*/

