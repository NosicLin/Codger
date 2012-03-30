#ifndef _REDY_VM_EXCEPT_H_
#define _REDY_VM_EXCEPT_H_ 
int vm_except_happened();
void vm_clear_except();
void vm_set_except(int flags);


/* exception */
void except_divzero_err_format(const char* s,...);
void except_type_err_format(const char* s,...);
void except_value_err_format(const char* s,...);
void except_overflow_err_format(const char* s,...);
void except_index_err_format(const char* s,...);
void except_key_err_format(const char* s,...);

#endif /*_REDY_VM_EXCEPT_H_*/

