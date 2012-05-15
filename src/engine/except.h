#ifndef _CODGER_VM_EXCEPT_H_
#define _CODGER_VM_EXCEPT_H_ 

/* err exception */
void GrErr_DiveZeroFormat(const char* s,...);
void GrErr_NegitiveShift(const char* s,...);
void GrErr_BugFromat(const char* s,...);
void GrErr_HashFormat(const char* s,...);
void GrErr_MemFormat(const char* s,...);
void GrErr_KeyFormat(const char* s,...);
void GrErr_NameFormat(const char* s,...);
void GrErr_TypeFormat(const char* s,...);
void GrErr_IndexFormat(const char* s,...);
void GrErr_OutOfRangeFormat(const char* s,...);
void GrErr_ArgsFormat(const char* s,...);
void GrErr_PermFormat(const char* s,...);

/* normal exception */

void GrExcept_IterStop();


int GrExcept_SetException(int ,const char* name,const char* msg);
int GrExcept_Happened();
void GrExcept_Clr();
int GrExcept_Type();

enum GR_EXCEPT_TYPE
{
	Gr_Err_Div_Zero,
	Gr_Err_Bug,
	Gr_Err_Index,
	Gr_Err_Name,
	Gr_Err_Type,
	Gr_Err_Mem,
	Gr_Err_Out_Of_Range,
	Gr_Err_Args,
	Gr_Except_Iter_Stop,
};

int GrModule_ExceptInit();



#endif /*_CODGER_VM_EXCEPT_H_*/

