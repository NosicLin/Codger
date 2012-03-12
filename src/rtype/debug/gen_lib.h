#ifndef GEN_LIB_H_
#define GEN_LIB_H_
#include<stdio.h>
void bash_write(FILE* f,char* op);
void python_write(FILE* f,char* op);
void gen_value(char* buf,int length);
void set_exe_name(char* name);
extern char buf_l[];
extern char buf_r[];
void gen_shift(FILE* bash,FILE* python,int length,int num);
void gen_expr(FILE* bash,FILE* python,int length,int num);
void gen_bitwise(FILE* bash,FILE* python,int length,int num);

#endif
