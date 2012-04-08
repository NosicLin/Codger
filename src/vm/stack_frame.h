#ifndef _CODGER_VM_STACK_FRAME_H_
#define _CODGER_VM_STACK_FRAME_H_
#include<rtype/bt_string.h>
#include<object/module_object.h>
#include<object/hash_table.h>
#include<object/func_object.h>
#include<vm/op_code.h>

struct stack_frame
{
	struct stack_frame* sf_link;

	BtString* sf_name;
	Robject* sf_origin;
	ModuleObject* sf_modules;

	HashTable* sf_symbols;

	OpCode* sf_codes;
	ssize_t sf_pc;
};

typedef struct stack_frame StackFrame;

StackFrame* sframe_new();
void sframe_free(StackFrame* sf);

void sframe_clear_cache();

StackFrame* sframe_from_func(FuncObject* f);
StackFrame* sframe_from_module(ModuleObject* m);

#endif /*_CODGER_VM_STACK_FRAME_H_*/

