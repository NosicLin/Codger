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

	FILE* bash=fopen("bash.dat","w+");
	FILE* python=fopen("py.dat","w+");

	int num=atoi(argv[2]);
	int length=atoi(argv[1]);

	set_exe_name(" bg_expr ");

	srand(time(NULL));

	int i=0;
	for(;i<num;i++)
	{

		gen_value(buf_l,length);
		gen_value(buf_r,length);

		bash_write(bash," div ");
		python_write(python," / ");
	}


	fclose(bash);
	fclose(python);
	return 0;
}






