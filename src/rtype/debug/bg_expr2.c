
#include<stdio.h>
#include<big_integer.h>
#include<string.h>

char l_val[1024*1024*8];
char r_val[1024*1024*8];
char op[1204];
int main(int argc,char** argv)
{
	BGInteger* bg1,*bg2;
	while(1)
	{
		scanf("%s",l_val);
		if(strcmp(l_val,"quit")==0)
		{
			break;
		}
		scanf("%s",op);
		scanf("%s",r_val);

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
			break;
		}

		bg_print_dec(r);
		printf("\n");
		//bg_print_bin(r);
		//printf("\n");

		bg_free(bg1);
		bg_free(bg2);
		bg_free(r);
	}

	return 0;

}


