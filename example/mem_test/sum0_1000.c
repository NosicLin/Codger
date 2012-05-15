#include<stdio.h>
int main()
{
	int sum=0;
	int i=0;
	while (i<3000000)
	{
		sum+=i;
		i+=1;
	}
	printf("%d\n",sum);
	return 0;
}


