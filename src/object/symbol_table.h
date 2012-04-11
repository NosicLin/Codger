#ifndef _CODGER_OBJECT_SYMBOL_TABLE_H_
#define _CODGER_OBJECT_SYMBOL_TABLE_H_
#include"hash_table.h"
#include<rtype/bt_string.h>
#include<vm/except.h>

struct  symbol_table 
{
	struct hash_table sy_base;
};
typedef struct symbol_table SymbolTable;

static inline SymbolTable* sy_table_new()
{
	return (SymbolTable*)hash_new();
}

static inline Robject* sy_table_lookup(SymbolTable* sy,Robject* key)
{
	Robject*  value=hash_get_item(&sy->sy_base,key);
	if(value==NULL)
	{
		if(!vm_except_happened())
		{
			except_name_err_format("name '%s' is not define",R_TO_S(key)->s_value);
		}

	}
	return value;
}

static inline int sy_table_map(SymbolTable* sy,Robject* key,Robject* value)
{
	return  hash_set_item(&sy->sy_base,key,value);
}
static inline void sy_table_free(SymbolTable* sy)
{
	hash_free(&sy->sy_base);
}
ROBJECT_TYPE_CAST(SY,TYPE_HASH,SymbolTable);

#endif /*_CODGER_OBJECT_SYMBOL_TABLE_H_*/



