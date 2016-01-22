#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "1.h"

#define CLI_LINE 8
#define DEF_P2 0x0000
#define TEST_KEY "1.A.1"
#define SEND_CMD CLIADMIN_POWER
char CLIADMIN_POWER_1[CLI_LINE][100] = {"[1]---23.40 W : 61.10 VA",
							        "[1]---(L1) 24.40 W : 63.20 VA",
							        "[1]---(A) 21.90 W : 61.00 VA (B) 0.00 W : 0.00 VA"
									,"","","","",""};

char CLIADMIN_POWER_1_A[CLI_LINE][100] = {"[1]---(A) 20.30 W : 51.50 VA",
							        "",
							        "","","","","",""};

char CLIADMIN_POWER_1_A_1[CLI_LINE][100] = {"[1.A]---(1) No Support",
							        "",
							        "","","","","",""};

char CLIADMIN_POWER_2_A_1[CLI_LINE][100] = {"[2.A]---(1) 0.00 W : 0.00 VA",
							        "",
							        "","","","","",""};

char CLIADMIN_POWER[CLI_LINE][100] = {"[1]---23.05 W : 0.00 VA",
							           "[1]---(L1) 23.20 W : 59.30 VA",
							           "[1]---(A) 22.60 W : 57.10 VA (B) 0.00 W : 0.00 VA",
									   "[1.A]---(1) No Support(2) No Support(3) No Support(4) No Support(5)",
									   "[2]---0.00 W : 0.00 VA",
									   "[2]---(L1) 0.00 W : 0.00 VA",
									   "[3]---10.00 W : 0.00 VA",
									   "[3]---(L1) 0.00 W : 0.00 VA"};					
									
									
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
		sprintf(a8tmp, "%s%c%c",SEND_CMD[i],PDUCB_CLI_CTRL_CHAR_CR,PDUCB_CLI_CTRL_CHAR_LF);
        strcat(p8ptr, a8tmp);
	}
    sprintf(a8tmp, "%c%c", PDUCB_CLI_CTRL_CHAR_CR,PDUCB_CLI_CTRL_CHAR_LF);
    strcat(p8ptr, a8tmp);
}						
									


typedef struct _PDU_DATA_PACKAGE
{
    UINT16 u16BufferSize;
    UINT16 u16RespLen;
    UINT8 au8Buffer[];
} *pPDU_DATA_PACKAGE;


typedef struct  
{
    UINT8 receptacle:8;
    UINT8 branch:4;
    UINT8 pdu:3;
} *pPDU_P2_Format;

#define CLISETRCPTSTATE_BUFFER 1000

char* trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

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

int genpowercmd()
{
    char powerstr[500]={0};
    aPDU_POWER mypdu;	
	UINT16 u16Parameter2;
	UINT16 u16MsgLength;
	pPDU_P2_Format pPDU_which_recp = (pPDU_P2_Format)&u16Parameter2;
	UINT8 au8tmp[10];
	UINT8 auKey[10]={0};
	UINT8 data_buf[ CLISETRCPTSTATE_BUFFER + 4 ] = {0};
    pPDU_DATA_PACKAGE pPDU_SENSOR_BUFFER = (pPDU_DATA_PACKAGE) data_buf; 
	
    u16Parameter2=DEF_P2;
    _DEBUG(2 ,"u16Parameter2 = 0x%04x\n", u16Parameter2);

    sprintf(&pPDU_SENSOR_BUFFER->au8Buffer[1], "%s", PDUCB_CLI_PWRCONSUMP_CMD);
    if (0 == (u16Parameter2&0x7FFF))
    {   
        /*Get total PDU power*/
    }
    else
    {
        if (0 == pPDU_which_recp->pdu)
        {
            _DEBUG(0, "return RAW_DEVICE_NACK\n");
            return RAW_DEVICE_NACK;
        }
        sprintf((char *)auKey," %d",pPDU_which_recp->pdu);
        if (0 != pPDU_which_recp->branch)
        {
            sprintf((char *)au8tmp,".%c",((pPDU_which_recp->branch) + 0x40));
            strcat((char *)auKey, (char *)au8tmp);
        }
        else if (0 != pPDU_which_recp->receptacle)
        {
                _DEBUG(0, "return RAW_DEVICE_NACK\n");
                return RAW_DEVICE_NACK;    
        }
        if (0 != pPDU_which_recp->receptacle)
        {
            sprintf( (char *)au8tmp,".%d", pPDU_which_recp->receptacle);
            strcat( (char *)auKey, (char *)au8tmp);
        }    
        strcat( (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1], (char *)auKey);
    }
    _DEBUG(2, "COMMAND is : %s \n key is %s \n", (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1], auKey);
    u16MsgLength = strlen( (char *)&pPDU_SENSOR_BUFFER->au8Buffer[1]) + 1;     
    
    
    prepare_string (powerstr);
    printf("%s",powerstr);
	PDUCLI_AdminGetPowerByKey(powerstr, auKey, &mypdu);
    //PDUCLI_AdminGetPowerByKey(powerstr, TEST_KEY, &mypdu);
}
RAWSTATUS PDUCLI_AdminGetPowerByKey(const char* string_data, const char* key, paPDU_POWER PDU_POWER)
{
    char acRealkey[10];
    char acTmp[10];
    char acBuffer[100];
    UINT8 *pu8KeyPtr;
    UINT8 *pu8DataPtr;
    UINT8 *pu8DataStartPtr;
    UINT8 *pu8DataEndPtr;

    pu8KeyPtr = trimwhitespace((char*) key);
    strncpy( acTmp, pu8KeyPtr, 10);
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

    pu8DataPtr = (UINT8 *)strstr(acBuffer, PDUCB_CLI_ADMINCMD_NOSUPPORT_STR);
    if(pu8DataPtr != NULL)
    {
        _DEBUG(0, "Device not support\n");
        return RAW_DEVICE_NOT_SUPPORT;
    }
    printf ("buff is %s\n",acBuffer);
	/* Get Watt point */
    pu8DataPtr = strstr (acBuffer,".");
    
	pu8DataStartPtr = pu8DataPtr;
	pu8DataEndPtr = pu8DataPtr;
    while (isdigit(*(pu8DataStartPtr - 1))) 
    {
       if ((char*)pu8DataStartPtr == acBuffer)
            break;
        pu8DataStartPtr--;
    }
    
	while (isdigit(*(pu8DataEndPtr + 1))) 
    {
        pu8DataEndPtr++;
    }
    pu8DataEndPtr++;	
    memcpy(PDU_POWER->WATT, pu8DataStartPtr, (pu8DataEndPtr-pu8DataStartPtr));
    PDU_POWER->WATT[(pu8DataEndPtr-pu8DataStartPtr)]=0;
    _DEBUG(2, "PDU_POWER->WATT = %s\n", PDU_POWER->WATT);

	/* Get VA point */
    pu8DataPtr = strstr (pu8DataPtr+1,".");
    
	pu8DataStartPtr = pu8DataPtr;
	pu8DataEndPtr = pu8DataPtr;
    while (isdigit(*(pu8DataStartPtr - 1))) 
    {
       if ((char*)pu8DataStartPtr == acBuffer)
            break;
        pu8DataStartPtr--;
    }
    
	while (isdigit(*(pu8DataEndPtr + 1))) 
    {
        pu8DataEndPtr++;
    }
    pu8DataEndPtr++;	
    memcpy(PDU_POWER->VA, pu8DataStartPtr, (pu8DataEndPtr-pu8DataStartPtr));
    PDU_POWER->VA[(pu8DataEndPtr-pu8DataStartPtr)]=0;
    _DEBUG(2, "PDU_POWER->VA = %s\n", PDU_POWER->VA);
		
    return RAW_OK;
}

void parsing_power_string()
{
  char powerstr[500]={0};
  aPDU_POWER mypdu;

  prepare_string (powerstr);
  
  
  printf("%s",powerstr);
  
  PDUCLI_AdminGetPowerByKey(powerstr, TEST_KEY, &mypdu);
  
}

void get_total_power()
{
  char powerstr[500]={0};
  aPDU_POWER mypdu;
  UINT16 u16Parameter2=0;
  char pReadData[30];
  prepare_string (powerstr);  
  printf("%s",powerstr);    

  memset(mypdu.WATT,0,sizeof(mypdu.WATT));
  memset(mypdu.VA,0,sizeof(mypdu.WATT));
  
    if (0 == (u16Parameter2&0x7FFF))
    {   
        /*Get total PDU power*/
        float fWATT=0.0;
        float fVA=0.0;
        UINT8 u8pdu;
        for ( u8pdu = 1; u8pdu <= PDUCB_MAX_ARRAYSIZE; u8pdu++ )
        {
            char au8key[5]={0};
            sprintf(au8key, "%d", u8pdu);
            if (RAW_OK != PDUCLI_AdminGetPowerByKey((char *)powerstr, au8key, &mypdu))
            {
                break;
            }
            fWATT += atof(mypdu.WATT);
            fVA += atof(mypdu.VA);
        }  
        sprintf(pReadData, "%02.2lf", fWATT);
    }   
  
}
#if 0
int main ()
{
  //receptaclestate();
  //genpowercmd();
  //parsing_power_string();
  get_total_power();
  
  return 0;
}
#endif

#define CLI_ADMIN_KEY_MAXIMUM 30 
RAWSTATUS PDUCLI_AdminGetValueByKey(const char* string_data, const char* key, char* value, UINT16 value_buff_size)
{
    UINT8 acKey[CLI_ADMIN_KEY_MAXIMUM + 2];
    UINT8 u8KeyLength;
    UINT8 *pu8KeyPtr = NULL;
    UINT8 *pu8DataPtr = NULL;
    UINT8 *pu8DataPtr_tmp = NULL;

    pu8KeyPtr = trimwhitespace((char*) key);
    // 1. check key length
    u8KeyLength = strlen (pu8KeyPtr);
    if ( u8KeyLength > CLI_ADMIN_KEY_MAXIMUM )
    {
        _DEBUG(0, "Key too long\n");
        return RAW_BUSY;
    }
    
    // 2. make key 
    acKey[0] = PDUCB_CLI_CTRL_CHAR_CR;
    acKey[1] = PDUCB_CLI_CTRL_CHAR_LF;
    strcpy( &acKey[2], pu8KeyPtr);
    
    // 3. find key in string
    pu8DataPtr = strstr (string_data, acKey);
    if ( NULL == pu8DataPtr)
    {
        _DEBUG(0, "cannot find key \n");
        return RAW_FAIL;
    }

    // 4. shift point to value start
    pu8DataPtr = (pu8DataPtr + u8KeyLength + 2);
    pu8DataPtr = strstr((char*) pu8DataPtr, "-");
    while ( *pu8DataPtr == PDUCB_CLI_CHAR_ENDASH )
    {
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




int main ()
{
  int AAA=0;
  pPDU_P2_Format PPP = &AAA;
  PPP->receptacle = 7;
  PPP->pdu = 2;
  PPP->branch = 1;
  printf ("0x%02x\n", AAA);
  return 0;
}
