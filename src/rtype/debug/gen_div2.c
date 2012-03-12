#include<stdio.h>
#include<big_integer.h>
#include<string.h>
#include<time.h>
#include"gen_lib.h"
int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("usage %s <length> <num> \n",argv[0]);
		exit(-1);
	}

	FILE* bash=fopen("bg.dat","w+");
	FILE* python=fopen("bg.py","w+");

	int num=atoi(argv[2]);
	int length=atoi(argv[1]);

	set_exe_name("");

	srand(time(NULL));

	int i=0;
	for(;i<num;i++)
	{

		gen_value(buf_l,length);
		gen_value(buf_r,length);

		bash_write(bash," div ");
		bash_write(bash," mod ");
		python_write(python," / ");
		python_write(python," % ");
	}
	fwrite("\nquit\n",1,strlen("\nquit"),bash);


	fclose(bash);
	fclose(python);
	return 0;
}






