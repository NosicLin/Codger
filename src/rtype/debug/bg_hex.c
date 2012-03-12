#include<stdio.h>
#include<big_integer.h>
#include<string.h>

int main()
{
	char str[2048];

	while(1)
	{
		printf("input:");
		scanf("%s",str);
		if(strcmp(str,"quit")==0)
		{
			break;
		}
		BGInteger* bg=bg_create_from_hexstr(str);
		bg_print_bin(bg);
		printf("\n");
		bg_print_dec(bg);
		printf("\n");
		bg_free(bg);
	}
	return 0;

}

		
