#include "test.h"
//using namespace std;
void *AlertSettingUpdateObject(void* apiName);

typedef struct AlerSettingUpdatePara{
	std::string objID;
	std::string msgID;
}AlerSettingUpdatePara;

int main (){
	AlerSettingUpdatePara body;
//	body = "he";
//	body.new();
	AlertSettingUpdateObject((void*)&body);
	printf("%s\n",body.objID.c_str());
	printf("%s\n",body.msgID.c_str());
//	body.to_string();

    
}

void *AlertSettingUpdateObject(void* apiName)
{
	AlerSettingUpdatePara* Test =  (AlerSettingUpdatePara*)apiName;
	Test-> objID = "123";
	Test-> msgID = "00003";
	printf("ss %s\n",Test->msgID.c_str());
	
}