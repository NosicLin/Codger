#ifndef _CODGER_OBJECT_FUNC_OBJECT_H_
#define _CODGER_OBJECT_FUNC_OBJECT_H_

#include"robject.h"
#include<rtype/bt_array.h>
#include"hash_table.h"
#include<rtype/bt_string.h>
#include"module_object.h"
#include<vm/op_code.h>
#include<utility_c/marocs.h>


#define FUNC_FLAGS_DEFALUT_ARGS (0x1<<0)
#define FUNC_FLAGS_MANY_ARGS (0x1<<1)


struct func_object
{
	INHERIT_ROBJECT;
	unsigned long f_flags;

	int f_args_nu;
	int f_args_min;  

	struct bt_string* f_name;
	struct bt_array* f_args_name;
	struct bt_array* f_defargs;
	struct module_object* f_module;
	struct op_code* f_codes;
};

typedef struct func_object FuncObject;

FuncObject* func_new();
static inline void func_set_name(FuncObject* f,BtString* name)
{
	robject_addref(S_TO_R(name));
	if(f->f_name)
	{	
		BUG("FuncObject Already Have A Name");
		robject_release(S_TO_R(f->f_name));
	}
	f->f_name=name;
}
static inline BtString* func_get_name(FuncObject* f)
{
	if(f->f_name) robject_addref(S_TO_R(f->f_name));
	BUG_ON(f->f_name==NULL,"FuncObject Don't Have A Name");
	return f->f_name;
}
static inline void func_set_flags(FuncObject* f,unsigned long flags)
{
	f->f_flags |= flags;
}
static inline unsigned long func_get_flags(FuncObject* f,
									unsigned long flags)
{
	return  f->f_flags& flags;
}
static inline void func_clear_flags(FuncObject* f,unsigned long flags)
{
	f->f_flags&=(~flags);
}
static inline void func_set_arg_nu(FuncObject* f,int arg_nu,int arg_min)
{
	f->f_args_nu=arg_nu;
	f->f_args_min=arg_min;
}

static inline void func_set_args_name(FuncObject* f,BtArray* args_name)
{
	robject_addref(A_TO_R(args_name));
	BUG_ON(f->f_args_name!=NULL,"FuncObject Already Have ArgsName");
	f->f_args_name=args_name;
}
static inline void func_set_module(FuncObject* f,ModuleObject* m)
{
	robject_addref(M_TO_R(m));
	BUG_ON(f->f_module!=NULL,"FuncObject Already Have Module");
	f->f_module=m;
}
static inline void func_set_opcode(FuncObject* f,OpCode* op)
{
	BUG_ON(f->f_codes!=NULL,"FuncObject Already Have Opcode");
	f->f_codes=op;
}

static inline void func_set_defargs(FuncObject* f,BtArray* defargs)
{
	robject_addref(A_TO_R(defargs));
	BUG_ON(f->f_defargs!=NULL,"FuncObject Already Have defargs");
	f->f_defargs=defargs;
}
void func_free(FuncObject* f);

ROBJECT_TYPE_CAST(FUNC,TYPE_FUNC,FuncObject);

#endif /*_CODGER_OBJECT_FUNC_OBJECT_H_*/

