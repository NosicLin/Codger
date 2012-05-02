#include"gr_int.h"
#include"gr_hash.h"
#include<memory/memory.h>
#include<memory/gc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define DEFALULT_SIZE 100000

GrObject* all_keys[DEFALULT_SIZE*2];
GrObject* all_value[DEFALULT_SIZE*2];


int test_map_no_exist()
{
	GrHash* h=GrHash_New();
	int i=0;
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		GrObject* key=all_keys[i];
		GrObject* value=all_value[i];
		GrHash_Map(h,(GrObject*)key,(GrObject*)value);
	}
	return 1;
}

int test_find_exist_value()
{
	GrHash* h=GrHash_New();
	GrObject* key;
	GrObject* value;
	int i=0;
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=all_value[i];
		assert(key);
		GrHash_Map(h,key,value);

		value=GrHash_Lookup(h,key);
		if(value==NULL||((GrInt*)value)->i_value!=i*10)
		{
			return 0;
		}
	}

	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=GrHash_Lookup(h,key);
		if(value==NULL||((GrInt*)value)->i_value!=i*10)
		{
			return 0;
		}
	}
	return 1;
}
int test_find_no_exist_value()
{
	int i=0;
	GrHash* h=GrHash_New();
	GrObject* key;
	GrObject* value;
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=all_value[i];
		assert(key);
		GrHash_Map(h,key,value);

		value=GrHash_Lookup(h,key);
		if(value==NULL||((GrInt*)value)->i_value!=i*10)
		{
			return 0;
		}
	}
	for(i=DEFALULT_SIZE;i<DEFALULT_SIZE*2;i++)
	{
		key=all_keys[i];
		value=GrHash_Lookup(h,key);
		if(value!=NULL)
		{
			return 0;
		}
	}
	return 1;
}

int test_insert_exist_value()
{
	int i=0;
	GrHash* h=GrHash_New();
	GrObject* key;
	GrObject* value;
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=all_value[i];

		GrHash_Map(h,key,value);

		value=GrHash_Lookup(h,key);
		if(value==NULL||((GrInt*)value)->i_value!=i*10)
		{
			return 0;
		}
	}
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=all_value[i+1];

		GrHash_Map(h,key,value);

		value=GrHash_Lookup(h,key);

		if(value==NULL||((GrInt*)value)->i_value!=(i+1)*10)
		{
			return 0;
		}
	}
	return 1;
}

int test_del_exist_item()
{
	int i=0;
	int ret;
	GrHash* h=GrHash_New();
	GrObject* key;
	GrObject* value;
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=all_value[i];
		GrHash_Map(h,key,value);
	}

	for(i=0;i<DEFALULT_SIZE;i+=3)
	{
		key=all_keys[i];
		value=GrHash_Lookup(h,key);
		if((value==NULL)||((GrInt*)value)->i_value!=i*10)
		{
			return 0;
		}
		ret=GrHash_Del(h,key);
		if(ret<0)
		{
			return 0;
		}
		value=GrHash_Lookup(h,key);
		if((value!=NULL))
		{
			return 0;
		}
	}
	for(i=0;i<DEFALULT_SIZE;i+=3)
	{
		key=all_keys[i];
		value=GrHash_Lookup(h,key);
		if(value!=NULL)
		{
			return 0;
		}
	}
	return 1;
}


int test_del_no_exist_item()
{

	int i=0;
	int ret=0;
	GrHash* h=GrHash_New();
	GrObject* key;
	GrObject* value;
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		key=all_keys[i];
		value=all_value[i];
		GrHash_Map(h,key,value);
	}

	for(i=0;i<DEFALULT_SIZE;i+=3)
	{
		key=all_keys[i];
		value=all_value[i];
		ret=GrHash_Del(h,key);
		if(ret<0)
		{
			return 0;
		}
	}
	for(i=0;i<DEFALULT_SIZE;i+=3)
	{
		key=all_keys[i];
		value=all_value[i];
		ret=GrHash_Del(h,key);
		if(ret>=0)
		{
			return 0;
		}
	}
	
	return  1;
}

#define TEST_TIMES 1

#define Func_Test(func) \
	do{ \
		printf("Unit_Test(%s)---",#func); \
		int i=0; \
		int ret; \
		while(i++<TEST_TIMES) \
		{ \
			ret=func(); \
			if(!ret) \
			{  \
				break; \
			} \
		} \
		if(ret) \
		{  \
			printf("(Ok)"); \
			g_corret++; \
		} \
		else \
		{  \
			printf("(Falied)");  \
			g_error++; \
		} \
		printf("\n"); \
	} while(0) 


int g_corret=0;
int g_error=0;


int main(int argc,char** argv)
{

	GrModule_MemInit();
	GrModule_GcInit();
	int i=0;

	for(;i<DEFALULT_SIZE*2;i++)
	{
		all_keys[i]=(GrObject*)GrInt_New(i);
		all_value[i]=(GrObject*)GrInt_New(i*10);
	}

	Func_Test(test_map_no_exist);
	Func_Test(test_find_exist_value);
	Func_Test(test_find_no_exist_value);
	Func_Test(test_insert_exist_value);
	Func_Test(test_del_exist_item);
	Func_Test(test_del_no_exist_item);

	printf("Result: Ok(%d),Falied(%d)\n",g_corret,g_error);
	GrModule_GcExit();
	GrModule_MemExit();
	return 0;
}


