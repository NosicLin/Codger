#include<stdio.h>
#include<list_head.h>
struct file
{
	int a;
	int b;
	struct list_head c;
};

#define to_str(str) #str
int main()
{
	struct file f ;
	typeof(f);
	printf("typeof(f)=%d\n",sizeof(typeof(f)));
	return 0;
}
