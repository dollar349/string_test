#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>



int main (int argc, char *argv[])
{
    unsigned long t = 0;
	//u_int32_t t = 0;
	//double t = 0;
	printf("%d\n",sizeof(t));
	
    struct timeval ttt;
    gettimeofday(&ttt, NULL);
    t = (1000 * ttt.tv_sec) + (ttt.tv_usec / 1000);
	printf("%llu\n",t);
	//printf("%d\n",ttt.tv_sec);
 
    return 0;
}

