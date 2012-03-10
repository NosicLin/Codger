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

	BGInteger* bg1,*bg2;
	char* l_val=argv[1];
	char* r_val=argv[3];
	if(*l_val=='-')
	{
		bg1=bg_create_from_decstr(l_val+1);
		bg_negative(bg1);
	}
	else
	{
		bg1=bg_create_from_decstr(l_val);
	}
	if(*r_val=='-')
	{
		bg2=bg_create_from_decstr(r_val+1);
		bg_negative(bg2);
	}
	else
	{
		bg2=bg_create_from_decstr(r_val);
	}


	BGInteger* r=NULL;

	if(strcmp(argv[2],"add")==0)
	{
		r=bg_plus(bg1,bg2);
	}
	else if(strcmp(argv[2],"sub")==0)
	{
		r=bg_minus(bg1,bg2);
	}
	else if(strcmp(argv[2],"mul")==0)
	{
		r=bg_mul(bg1,bg2);

	}
	else if(strcmp(argv[2],"div")==0)
	{
		r=bg_div(bg1,bg2);

	}
	else if(strcmp(argv[2],"lshift")==0)
	{
		r=bg_lshift(bg1,bg2);
	}
	else if(strcmp(argv[2],"rshift")==0)
	{
		r=bg_rshift(bg1,bg2);
	}
	else if(strcmp(argv[2],"and")==0)
	{
		r=bg_and(bg1,bg2);
	}
	else if(strcmp(argv[2],"or")==0)
	{
		r=bg_or(bg1,bg2);
	}
	else if(strcmp(argv[2],"xor")==0)
	{
		r=bg_xor(bg1,bg2);
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
	//bg_print_bin(r);
	//printf("\n");

	bg_free(bg1);
	bg_free(bg2);
	bg_free(r);

	return 0;

}


