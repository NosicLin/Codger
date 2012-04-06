#ifndef _CODGER_SYNTAX_SYMBOL_TABLE_H_
#define _CODGER_SYNTAX_SYMBOL_TABLE_H_
#include<object/robject.h>
int symbol_init();
Robject* symbol_get_local(Robject* key);
int symbol_set_local(Robject* key,Robject* value);
int symbol_exit();


#endif /*_CODGER_SYNTAX_SYMBOL_TABLE_H_*/




