#ifndef _CODGER_VM_EXCEPT_H_
#define _CODGER_VM_EXCEPT_H_ 

/* exception */
static inline void GrErr_DiveZeroFormat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_NegitiveShift(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_BugFromat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_HashFormat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_MemFormat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_KeyFormat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_TypeFormat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_IndexFormat(const char* s,...)
{
	printf("%s",s);
}
static inline void GrErr_OutOfRangeFormat(const char* s,...)
{
	printf("%s",s);
}

static inline int GrExcept_Happened(){return 0;}


#endif /*_CODGER_VM_EXCEPT_H_*/

