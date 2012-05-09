#include"bt_array.h"
#include"bt_int.h"


int test_set_and_get_item()
{
	int array_size=1000;
	BtArray* array=btarray_create_size(array_size);
	BtInt* c_i=0;
	int ret=1;
	int i;
	if(btarray_size(array)!=array_size)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_set_item(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	if(btarray_size(array)!=array_size)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size;i++)
	{
		BtInt* c_i=(BtInt*)btarray_get_item(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(btint_get(c_i)!=i)
		{
			robject_release(I_TO_R(c_i));
			c_i=0;
			ret=0;
			goto error;
		}
		robject_release(I_TO_R(c_i));
		c_i=0;
	}
	if(btarray_size(array)!=array_size)
	{
		ret=0;
		goto error;
	}
error:
	robject_release(A_TO_R(array));
	return ret;
}

int test_get_no_exist_item()
{
	int array_size=1000;
	BtArray* array=btarray_create_size(array_size);
	BtInt* c_i=0;
	int ret=1;
	int i;
	/* set array value*/
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_set_item(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
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
		c_i=(BtInt*)btarray_get_item(array,i);
		if(c_i!=NULL)
		{
			robject_release(I_TO_R(c_i));
			c_i=NULL;
			ret=0;
			goto error;
		}
	}
error:
	robject_release(A_TO_R(array));
	return ret;
}
int test_push_back_item()
{
	int array_size=1000;
	BtArray* array=btarray_create();
	BtInt* c_i=0;
	int ret=1;
	int i;
	/* push back item */
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_push_back(array,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=NULL;
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	/* examine array_size*/
	if(btarray_size(array)!=array_size)
	{
		ret=0;
		goto error;
	}

	/* examine array items is correct set*/
	for(i=0;i<array_size;i++)
	{
		c_i=(BtInt*)btarray_get_item(array,i);
		//printf("insert i=%d\n",i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(btint_get(c_i)!=i)
		{
			robject_release(I_TO_R(c_i));
			c_i=0;
			ret=0;
			goto error;
		}
		robject_release(I_TO_R(c_i));
		c_i=0;
	}
error:
	robject_release(A_TO_R(array));
	return 1;
}


/* insert front*/
int test_insert_front()
{
	int array_size=1000;
	BtArray* array=btarray_create();
	BtInt* c_i=0;
	int ret=1;
	int i;
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_insert(array,0,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}
		c_i=(BtInt*)btarray_get_item(array,0);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(btint_get(c_i)!=i)
		{
			robject_release(I_TO_R(c_i));
			c_i=0;
			ret=0;
			goto error;
		}
		robject_release(I_TO_R(c_i));
		c_i=0;
	}
	/* examine array size */
   if(btarray_size(array)!=array_size)
   {
	   ret=0;
	   goto error;
   }
   /* examine array item */
   for(i=0;i<array_size;i++)
   {
	   c_i=(BtInt*)btarray_get_item(array,i);
	   if(c_i==NULL)
	   {
		   ret=0;
		   goto error;
	   }
	   if(btint_get(c_i)!=array_size-1-i)
	   {
		   robject_release(I_TO_R(c_i));
		   c_i=0;
		   ret=0;
		   goto error;
	   }
	   robject_release(I_TO_R(c_i));
	   c_i=0;
   }
   robject_release(A_TO_R(array));
   array=0;

error:
   if(array) robject_release(A_TO_R(array));
   return ret;
}

/* insert tail */
int test_insert_tail()
{
	int array_size=1000;
	BtArray* array=btarray_create();
	BtInt* c_i=0;
	int ret=1;
	int i;

	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_insert(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}
		c_i=(BtInt*)btarray_get_item(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(btint_get(c_i)!=i)
		{
			robject_release(I_TO_R(c_i));
			c_i=0;
			ret=0;
			goto error;
		}
		robject_release(I_TO_R(c_i));
		c_i=0;
	}
	/* examine array size */
   if(btarray_size(array)!=array_size)
   {
	   ret=0;
	   goto error;
   }
   /* examine array item */
   for(i=0;i<array_size;i++)
   {
	   c_i=(BtInt*)btarray_get_item(array,i);
	   if(c_i==NULL)
	   {
		   ret=0;
		   goto error;
	   }
	   if(btint_get(c_i)!=i)
	   {
		   robject_release(I_TO_R(c_i));
		   c_i=0;
		   ret=0;
		   goto error;
	   }
	   robject_release(I_TO_R(c_i));
	   c_i=0;
   }
   robject_release(A_TO_R(array));
   array=0;


error:
   if(array) robject_release(A_TO_R(array));
   return ret;
}

int test_insert_middle()
{
	int array_size=1000;
	BtArray* array=btarray_create();
	BtInt* c_i=0;
	int ret=1;
	int i;

	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int pos=i/2;
		int r=btarray_insert(array,pos,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}
		c_i=(BtInt*)btarray_get_item(array,pos);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		if(btint_get(c_i)!=i)
		{
			robject_release(I_TO_R(c_i));
			c_i=0;
			ret=0;
			goto error;
		}
		robject_release(I_TO_R(c_i));
		c_i=0;
	}
	/* examine array size */
   if(btarray_size(array)!=array_size)
   {
	   ret=0;
	   goto error;
   }
   /* examine array item */
   for(i=0;i<array_size;i++)
   {
	   c_i=(BtInt*)btarray_get_item(array,i);
	   if(c_i==NULL)
	   {
		   ret=0;
		   goto error;
	   }
	   int val=btint_get(c_i);
	   robject_release(I_TO_R(c_i));
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
   robject_release(A_TO_R(array));
   array=0;


error:
   if(array) robject_release(A_TO_R(array));
   return ret;
}


int test_remove_front()
{

	int array_size=1000;
	BtArray* array=btarray_create_size(array_size);
	BtInt* c_i=0;
	int ret=1;
	int i;
	/* set array item from 0 to array_size-1 */
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_set_item(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=0;i<array_size/2;i++)
	{
		int r=btarray_remove(array,0);
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	if(btarray_size(array)!=array_size/2)
	{
		ret=0;
		goto error;
	}

	for(i=0;i<array_size/2;i++)
	{
		BtInt* c_i=(BtInt*)btarray_get_item(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		int val=btint_get(c_i);
		robject_release(I_TO_R(c_i));
		c_i=NULL;

		if(val!=array_size/2+i)
		{
			ret=0;
			goto error;
		}
	}
error:
	if(array) robject_release(A_TO_R(array));
	return ret;
}

int test_remove_tail()
{

	int array_size=1000;
	BtArray* array=btarray_create_size(array_size);
	BtInt* c_i=0;
	int ret=1;
	int i;
	/* set array item from 0 to array_size-1 */
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_set_item(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=array_size-1;i>=array_size/2;i--)
	{
		int r=btarray_remove(array,i);
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	if(btarray_size(array)!=array_size/2)
	{
		ret=0;
		goto error;
	}

	for(i=0;i<array_size/2;i++)
	{
		BtInt* c_i=(BtInt*)btarray_get_item(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		int val=btint_get(c_i);
		robject_release(I_TO_R(c_i));
		c_i=NULL;

		if(val!=i)
		{
			ret=0;
			goto error;
		}
	}
error:
	if(array) robject_release(A_TO_R(array));
	return ret;
}
int test_remove_middle()
{

	int array_size=1000;
	BtArray* array=btarray_create_size(array_size);
	BtInt* c_i=0;
	int ret=1;
	int i;
	/* set array item from 0 to array_size-1 */
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_set_item(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=0;i<array_size/2;i++)
	{
		int r=btarray_remove(array,array_size/4);
		if(r<0)
		{
			ret=0;
			goto error;
		}
	}
	if(btarray_size(array)!=array_size/2)
	{
		ret=0;
		goto error;
	}

	for(i=0;i<array_size/2;i++)
	{
		BtInt* c_i=(BtInt*)btarray_get_item(array,i);
		if(c_i==NULL)
		{
			ret=0;
			goto error;
		}
		int val=btint_get(c_i);
		robject_release(I_TO_R(c_i));
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
	if(array) robject_release(A_TO_R(array));
	return ret;
}


int test_remove_no_exist_item()
{

	int array_size=1000;
	BtArray* array=btarray_create_size(array_size);
	BtInt* c_i=0;
	int ret=1;
	int i;
	for(i=0;i<array_size;i++)
	{
		c_i=btint_create(i);
		int r=btarray_set_item(array,i,I_TO_R(c_i));
		robject_release(I_TO_R(c_i));
		c_i=0;
		if(r<0)
		{
			ret=0;
			goto error;
		}

	}
	for(i=array_size;i<array_size*2;i++)
	{
		int r=btarray_remove(array,i);
		if(r>=0)
		{
			ret=0;
			goto error;
		}
	}
error:
	if(array) robject_release(A_TO_R(array));
	return ret;
}

int test_plus_two_array()
{
	int array_size=1000;
	BtArray* x=btarray_create_size(array_size);
	BtArray* y=btarray_create_size(array_size);
	BtArray* xy=0;
	int ret=1;
	int i;

	/* set array x,y */
	for(i=0;i<array_size;i++)
	{
		BtInt* x_val=btint_create(i*2);
		BtInt* y_val=btint_create(i*2+1);
		int x_ret=btarray_set_item(x,i,I_TO_R(x_val));
		robject_release(I_TO_R(x_val));
		int y_ret=btarray_set_item(y,i,I_TO_R(y_val));
		robject_release(I_TO_R(y_val));
		if(x_ret<0||y_ret<0)
		{
			ret=0;
			goto error;
		}
	}

	/* test plus xy=x+y */
	xy=btarray_plus(x,y);
	if(xy==NULL)
	{
		ret=0;
		goto error;
	}
	if(btarray_size(xy)!=array_size*2)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size*2;i++)
	{
		BtInt* c_val=(BtInt*)btarray_get_item(xy,i);
		if(c_val==NULL)
		{
			ret=0;
			goto error;
		}
		int val=btint_get(c_val);

		robject_release(I_TO_R(c_val));
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
	robject_release(A_TO_R(xy));
	xy=0;

	/* xy=y+x */ 
	xy=btarray_plus(y,x);
	if(btarray_size(xy)!=array_size*2)
	{
		ret=0;
		goto error;
	}
	for(i=0;i<array_size*2;i++)
	{
		BtInt* c_val=(BtInt*)btarray_get_item(xy,i);
		if(c_val==NULL)
		{
			ret=0;
			goto error;
		}
		int val=btint_get(c_val);

		robject_release(I_TO_R(c_val));
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
	if(xy) robject_release(A_TO_R(xy));
	if(x) robject_release(A_TO_R(x));
	if(y) robject_release(A_TO_R(y));
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

