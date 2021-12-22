#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define CONFIG_FILE "server.ttyEcho.conf"
#define CONFIG_FILE_SIZE 4096
#define warn(msg, arg...)  printf(msg, ##arg)


#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#if 1
char *str_replace (const char *source, char *find,  char *rep){ 
	int find_L=strlen(find);
	int rep_L=strlen(rep);
	int length=strlen(source)+1;
	int gap=0;

	// allocate memory and make a copy
	char *result = (char*)malloc(sizeof(char) * length);
	strcpy(result, source);

	char *former;
	// find string location
	char *location= strstr(source, find); 
	while(location!=NULL){
		gap+=(location - source);
		result[gap]='\0';
		length+=(rep_L-find_L);
		result = (char*)realloc(result, length * sizeof(char));
		strcat(result, rep);
		gap+=rep_L;
		former=location+find_L;
		strcat(result, former);
		location= strstr(former, find);
	}
	return result;
}
/*
char *str_replace (char *source, char *find,  char *rep){ 
	int find_L=strlen(find);
	int rep_L=strlen(rep);
	int length=strlen(source)+1;
	int gap=0;

	// allocate memory and make a copy
	char *result = (char*)malloc(sizeof(char) * length);
	strcpy(result, source);

	char *former=source;
	// find string location
	char *location= strstr(former, find); 
	while(location!=NULL){
		gap+=(location - former);
		result[gap]='\0';
		length+=(rep_L-find_L);
		result = (char*)realloc(result, length * sizeof(char));
		strcat(result, rep);
		gap+=rep_L;
		former=location+find_L;
		strcat(result, former);
		location= strstr(former, find);
	}
	return result;
}
*/
#else
/* str_replace [字串取代] 
* @param {char*} source 原始的文字 
* @param {char*} find 搜尋的文字   
* @param {char*} rep 替換的文字 
* */  
char *str_replace (char *source, char *find,  char *rep){  
   // 搜尋文字的長度  
   int find_L=strlen(find);  
   // 替換文字的長度  
   int rep_L=strlen(rep);  
   // 結果文字的長度  
   int length=strlen(source)+1;  
   // 定位偏移量  
   int gap=0;  
     
   // 建立結果文字，並複製文字  
   char *result = (char*)malloc(sizeof(char) * length);  
   strcpy(result, source);      
     
   // 尚未被取代的字串  
   char *former=source;  
   // 搜尋文字出現的起始位址指標  
   char *location= strstr(former, find);  
     
   // 漸進搜尋欲替換的文字  
   while(location!=NULL){  
       // 增加定位偏移量  
       gap+=(location - former);  
       // 將結束符號定在搜尋到的位址上  
       result[gap]='\0';  
         
       // 計算新的長度  
       length+=(rep_L-find_L);  
       // 變更記憶體空間  
       result = (char*)realloc(result, length * sizeof(char));  
       // 替換的文字串接在結果後面  
       strcat(result, rep);  
       // 更新定位偏移量  
       gap+=rep_L;  
         
       // 更新尚未被取代的字串的位址  
       former=location+find_L;  
       // 將尚未被取代的文字串接在結果後面  
       strcat(result, former);  
         
       // 搜尋文字出現的起始位址指標  
       location= strstr(former, find);  
   }      
  
   return result;  
}  
#endif

int main (int argc, char *argv[])
{
    char* client_name = str_replace(CONFIG_FILE,"server","client");
	printf("server_name = %s\n", CONFIG_FILE);
	printf("client_name = %s\n", client_name);
	free(client_name);
    return 0;
}

