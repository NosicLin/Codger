#include<stdio.h>
#include<big_integer.h>
#include<string.h>
#include<time.h>

char buf_l[100000];
char buf_r[100000];
char exe_name[]="bg_expr ";

void gen_value(char* buf,int length)
{
	int real_len=rand()%length+1;
	int i=0;
	if(rand()%2)
	{
		buf[i]='-';
		i++;
	}
	int value=rand()%10;
	while(!value)
	{
		value=rand()%10;
	}
	buf[i]='0'+value;
	i++;
	for(;i<real_len;i++)
	{
		int value=rand()%10;
		buf[i]='0'+value;
	}
	buf[i]=0;
}
void bash_write(FILE* f)
{
	fwrite(exe_name,1,strlen(exe_name),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite(" or ",1,strlen(" or "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("\n",1,1,f);

	fwrite(exe_name,1,strlen(exe_name),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite(" and ",1,strlen(" and "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("\n",1,1,f);

	fwrite(exe_name,1,strlen(exe_name),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite(" xor ",1,strlen(" xor "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("\n",1,1,f);
}
void python_write(FILE* f)
{

	fwrite("a=",1,strlen("a="),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite("l",1,strlen("l"),f);
	fwrite(" | ",1,strlen(" | "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("l",1,strlen("l"),f);
	fwrite("\n",1,1,f);
	fwrite("print a\n",1,strlen("print a\n"),f);

	fwrite("a=",1,strlen("a="),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite("l",1,strlen("l"),f);
	fwrite(" & ",1,strlen(" & "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("l",1,strlen("l"),f);
	fwrite("\n",1,sizeof("\n")-1,f);
	fwrite("print a\n",1,strlen("print a\n"),f);

	fwrite("a=",1,strlen("a="),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite("l",1,strlen("l"),f);
	fwrite(" ^ ",1,strlen(" ^ "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("l",1,strlen("l"),f);
	fwrite("\n",1,sizeof("\n")-1,f);
	fwrite("print a\n",1,strlen("print a\n"),f);

}

void bash_lshift_write(FILE* f)
{
	fwrite("bg_expr ",1,sizeof("bg_expr"),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite(" lshift ",1,strlen(" lshift "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("\n",1,1,f);
}
void python_lshift_write(FILE* f)
{
	fwrite("a=",1,strlen("a="),f);
	fwrite(buf_l,1,strlen(buf_l),f);
	fwrite("l",1,strlen("l"),f);
	fwrite(" << ",1,strlen(" << "),f);
	fwrite(buf_r,1,strlen(buf_r),f);
	fwrite("l",1,strlen("l"),f);
	fwrite("\n",1,sizeof("\n")-1,f);
	fwrite("print a\n",1,strlen("print a\n"),f);

}

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("usage %s <num> <length> \n",argv[0]);
		exit(-1);
	}

	FILE* bash=fopen("bg.sh","w+");
	FILE* python=fopen("bg.py","w+");

	int num=atoi(argv[1]);
	int length=atoi(argv[2]);

	srand(time(NULL));

	int i=0;
	for(;i<num;i++)
	{

		gen_value(buf_l,length);
		gen_value(buf_r,length);

//		printf("left=%s\n",buf_l);
//		printf("right=%s\n",buf_r);
		bash_write(bash);
		python_write(python);

	}


	fclose(bash);
	fclose(python);
	return 0;
}






