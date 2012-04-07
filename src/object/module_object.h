#ifndef _CODGER_OBJECT_MODULE_OBJECT_H_
#define _CODGER_OBJECT_MODULE_OBJECT_H_
#include"robject.h"
#include"hash_table.h"

struct module_object
{
	INHERIT_ROBJECT;
	struct module_object* f_belong;
};
typedef struct module_object ModuleObject;

#endif  /*_CODGER_OBJECT_MODULE_OBJECT_H_*/

