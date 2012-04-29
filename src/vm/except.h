#ifndef _CODGER_VM_EXCEPT_H_
#define _CODGER_VM_EXCEPT_H_ 

/* exception */
void GrErr_DiveZeroFormat(const char* s,...);
void GrErr_NegitiveShift(const char* s,...);
void GrMem_ErrFormat(const char* s,...);

#endif /*_CODGER_VM_EXCEPT_H_*/

