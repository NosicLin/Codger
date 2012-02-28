#include"lex_file.h"
#include<stdio.h>

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("usage %s [filename]\n",argv[0]);
		exit(0);
	}
	struct lex_file* lf=lf_create(argv[1]);

	char c;
	int i=0;
	while(1)
	{
		c=lf_next_char(lf);
		if(c==EOF)
		{
			break;
		}
		printf("%c",c);
		i++;
		if(i%100==0)
		{
			lf_mark(lf);
			lf_reset_to_mark(lf);
		}

	};
	return 0;
}

		


