#ifndef _CODGER_VM_EXCEPT_H_
#define _CODGER_VM_EXCEPT_H_ 

/* exception */
void GrErr_DiveZeroFormat(const char* s,...);
void GrErr_NegitiveShift(const char* s,...);
void GrErr_BugFromat(const char* s,...);
void GrErr_HashFormat(const char* s,...);
void GrErr_MemFormat(const char* s,...);
void GrErr_KeyFormat(const char* s,...);
void GrErr_TypeFormat(const char* s,...);
void GrErr_IndexFormat(const char* s,...);
void GrErr_OutOfRangeFormat(const char* s,...);

int GrExcept_SetException(const char* name,const char* msg);
int GrExcept_Happened();
void GrExcept_Clr();

#endif /*_CODGER_VM_EXCEPT_H_*/

