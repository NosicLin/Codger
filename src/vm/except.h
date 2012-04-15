#ifndef _CODGER_VM_EXCEPT_H_
#define _CODGER_VM_EXCEPT_H_ 
int vm_except_happened();
void vm_clear_except();
void vm_set_except(int flags);
int vm_except_type();

enum EXCEPT_TYPE 
{
	E_UNKOWN=0,
	E_DIV_ZERO,
	E_VALUE_ERR,
	E_TYPE_ERR,
	E_OVER_FLOW,
	E_INDEX_ERROR,
	E_KEY_ERR,
	E_NAME_ERR,
	E_SYNTAX_ERR,
	E_ITER_STOP,
	E_ITER_ERR,
	E_ARGS,
};



/* exception */
void except_divzero_err_format(const char* s,...);
void except_type_err_format(const char* s,...);
void except_value_err_format(const char* s,...);
void except_overflow_err_format(const char* s,...);
void except_index_err_format(const char* s,...);
void except_key_err_format(const char* s,...);
void except_unkown_err_format(const char* s,...);
void except_name_err_format(const char* s,...);
void except_syntax_err_format(const char* s,...);
void except_args_err_format(const char* s,...);
void except_iter_err_format(const char* s,...);
void except_iter_stop();

#endif /*_CODGER_VM_EXCEPT_H_*/

