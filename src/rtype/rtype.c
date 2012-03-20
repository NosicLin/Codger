#include"rtype.h"
#include<utility_c/marocs.h>
#include<vm/except.h>

void rt_raise_type_error(char* msg)
{
	TODO("TypeError");
	vm_set_except(1);
}

void rt_raise_div_zero(char* msg)
{
	TODO("DivZeroError");
	vm_set_except(1);
}
void rt_raise_overflow(char* msg)
{
	TODO("OverflowError");
	vm_set_except(1);
}
void rt_raise_value_error(char* msg )
{
	TODO("VauleError");
	vm_set_except(1);
}

void rt_raise_index_error(char* msg )
{
	TODO("IndexError");
	vm_set_except(1);
}
