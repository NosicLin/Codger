#ifndef _CODGER_OBJECT_FUNC_OBJECT_H_
#define _CODGER_OBJECT_FUNC_OBJECT_H_

#include"robject.h"
#include<rtype/bt_array.h>
#include"hash_table.h"
#include<rtype/bt_string.h>
#include"module_object.h"
#include<vm/op_code.h>


#define FUNC_FLAGS_DEFALUT_ARGS 0x1<<0
#define FUNC_FLAGS_MULTIY_ARGS 0x1<<1

#define FLAGS_SET(f,flags) (f->f_flags|=flags)
#define FLAGS_GET(f,flags) (f->f_flags&flags)
#define FLAGS_CLEAR(f,flags) (f->f_flags&=~flags) 

struct func_object
{
	INHERIT_ROBJECT;
	unsigned long f_flags;

	ssize_t f_args_nu;
	ssize_t f_args_min;  

	struct bt_string* f_name;
	struct bt_array* f_args_name;
	struct module_object* f_module;
	struct op_code* f_codes;
};

typedef struct func_object FuncObject;


ROBJECT_TYPE_CAST(FUNC,TYPE_FUNC,FuncObject);

#endif /*_CODGER_OBJECT_FUNC_OBJECT_H_*/

