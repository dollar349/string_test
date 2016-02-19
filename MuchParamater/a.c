#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#if 1
typedef enum {
    ACTION_BLOCK,
    ACTION_NONBLOCK
} COOLERAPI_BLOCK_STATUS_e;

int Myfunc(int first, const char *userName, ...)
{
    COOLERAPI_BLOCK_STATUS_e block_st;
    va_list ap;
	va_start(ap, userName);
    block_st = va_arg(ap,COOLERAPI_BLOCK_STATUS_e);

	if (block_st == ACTION_NONBLOCK)
	{printf("*******Nonblock work *****\n");}
    else
	{
		printf("block work \n");
	}
	va_end(ap);
	
    return first; 	
}


int main()
{
    int a=10;
   // int b=7;
    int res;
    res = Myfunc(a,"hello");
    printf("Res = %d\n", res);
}


#else

void ar_cnt(int cnt,...);
void ar_cst(char const *s,...);
int main(int argc, char* argv[])
{
   // int in_size =_INTSIZEOF(int);
    //printf("int_size=%d\n",in_size);
    ar_cnt(5,1,2,3,4);
    return 0; 
}
void ar_cnt(int cnt,...)
{
    int value1=0;
    int i=0;
    int arg_cnt = cnt;
    va_list arg_ptr;
    va_start(arg_ptr,cnt);
    for(i=0;i<cnt;i++)
    {
        value1=va_arg(arg_ptr,int);
        printf("posation %d=%d\n",value1,i+1);
    }
    va_end(arg_ptr);
}
#endif