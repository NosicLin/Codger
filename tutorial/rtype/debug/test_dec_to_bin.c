#include<stdio.h>
int main()
{
	char str[2048];
	char str2[2048];
	char result[2048*4];

	while(1)
	{
		printf("input:");
		scanf("%s",str);

		char* cal_str=str;
		char* re_str=str2;


		int r_pos=0;
		while(cal_str[0])
		{
			int i=0;
			int c_remainder=0;

			while(cal_str[i])
			{
				int c_val=cal_str[i]-'0'+c_remainder*10;
				re_str[i]=(c_val/2)+'0';
				c_remainder=c_val%2;
				i++;
			}
			result[r_pos++]=c_remainder+'0';

			re_str[i]='\0';
			if(re_str[0]=='0') re_str++;
			char* temp=cal_str;
			cal_str=re_str;
			re_str=temp;
		}
		while(r_pos--)
		{
			printf("%c",result[r_pos]);

		}

		printf("\n");
	}

	return 0;
}
