#include <stdio.h>
#include <string.h>
#include "1.h"

#define CLI_LINE 3
char CLIADMIN_POWER_1[CLI_LINE][100] = {"[1]---23.40 W : 61.10 VA",
							        "[1]---(L1) 24.40 W : 63.20 VA",
							        "[1]---(A) 21.90 W : 61.00 VA (B) 0.00 W : 0.00 VA"};

char CLIADMIN_POWER_1_A[CLI_LINE][100] = {"[1]---(A) 20.30 W : 51.50 VA",
							        "",
							        ""};

char CLIADMIN_POWER_1_A_1[CLI_LINE][100] = {"[1.A]---(1) No Support",
							        "",
							        ""};

char CLIADMIN_POWER_2_A_1[CLI_LINE][100] = {"[2.A]---(1) 0.00 W : 0.00 VA",
							        "",
							        ""};

void prepare_string(char *your_str_tmp);			
void prepare_string(char *your_str_tmp)
{
	int i;
	char a8tmp[200];
	char* p8ptr;
    your_str_tmp[0] = PDUCB_CLI_CTRL_CHAR_CR;
    your_str_tmp[1] = PDUCB_CLI_CTRL_CHAR_LF;
	p8ptr = &your_str_tmp[2] ;
	for (i=0; i < CLI_LINE; i++)
	{
		sprintf(a8tmp, "%s%c%c",CLIADMIN_POWER_1_A[i],PDUCB_CLI_CTRL_CHAR_CR,PDUCB_CLI_CTRL_CHAR_LF);
        strcat(p8ptr, a8tmp);
	}
    sprintf(a8tmp, "%c%c", PDUCB_CLI_CTRL_CHAR_CR,PDUCB_CLI_CTRL_CHAR_LF);
    strcat(p8ptr, a8tmp);
}						
									
typedef struct  
{
    UINT8 receptacle:8;
    UINT8 branch:4;
    UINT8 pdu:3;
} *pPDU_P2_Format;


typedef struct _PDU_DATA_PACKAGE
{
    UINT16 u16BufferSize;
    UINT16 u16RespLen;
    UINT8 au8Buffer[];
} *pPDU_DATA_PACKAGE;

#define PDUCB_CLI_RCPTSTATE_CMD "receptaclestate"
#define PDUCB_CLI_PWRCONSUMP_CMD "power"
#define CLISETRCPTSTATE_BUFFER 1000



int receptaclestate()
{
	UINT16 u16Parameter2;
	pPDU_P2_Format pPDU_which_recp = (pPDU_P2_Format)&u16Parameter2;
	UINT8 au8tmp[10];
	UINT8 data_buf[ CLISETRCPTSTATE_BUFFER + 4 ] = {0};
    pPDU_DATA_PACKAGE pPDU_SENSOR_BUFFER = (pPDU_DATA_PACKAGE) data_buf; 
	char pWriteData[] ="off";
	
  u16Parameter2=0x1100;
    if (0 == pPDU_which_recp->pdu)
    {
        printf( "return STATUS_DEVICE_NACK\n");
        return 1;
    }
    sprintf(&pPDU_SENSOR_BUFFER->au8Buffer[1], "%s %d", PDUCB_CLI_RCPTSTATE_CMD, pPDU_which_recp->pdu);       
    if (0 != pPDU_which_recp->branch)
    {
        sprintf((char *)au8tmp,".%c",((pPDU_which_recp->branch) + 0x40));
        strcat((char *)&pPDU_SENSOR_BUFFER->au8Buffer[1], (char *)au8tmp);
    }
    else if (0 != pPDU_which_recp->receptacle)
    {
            printf("return STATUS_DEVICE_NACK\n");
            return 1;    
    }
    if (0 != pPDU_which_recp->receptacle)
    {
        sprintf( (char *)au8tmp,".%d", pPDU_which_recp->receptacle);
        strcat( (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1], (char *)au8tmp);
    }    
    sprintf( (char *)au8tmp, " %s", pWriteData);
    strcat( (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1], (char *)au8tmp);

    printf("COMMAND is : %s \n", (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1]);
    return 0;
}

int getpower()
{
	UINT16 u16Parameter2;
	pPDU_P2_Format pPDU_which_recp = (pPDU_P2_Format)&u16Parameter2;
	UINT8 au8tmp[10];
	UINT8 auKey[10]={0};
	UINT8 data_buf[ CLISETRCPTSTATE_BUFFER + 4 ] = {0};
    pPDU_DATA_PACKAGE pPDU_SENSOR_BUFFER = (pPDU_DATA_PACKAGE) data_buf; 
	
  u16Parameter2=0x1000;
	if (0 == pPDU_which_recp->pdu)
	{
		printf(0, "return RAW_DEVICE_NACK\n");
		return 0;
	}
	sprintf((char *)auKey," %d",pPDU_which_recp->pdu);           
	if (0 != pPDU_which_recp->branch)
	{
		sprintf((char *)au8tmp,".%c",((pPDU_which_recp->branch) + 0x40));
		strcat((char *)auKey, (char *)au8tmp);
	}
	else if (0 != pPDU_which_recp->receptacle)
	{
			printf(0, "return RAW_DEVICE_NACK\n");
			return 0;    
	}
	if (0 != pPDU_which_recp->receptacle)
	{
		sprintf( (char *)au8tmp,".%d", pPDU_which_recp->receptacle);
		strcat( (char *)auKey, (char *)au8tmp);
	}    
	strcat( (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1], (char *)auKey);

    printf("COMMAND is : %s \n", (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1]);


    
}
RAWSTATUS PDUCLI_AdminGetPowerByKey(const char* string_data, const char* key, paPDU_POWER PDU_POWER)
{
    char acRealkey[10];
    char acTmp[10];
    char acBuffer[100];
    UINT8 *pu8DataPtr;
    UINT8 *pu8DataStartPtr;
    UINT8 *pu8DataEndPtr;

    strncpy( acTmp, key, 10);
    pu8DataPtr = strrchr(acTmp,'.');
    if (pu8DataPtr != NULL)
    {
        *pu8DataPtr = '\0';
    }
    sprintf(acRealkey, "[%s]", acTmp); 

    if ( RAW_OK != PDUCLI_AdminGetValueByKey(string_data, acRealkey, acBuffer, 100))
    {
        return RAW_FAIL;
    }
    //dollar++
    pu8DataPtr = (UINT8 *)strstr(acBuffer, PDUCB_CLI_ADMINCMD_NOSUPPORT_STR);
    if(pu8DataPtr != NULL)
    {
        _DEBUG(0, "Device not support\n");
        return RAW_DEVICE_NOT_SUPPORT;
    }
    printf(acBuffer);
    printf("\n");
    pu8DataPtr = strstr (acBuffer,".");
    /* Get Watt start*/

    while (isdigit(*(pu8DataStartPtr))) 
    {
        if (pu8DataStartPtr == acBuffer)
            break;
        pu8DataStartPtr--;
    }
    
    printf (pu8DataStartPtr);
    printf("\n");

}
/*    
RAWSTATUS PDUCLI_AdminGetPowerByKey(const char* string_data, const char* key, paPDU_POWER PDU_POWER)
{
    char acRealkey[10];
    char acTmp[10];
    char acBuffer[100];
    UINT8 *pu8DataPtr;

    strncpy( acTmp, key, 10);
    pu8DataPtr = strrchr(acTmp,'.');
    *pu8DataPtr = '\0';
    sprintf(acRealkey, "[%s]", acTmp); 
	printf ("acRealkey = %s\n", acRealkey);
    if ( RAW_OK != PDUCLI_AdminGetValueByKey(string_data, acRealkey, acBuffer, 100))
    {
        return RAW_FAIL;
    }
	printf (acBuffer);
	
    return RAW_OK;	
}
*/
int main ()
{
  //receptaclestate();
  //getpower();
  char powerstr[500]={0};
  aPDU_POWER mypdu;

  prepare_string (powerstr);
  
  
  printf(powerstr);
  
  PDUCLI_AdminGetPowerByKey(powerstr, "1.A", &mypdu);
  
  
  return 0;
}


#define CLI_ADMIN_KEY_MAXIMUM 30 
RAWSTATUS PDUCLI_AdminGetValueByKey(const char* string_data, const char* key, char* value, UINT16 value_buff_size)
{
    UINT8 acKey[CLI_ADMIN_KEY_MAXIMUM + 2];
    UINT8 u8KeyLength;
    UINT8 *pu8DataPtr = NULL;
    UINT8 *pu8DataPtr_tmp = NULL;
    
    // 1. check key length
    u8KeyLength = strlen (key);
    if ( u8KeyLength > CLI_ADMIN_KEY_MAXIMUM )
    {
        _DEBUG(0, "Key too long\n");
        return RAW_BUSY;
    }
    
    // 2. make key 
    acKey[0] = PDUCB_CLI_CTRL_CHAR_CR;
    acKey[1] = PDUCB_CLI_CTRL_CHAR_LF;
    strcpy( &acKey[2], key);

    // 3. find key in string
    pu8DataPtr = strstr (string_data, acKey);
    if ( NULL == pu8DataPtr)
    {
        _DEBUG(0, "cannot find key \n");
        return RAW_FAIL;
    }

    // 4. shift point to value start
    pu8DataPtr = (pu8DataPtr + u8KeyLength + 2);
    while ( *pu8DataPtr == PDUCB_CLI_CHAR_ENDASH )
    {
        //printf("%c \n",*pu8DataPtr );
        pu8DataPtr++;
    }

    // 5. find value end.
    pu8DataPtr_tmp = strchr(pu8DataPtr, PDUCB_CLI_CTRL_CHAR_CR);
    //printf("value length %d", (pu8DataPtr_tmp - pu8DataPtr));
    if ( (pu8DataPtr_tmp - pu8DataPtr) > value_buff_size )
    {
        _DEBUG(0, "Buff not enough \n");
        return RAW_DEVICE_AL;
    }

    // 6. got value.   
    strncpy( value, pu8DataPtr, (pu8DataPtr_tmp - pu8DataPtr));
    value[(pu8DataPtr_tmp - pu8DataPtr)] = '\0' ;
    return RAW_OK;
}

#if 0
int main ()
{
  char str[] ="[1.A]---(1) {Off : Normal : Unlocked : Critical}";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strstr(str, "{");
  pch = strtok (pch,"{ :");
//  printf ("%s\n",pch);
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, "{} :");
  }
  return 0;
}
#endif