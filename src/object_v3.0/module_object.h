#ifndef _CODGER_OBJECT_MODULE_OBJECT_H_
#define _CODGER_OBJECT_MODULE_OBJECT_H_
#include"robject.h"
#include"hash_table.h"
#include<vm/op_code.h>
#include<assert.h>
#include<stdio.h>
struct bt_array;
struct bt_string;
struct func_object;

struct module_object
{
	INHERIT_ROBJECT;
	struct module_object* m_belong;
	struct bt_array* m_consts;
	struct bt_array* m_symbols;

	struct bt_string* m_name;
	struct op_code* m_codes;

	struct bt_array* m_funcs;

	struct symbol_table* m_attrs;
};

typedef struct module_object ModuleObject;
ROBJECT_TYPE_CAST(M,TYPE_MODULE,ModuleObject);

struct module_object* module_new();
void module_free(ModuleObject* m);

static inline void module_set_opcode(ModuleObject* m,struct op_code* c)
{
	assert(m->m_codes==NULL);
	m->m_codes=c;
}


int32_t module_map_const(ModuleObject* m,Robject* value);
int32_t module_map_symbol(ModuleObject* m,Robject* symbol);

int module_add_func(ModuleObject* m,struct func_object* f);
void module_write(ModuleObject* m,FILE* f);


#endif  /*_CODGER_OBJECT_MODULE_OBJECT_H_*/

