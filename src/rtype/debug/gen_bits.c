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

	FILE* bash=fopen("bg.sh","w+");
	FILE* python=fopen("bg.py","w+");

	int length=atoi(argv[1]);
	int num=atoi(argv[2]);
	set_exe_name(" bg_expr ");

	srand(time(NULL));
	gen_bitwise(bash,python,length,num);


	fclose(bash);
	fclose(python);
	return 0;
}






