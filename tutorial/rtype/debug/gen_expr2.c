#include<stdio.h>
#include<big_integer.h>
#include<string.h>
#include<time.h>
#include"gen_lib.h"

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("usage %s <num> <length> \n",argv[0]);
		exit(-1);
	}

	FILE* bash=fopen("bg.dat","w+");
	FILE* python=fopen("bg.py","w+");

	int num=atoi(argv[1]);
	int length=atoi(argv[2]);

	set_exe_name("");

	srand(time(NULL));
	gen_expr(bash,python,length,num);
	fwrite("\nquit\n",1,strlen("\nquit"),bash);

	fclose(bash);
	fclose(python);
	return 0;
}





