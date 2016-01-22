#include <stdio.h>
#include <math.h>

typedef struct {
	union{
		int act_semqKey;
		struct {
		int act_semqKey2;
		}h2,
		 h1;
	}ttt[10];
}actdata;

int main(){
   actdata aaa;
   aaa.ttt[0].act_semqKey = 10;
   printf("aaa size = %d \n", sizeof(aaa));   
   printf("aaa act_semqKey2 = %d \n", aaa.ttt[0].h1.act_semqKey2);  
}

