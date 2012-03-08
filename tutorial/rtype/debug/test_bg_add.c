#include<stdio.h>
#include<big_integer.h>
#include<string.h>

int main(int argc,char** argv)
{
	if(argc<4)
	{
		printf("usage:%s <l1> op <l2>\n",argv[0]);
		exit(-1);
	}
	// printf("%s %s %s %s\n",argv[0],argv[1],argv[2],argv[3]);

	BGInteger* bg1=bg_create_from_decstr(argv[1]);
	BGInteger* bg2=bg_create_from_decstr(argv[3]);



	BGInteger* r=NULL;

	if(strcmp(argv[2],"add")==0)
	{
		r=bg_plus(bg1,bg2);
	}
	else if(strcmp(argv[2],"dec")==0)
	{
		r=bg_minus(bg1,bg2);
	}
	else if(strcmp(argv[2],"mul")==0)
	{
		r=bg_mul(bg1,bg2);

	}
	else
	{
		printf(" %s is invalid,please use right operator\n",argv[2]);
		bg_free(bg1);
		bg_free(bg2);
		return 0;
	}


	bg_print_dec(r);
	printf("\n");


	bg_free(bg1);
	bg_free(bg2);
	bg_free(r);

	return 0;

}


