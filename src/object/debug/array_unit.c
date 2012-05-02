#include"gr_array.h"
#include"gr_int.h"
#include<memory/memory.h>
#include<memory/gc.h>

int test_set_and_get_item()
{
	int array_size=1000;
	GrArray* array=GrArray_NewWithSize(array_size);
	GrInt* c_i=0;
	int ret=1;
	int i;
	if(GrArray_Size(array)!=array_size)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Set(array,i,I_TO_GR(c_i));

		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	if(GrArray_Size(array)!=array_size)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size;i++)
	{
		GrInt* c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(GrInt_GetValue(c_i)!=i)
		{
			c_i=0;
			ret=0;
			goto error;
		}
		c_i=0;
	}
	if(GrArray_Size(array)!=array_size)
	{
		ret=0;
		goto error;
	}
error:
	return ret;
}

int test_get_no_exist_item()
{
	int array_size=1000;
	GrArray* array=GrArray_NewWithSize(array_size);
	GrInt* c_i=0;
	int ret=1;
	int i;
	/* set array value*/
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Set(array,i,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	/*get no exist item*/
	for(i=array_size;i<array_size*2;i++)
	{
		c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i!=NULL)
		{
			c_i=NULL;
			ret=0;
			goto error;
		}
	}
error:
	return ret;
}
int test_push_back_item()
{
	int array_size=1000;
	GrArray* array=GrArray_New();
	GrInt* c_i=0;
	int ret=1;
	int i;
	/* push back item */
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Push(array,I_TO_GR(c_i));
		c_i=NULL;
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	/* examine array_size*/
	if(GrArray_Size(array)!=array_size)
	{
		ret=0;
		goto error;
	}

	/* examine array items is correct set*/
	for(i=0;i<array_size;i++)
	{
		c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(GrInt_GetValue(c_i)!=i)
		{
			c_i=0;
			ret=0;
			goto error;
		}
		c_i=0;
	}
error:
	return 1;
}


/* insert front*/
int test_insert_front()
{
	int array_size=1000;
	GrArray* array=GrArray_New();
	GrInt* c_i=0;
	int ret=1;
	int i;
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Insert(array,0,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}
		c_i=(GrInt*)GrArray_Get(array,0);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(GrInt_GetValue(c_i)!=i)
		{
			c_i=0;
			ret=0;
			goto error;
		}
		c_i=0;
	}
	/* examine array size */
   if(GrArray_Size(array)!=array_size)
   {
	   ret=0;
	   goto error;
   }
   /* examine array item */
   for(i=0;i<array_size;i++)
   {
	   c_i=(GrInt*)GrArray_Get(array,i);
	   if(c_i==NULL)
	   {
		   ret=0;
		   goto error;
	   }
	   if(GrInt_GetValue(c_i)!=array_size-1-i)
	   {
		   c_i=0;
		   ret=0;
		   goto error;
	   }
	   c_i=0;
   }
   array=0;

error:
   return ret;
}

/* insert tail */
int test_insert_tail()
{
	int array_size=1000;
	GrArray* array=GrArray_New();
	GrInt* c_i=0;
	int ret=1;
	int i;

	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Insert(array,i,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}
		c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(GrInt_GetValue(c_i)!=i)
		{
			c_i=0;
			ret=0;
			goto error;
		}
		c_i=0;
	}
	/* examine array size */
   if(GrArray_Size(array)!=array_size)
   {
	   ret=0;
	   goto error;
   }
   /* examine array item */
   for(i=0;i<array_size;i++)
   {
	   c_i=(GrInt*)GrArray_Get(array,i);
	   if(c_i==NULL)
	   {
		   ret=0;
		   goto error;
	   }
	   if(GrInt_GetValue(c_i)!=i)
	   {
		   c_i=0;
		   ret=0;
		   goto error;
	   }
	   c_i=0;
   }
   array=0;


error:
   return ret;
}

int test_insert_middle()
{
	int array_size=1000;
	GrArray* array=GrArray_New();
	GrInt* c_i=0;
	int ret=1;
	int i;

	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int pos=i/2;
		int r=GrArray_Insert(array,pos,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}
		c_i=(GrInt*)GrArray_Get(array,pos);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(GrInt_GetValue(c_i)!=i)
		{
			c_i=0;
			ret=0;
			goto error;
		}
		c_i=0;
	}
	/* examine array size */
   if(GrArray_Size(array)!=array_size)
   {
	   ret=0;
	   goto error;
   }
   /* examine array item */
   for(i=0;i<array_size;i++)
   {
	   c_i=(GrInt*)GrArray_Get(array,i);
	   if(c_i==NULL)
	   {
		   ret=0;
		   goto error;
	   }
	   int val=GrInt_GetValue(c_i);
	   c_i=0;
	   if(i<array_size/2)
	   {
		   if(val!=i*2+1)
		   {
			   ret=0;
			   goto error;
		   }
	   }
	   if(i>=array_size/2)
	   {
		   if(val!=(array_size-i-1)*2)
		   {
			   ret=0;
			   goto error;
		   }

	   }


   }
error:
   return ret;
}


int test_remove_front()
{

	int array_size=1000;
	GrArray* array=GrArray_NewWithSize(array_size);
	GrInt* c_i=0;
	int ret=1;
	int i;
	/* set array item from 0 to array_size-1 */
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Set(array,i,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=0;i<array_size/2;i++)
	{
		int r=GrArray_Remove(array,0);
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	if(GrArray_Size(array)!=array_size/2)
	{
		ret=0;
		goto error;
	}

	for(i=0;i<array_size/2;i++)
	{
		GrInt* c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		int val=GrInt_GetValue(c_i);
		c_i=NULL;

		if(val!=array_size/2+i)
		{
			ret=0;
			goto error;
		}
	}
error:
	return ret;
}

int test_remove_tail()
{

	int array_size=1000;
	GrArray* array=GrArray_NewWithSize(array_size);
	GrInt* c_i=0;
	int ret=1;
	int i;
	/* set array item from 0 to array_size-1 */
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Set(array,i,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=array_size-1;i>=array_size/2;i--)
	{
		int r=GrArray_Remove(array,i);
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	if(GrArray_Size(array)!=array_size/2)
	{
		ret=0;
		goto error;
	}

	for(i=0;i<array_size/2;i++)
	{
		GrInt* c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		int val=GrInt_GetValue(c_i);
		c_i=NULL;

		if(val!=i)
		{
			ret=0;
			goto error;
		}
	}
error:
	return ret;
}
int test_remove_middle()
{

	int array_size=1000;
	GrArray* array=GrArray_NewWithSize(array_size);
	GrInt* c_i=0;
	int ret=1;
	int i;
	/* set array item from 0 to array_size-1 */
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Set(array,i,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=0;i<array_size/2;i++)
	{
		int r=GrArray_Remove(array,array_size/4);
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	if(GrArray_Size(array)!=array_size/2)
	{
		ret=0;
		goto error;
	}

	for(i=0;i<array_size/2;i++)
	{
		GrInt* c_i=(GrInt*)GrArray_Get(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		int val=GrInt_GetValue(c_i);
		c_i=NULL;

		if(i<array_size/4)
		{
			if(val!=i)
			{
				printf("val=%d ,real=%d \n",val,i);
				ret=0;
				goto error;
			}
		}
		else 
		{
			if(val!=array_size/2+i)
			{
				printf("val=%d ,real=%d \n",val,array_size/2+i);
				ret=0;
				goto error;
			}
		}
	}
error:
	return ret;
}


int test_remove_no_exist_item()
{

	int array_size=1000;
	GrArray* array=GrArray_NewWithSize(array_size);
	GrInt* c_i=0;
	int ret=1;
	int i;
	for(i=0;i<array_size;i++)
	{
		c_i=GrInt_New(i);
		int r=GrArray_Set(array,i,I_TO_GR(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=array_size;i<array_size*2;i++)
	{
		int r=GrArray_Remove(array,i);
		if(r>=0)
		{
			ret=0;
			goto error;
		}
	}
error:
	return ret;
}

int test_plus_two_array()
{
	int array_size=1000;
	GrArray* x=GrArray_NewWithSize(array_size);
	GrArray* y=GrArray_NewWithSize(array_size);
	GrArray* xy=0;
	int ret=1;
	int i;

	/* set array x,y */
	for(i=0;i<array_size;i++)
	{
		GrInt* x_val=GrInt_New(i*2);
		GrInt* y_val=GrInt_New(i*2+1);
		int x_ret=GrArray_Set(x,i,I_TO_GR(x_val));
		int y_ret=GrArray_Set(y,i,I_TO_GR(y_val));
		if(x_ret<0||y_ret<0)
		{
			ret=0;
			goto error;
		}
	}

	/* test plus xy=x+y */
	xy=GrArray_Plus(x,y);
	if(xy==NULL)
	{
		ret=0;
		goto error;
	}
	if(GrArray_Size(xy)!=array_size*2)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size*2;i++)
	{
		GrInt* c_val=(GrInt*)GrArray_Get(xy,i);
		if(c_val==NULL)
		{
			ret=0;
			goto error;
		}
		int val=GrInt_GetValue(c_val);

		c_val=0;

		if(i<array_size)
		{
			if(val!=i*2)
			{
				ret=0;
				goto error;
			}
		}
		else
		{
			if(val!=(i-array_size)*2+1)
			{
				ret=0;
				goto error;
			}
		}
	}
	xy=0;

	/* xy=y+x */ 
	xy=GrArray_Plus(y,x);
	if(GrArray_Size(xy)!=array_size*2)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size*2;i++)
	{
		GrInt* c_val=(GrInt*)GrArray_Get(xy,i);
		if(c_val==NULL)
		{
			ret=0;
			goto error;
		}
		int val=GrInt_GetValue(c_val);

		c_val=0;

		if(i<array_size)
		{
			if(val!=i*2+1)
			{
				ret=0;
				goto error;
			}
		}
		else
		{
			if(val!=(i-array_size)*2)
			{
				ret=0;
				goto error;
			}
		}
	}
error:
	return ret;
}


#define Func_Test(func) \
	do{ \
		printf("Unit_Test(%s)---",#func); \
		int ret=func(); \
		if(ret) { printf("(Ok)");g_corret++; } \
		else \
		{ printf("(Falied)"); g_error++;} \
		printf("\n"); \
	} while(0) 

static int g_corret=0;
static int g_error=0;
int main()
{
	GrModule_MemInit();
	GrModule_GcInit();

	Func_Test(test_set_and_get_item);
	Func_Test(test_get_no_exist_item);
	Func_Test(test_push_back_item);
	Func_Test(test_insert_front);
	Func_Test(test_insert_tail);
	Func_Test(test_insert_middle);
	Func_Test(test_remove_front);
	Func_Test(test_remove_tail);
	Func_Test(test_remove_middle);
	Func_Test(test_remove_no_exist_item);
	Func_Test(test_plus_two_array);
	printf("Unit_Test Result:Corret=%d, Error=%d, Total=%d \n",g_corret,g_error,g_corret+g_error);
	return 0;
}

