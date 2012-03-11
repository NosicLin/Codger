#include"gen_lib.h"
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
char buf_l[100000];
char buf_r[100000];
char exe_name[1000];

void set_exe_name(char* name)
{
	memcpy(exe_name,name,strlen(name)+1);
}


void bash_write(FILE* f,char* op)
{
	fwrite(exe_name,1,strlen(exe_name),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite(op,1,strlen(op),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("\n",1,1,f);
}
void python_write(FILE* f,char* op)
{
	fwrite("a=",1,strlen("a="),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite("l",1,strlen("l"),f);
	fwrite(op,1,strlen(op),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("l",1,strlen("l"),f);
	fwrite("\n",1,sizeof("\n")-1,f);
	fwrite("print a\n",1,strlen("print a\n"),f);

}
void gen_value(char* buf,int length)
{
	int real_len=rand()%length+1;
	int i=0;
	if(rand()%2)
	{
		buf[i]='-';
		i++;
	}
	int value=rand()%10;
	while(!value)
	{
		value=rand()%10;
	}
	buf[i]='0'+value;
	i++;
	for(;i<real_len;i++)
	{
		int value=rand()%10;
		buf[i]='0'+value;
	}
	buf[i]=0;
}

void gen_shift(FILE* bash,FILE* python,int length,int shift)
{
	int i=0;
	for(i=0;i<shift;i++)
	{
		gen_value(buf_l,length);
		sprintf(buf_r,"%d",i);
		bash_write(bash," lshift ");
		bash_write(bash," rshift ");
		python_write(python," << ");
		python_write(python," >> ");
	}
}

void gen_expr(FILE* bash,FILE* python,int length,int num)
{
	int i=0;
	for(;i<num;i++)
	{

		gen_value(buf_l,length);
		gen_value(buf_r,length);

		bash_write(bash," add ");
		bash_write(bash," sub ");
		bash_write(bash," mul ");
		bash_write(bash," div ");
		python_write(python," + ");
		python_write(python," - ");
		python_write(python," * ");
		python_write(python," / ");
	}
}

void gen_bitwise(FILE* bash,FILE* python,int length,int num)
{
	int i=0;
	for(;i<num;i++)
	{

		gen_value(buf_l,length);
		gen_value(buf_r,length);

		bash_write(bash," or ");
		bash_write(bash," and ");
		bash_write(bash," xor ");
		python_write(python," | ");
		python_write(python," & ");
		python_write(python," ^ ");

	}

}
