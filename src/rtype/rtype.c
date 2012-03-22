#include"rtype.h"
#include<utility_c/marocs.h>
#include<vm/except.h>

void rt_raise_type_error(char* msg)
{
	//TODO("TypeError");
	printf("TypeError:%s\n",msg);
	vm_set_except(1);
}

void rt_raise_div_zero(char* msg)
{
	//TODO("DivZeroError");
	printf("DivZeroError:%s\n",msg);
	vm_set_except(1);
}
void rt_raise_overflow(char* msg)
{
	//TODO("OverflowError");
	printf("OverflowError:%s\n",msg);
	vm_set_except(1);
}
void rt_raise_value_error(char* msg )
{
	//TODO("VauleError");
	printf("VauleError:%s\n",msg);
	vm_set_except(1);
}

void rt_raise_index_error(char* msg )
{
	//TODO("IndexError");
	printf("IndexError:%s\n",msg);
	vm_set_except(1);
}
