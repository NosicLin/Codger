#include"symbol_table.h"
#include<assert.h>
#include<object/hash_table.h>

static HashTable* s_table=NULL;
int symbol_init()
{
		s_table=hash_new();
		if(s_table==NULL)
			return -1;
		return 0;

}

Robject* symbol_get_local(Robject* key)
{
	assert(s_table);
	Robject* value=hash_get_item(s_table,key);
	return value;
}
int symbol_set_local(Robject* key,Robject* value)
{
	assert(s_table);
	int ret=hash_set_item(s_table,key,value);
	return ret;
}

int symbol_exit()
{
	hash_free(s_table);
	s_table=NULL;
	return 0;
}

