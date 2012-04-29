#ifndef _CODGER_VM_EXCEPT_H_
#define _CODGER_VM_EXCEPT_H_ 

/* exception */
static inline void GrErr_DiveZeroFormat(const char* s,...){}
static inline void GrErr_NegitiveShift(const char* s,...){}
static inline void GrMem_ErrFormat(const char* s,...){}

#endif /*_CODGER_VM_EXCEPT_H_*/

