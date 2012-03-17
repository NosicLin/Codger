#include"bt_long.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char buf[1024];
int main()
{

	while(1)
	{
		scanf("%s",buf);
		if(strcmp(buf,"quit")==0)
		{
			break;
		}

		BtLong* value=bt_long_from_str(buf);

		bg_print_dec(value->l_value);
		bt_long_free(value);
		printf("\n");
	}
	return 0;
}




