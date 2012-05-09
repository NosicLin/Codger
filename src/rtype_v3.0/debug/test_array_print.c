#include"bt_array.h"
int main()
{
	BtArray* a0=btarray_create();
	BtArray* a5=btarray_create_size(20);
	btarray_print(a0,NULL,PRINT_FLAGS_NEWLINE);
	btarray_print(a5,NULL,PRINT_FLAGS_NEWLINE);
	btarray_set_item(a5,3,A_TO_R(a5));
	btarray_set_item(a5,4,A_TO_R(a0));
	btarray_print(a5,NULL,PRINT_FLAGS_NEWLINE);
	robject_release(A_TO_R(a0));
	robject_release(A_TO_R(a5));
	return 0;

}
	

