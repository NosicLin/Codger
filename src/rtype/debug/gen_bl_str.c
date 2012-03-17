#include<stdio.h>
#include<string.h>
#include<time.h>
#include"gen_lib.h"
#include"stdlib.h"

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("usage %s <length> <num> \n",argv[0]);
		exit(-1);
	}

	FILE* bash=fopen("bash.dat","w+");
	FILE* python=fopen("py.dat","w+");

	int length=atoi(argv[1]);
	int num=atoi(argv[2]);
	set_exe_name(" bg_expr ");

	srand(time(NULL));
	gen_bl_from_str(bash,python,length,num);


	fclose(bash);
	fclose(python);
	return 0;
}



