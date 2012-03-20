#include"except.h"
static int except_flags=0;

/* exception interface*/
int vm_except_happened()
{
	return except_flags;
}
void vm_clear_except()
{
	except_flags=0;
}
void vm_set_except(int flags)
{
	except_flags=flags;
}
