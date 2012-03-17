#include<stdio.h>
#include<big_integer.h>
#include<string.h>
char val[1024*1024*8];
char op[1204];
int main(int argc,char** argv)
{
	BGInteger* bg1;
	while(1)
	{
		scanf("%s",val);
		if(strcmp(val,"quit")==0)
		{
			break;
		}

		if(*val=='-')
		{
			bg1=bg_create_from_decstr(val+1);
			bg_self_negative(bg1);
		}
		else
		{
			bg1=bg_create_from_decstr(val);
		}

		float value=bg_to_float(bg1);
		printf("%g\n",value);
	}
	return 0;
}

