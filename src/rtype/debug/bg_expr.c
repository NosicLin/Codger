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
	// printf("%s %s %s %s\n",argv[0],argv[1],op,argv[3]);

	BGInteger* bg1,*bg2;
	char* l_val=argv[1];
	char* r_val=argv[3];
	char* op=argv[2];


	if(*l_val=='-')
	{
		bg1=bg_create_from_decstr(l_val+1);
		bg_self_negative(bg1);
	}
	else
	{
		bg1=bg_create_from_decstr(l_val);
	}
	if(*r_val=='-')
	{
		bg2=bg_create_from_decstr(r_val+1);
		bg_self_negative(bg2);
	}
	else
	{
		bg2=bg_create_from_decstr(r_val);
	}
	/*
	bg_print_dec(bg1);
	printf("\n");
	bg_print_bin(bg1);
	printf("\n");


	bg_print_dec(bg2);
	printf("\n");
	bg_print_bin(bg2);
	printf("\n");

	*/

	BGInteger* r=NULL;

	if(strcmp(op,"add")==0)
	{
		r=bg_plus(bg1,bg2);
	}
	else if(strcmp(op,"sub")==0)
	{
		r=bg_minus(bg1,bg2);
	}
	else if(strcmp(op,"mul")==0)
	{
		r=bg_mul(bg1,bg2);

	}
	else if(strcmp(op,"div")==0)
	{
		r=bg_div(bg1,bg2);

	}
	else if(strcmp(op,"mod")==0)
	{
		r=bg_mod(bg1,bg2);

	}
	else if(strcmp(op,"lshift")==0)
	{
		r=bg_lshift(bg1,bg2);
	}
	else if(strcmp(op,"rshift")==0)
	{
		r=bg_rshift(bg1,bg2);
	}
	else if(strcmp(op,"and")==0)
	{
		r=bg_and(bg1,bg2);
	}
	else if(strcmp(op,"or")==0)
	{
		r=bg_or(bg1,bg2);
	}
	else if(strcmp(op,"xor")==0)
	{
		r=bg_xor(bg1,bg2);
	}
	else
	{
		printf(" %s is invalid,please use right operator\n",op);
		bg_free(bg1);
		bg_free(bg2);
		return 0;
	}

	bg_print_dec(r);
	printf("\n");
	//bg_print_bin(r);
	//printf("\n");

	bg_free(bg1);
	bg_free(bg2);
	bg_free(r);

	return 0;

}


