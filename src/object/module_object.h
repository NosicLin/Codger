#ifndef _CODGER_OBJECT_MODULE_OBJECT_H_
#define _CODGER_OBJECT_MODULE_OBJECT_H_
#include"robject.h"
#include"hash_table.h"
#include<vm/op_code.h>
#include<assert.h>
struct bt_array;
struct bt_string;


struct module_object
{
	INHERIT_ROBJECT;
	struct module_object* m_belong;
	struct bt_array* m_consts;
	struct bt_array* m_symbols;

	struct bt_string* m_name;
	struct op_code* m_codes;

	struct symbol_table* m_attrs;
};

typedef struct module_object ModuleObject;
ROBJECT_TYPE_CAST(M,TYPE_MODULE,ModuleObject);

struct module_object* module_new();
static inline void module_set_opcode(ModuleObject* m,struct op_code* c)
{
	assert(m->m_codes==NULL);
	m->m_codes=c;
}


unsigned long module_map_const(ModuleObject* m,Robject* value);
unsigned long module_map_symbol(ModuleObject* m,Robject* symbol);
#endif  /*_CODGER_OBJECT_MODULE_OBJECT_H_*/

