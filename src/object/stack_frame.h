#ifndef _CODGER_OBJECT_STACK_FRAME_H_
#define _CODGER_OBJECT_STACK_FRAME_H_

#include"robject.h"
#include"hash_object.h"
#include<utility_c/list_head.h>
struct stack_frame
{
	/* @s_stacks: used simulate  computor stack */
	struct list_head s_stacks;

	/* @s_table: store local symbol */
	HashTable* s_table;

	ModuleObject* s_module;
};
typedef struct stack_frame StackFrame;

#endif /*_CODGER_OBJECT_STACK_FRAME_H_*/

