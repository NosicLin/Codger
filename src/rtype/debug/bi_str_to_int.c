#include"bt_int.h"
#include<string.h>
#include<stdio.h>
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

		BtInt* value=bt_int_from_str(buf);

		printf("%d\n",value->i_value);
		bt_int_free(value);
	}
	return 0;
}




