#include<rtype/bt_int.h>
#include"hash_table.h"
#include"robject.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
int DEFALULT_SIZE=1000;

int main(int argc,char** argv)
{
	if(argc>=2)
	{
		DEFALULT_SIZE=atoi(argv[1]);
	}
	HashTable* h=hash_new();
	
	int i=0;
	long begin_test_value=clock();

	long now_test=0;
	long diff=0;

	printf("part1-------------\n");
	printf("now test insert item to hash_table");
	now_test=clock();
	for(;i<DEFALULT_SIZE;i++)
	{
		BtInt* int_key=btint_create(i);
		//robject_print(I_TO_R(int_key),NULL,PRINT_FLAGS_NEWLINE);
		if(int_key==NULL)
		{
			printf("create int_key(%d) failed\n",i);
			goto error;
		}
		BtInt* int_value=btint_create(i*10);
		if(int_value==NULL)
		{
			printf("create int_key(%d) failed\n",i);
			robject_release(I_TO_R(int_key));
			goto error;
		}
		Robject* key=I_TO_R(int_key);
		Robject* value=I_TO_R(int_value);

		hash_set_item(h,key,value);
		robject_release(key);
		robject_release(value);

	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);

	/*-----------------------------------------------*/
	printf("now test find exist value in hash_table");
	now_test=clock();
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value==NULL)
		{
			printf("GetItem Error(%d->NULL)\n",i);
			goto error;
		}
		int i_value=R_TO_I(value)->i_value;
		robject_release(value);
		if(i_value!=i*10)
		{
			printf("GetItem Error(%d->%d(%d))\n",i,i_value,i*10);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);


	/*----------------------------------------------*/
	printf("now test find no exist value in hash_table");
	now_test=clock();
	for(i=DEFALULT_SIZE;i<DEFALULT_SIZE*2;i++)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value!=NULL)
		{
			robject_release(value);
			printf("GetItem Key not insert,but find(%d->!NULL)\n",i);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);



	printf("\n\npart2-------------\n");
	/*-------------------------------------------*/
	printf("now test insert exist key to hash_table");
	now_test=clock();
	for(;i<DEFALULT_SIZE;i+=3)
	{
		BtInt* int_key=btint_create(i);
		//robject_print(I_TO_R(int_key),NULL,PRINT_FLAGS_NEWLINE);
		if(int_key==NULL)
		{
			printf("create int_key(%d) failed\n",i);
			goto error;
		}
		BtInt* int_value=btint_create(i*10);
		if(int_value==NULL)
		{
			printf("create int_key(%d) failed\n",i);
			robject_release(I_TO_R(int_key));
			goto error;
		}
		Robject* key=I_TO_R(int_key);
		Robject* value=I_TO_R(int_value);

		hash_set_item(h,key,value);
		robject_release(key);
		robject_release(value);

	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);

	/*-----------------------------------------------*/
	printf("now test find2 exist value in hash_table");
	now_test=clock();
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value==NULL)
		{
			printf("GetItem Error(%d->NULL)\n",i);
			goto error;
		}
		int i_value=R_TO_I(value)->i_value;
		robject_release(value);
		if(i_value!=i*10)
		{
			printf("GetItem Error(%d->%d(%d))\n",i,i_value,i*10);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);


	/*----------------------------------------------*/
	printf("now test find2 no exist value in hash_table");
	now_test=clock();
	for(i=DEFALULT_SIZE;i<DEFALULT_SIZE*2;i++)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value!=NULL)
		{
			robject_release(value);
			printf("GetItem Key not insert,but find(%d->!NULL)\n",i);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);




	printf("\n\npart1-------------\n");
	/*----------------------------------------------*/
	printf("now test hash_table.del_item");
	now_test=clock();
	for(i=0;i<DEFALULT_SIZE;i+=2)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		int del_info=hash_del_item(h,key);
		if(del_info!=0)
		{
			robject_release(key);
			printf("DelItem Error: %d Exist But Not Find\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value!=NULL)
		{
			printf("DelItem Error:key %d delete,but can find(%d)\n",
						i,R_TO_I(value)->i_value);
			robject_release(value);
		}
	}
	for(i=0;i<DEFALULT_SIZE;i+=2)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value!=NULL)
		{
			printf("DelItem Error:key %d delete,but can find(%d)\n",
						i,R_TO_I(value)->i_value);
			robject_release(value);
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);



	/*----------------------------------------------*/
	printf("now test reinsert delitem to  hash_table");
	now_test=clock();
	for(i=0;i<DEFALULT_SIZE;i+=2)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		BtInt* int_value=btint_create(i*100);
		if(int_value==NULL)
		{
			robject_release(key);
			printf("create int_value(%d) Falied\n",i*100);
		}
		Robject* value=I_TO_R(int_value);
		int insert_info=hash_set_item(h,key,value);
		robject_release(key);
		robject_release(value);
		if(insert_info!=0)
		{
			printf("ReInsert Error:insert key(%d)->value(%d) failed \n",
					i,i*100);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);


	/*--------------------------------------------------*/
	printf("now test refind hash_table.get_item");
	now_test=clock();
	for(i=0;i<DEFALULT_SIZE;i++)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value==NULL)
		{
			printf("GetItem Error(%d->NULL)\n",i);
			goto error;
		}
		int i_value=R_TO_I(value)->i_value;
		robject_release(value);
		int expect_value=i%2!=0?i*10:i*100;
		if(i_value!=expect_value)
		{
			printf("ReGetItem Error(%d->%d(%d))\n",i,i_value,expect_value);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);



	/*-----------------------------------------------------*/
	printf("now test refind no exist value in hash_table");
	now_test=clock();
	for(i=DEFALULT_SIZE;i<DEFALULT_SIZE*2;i++)
	{
		BtInt* int_key=btint_create(i);
		Robject* key=I_TO_R(int_key);
		if(int_key==NULL)
		{
			printf("create int_key(%d) faied\n",i);
			goto error;
		}
		Robject* value=hash_get_item(h,key);
		robject_release(key);
		if(value!=NULL)
		{
			robject_release(value);
			printf("GetItem Key not insert,but find(%d->!NULL)\n",i);
			goto error;
		}
	}
	diff=clock()-now_test;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);



	/*----------------------------------------------------*/

//	robject_print(HASH_TO_R(h),NULL,PRINT_FLAGS_NEWLINE);
	robject_release(HASH_TO_R(h));
	printf("Hash Unit Test Ok");
	diff=clock()-begin_test_value;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);
	return 0;
error:
	robject_release(HASH_TO_R(h));
	printf("Hash Unit Test Falied");
	diff=clock()-begin_test_value;
	printf("(%.3fs)\n",(float)diff/CLOCKS_PER_SEC);
	return -1;
}
	

	

