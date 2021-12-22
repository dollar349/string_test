#include "test.h"
using namespace std;

int main (){
        string test("xyz.openbmc_project.console.ttyEcho");
        test = test.substr(test.find_last_of('.')+1);
        cout << test << endl;  
//	body = "he";
//	body.new();
//	AlertSettingUpdateObject((void*)&body);
//	printf("%s\n",body.objID.c_str());
//	printf("%s\n",body.msgID.c_str());
//	body.to_string();

    
}
