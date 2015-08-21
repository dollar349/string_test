

typedef struct 
{
    char WATT[10];
    char VA[10];        
}aPDU_POWER, *paPDU_POWER;

#define PDUCB_MAX_ARRAYSIZE 4
#define PDUCB_MAX_BRANCHSIZE 7
#define PDUCB_MAX_RCPTSIZE 18
#define PDUCB_BUFF_SIZE 2048

/* Definition for PDU CLI command */
#define PDUCB_CLI_ADMIN_MODE 0x00
#define PDUCB_CLI_APPLIANCE_MODE 0x01

#define PDUCB_CLI_ADMINCMD_ERROR_STR "Error"
#define PDUCB_CLI_ADMINCMD_NOSUPPORT_STR "No Support"
#define PDUCB_CLI_CTRL_CHAR_STX 0x02
#define PDUCB_CLI_CTRL_CHAR_ETX 0x03
#define PDUCB_CLI_CTRL_CHAR_RS 0x1E
#define PDUCB_CLI_CTRL_CHAR_US 0x1F
#define PDUCB_CLI_CTRL_CHAR_NAK 0x15
#define PDUCB_CLI_CTRL_CHAR_ACK 0x06
#define PDUCB_CLI_CTRL_CHAR_LF 0x0A
#define PDUCB_CLI_CTRL_CHAR_CR 0x0D
#define PDUCB_CLI_CHAR_ENDASH 0x2D

#define LIBPDUCB_DEBUG
#ifdef LIBPDUCB_DEBUG
/*
 * The level define:
 * 0: Print key data
 * 1: Debug
 * 2: Trace
 */
    #define LIBPDUCB_DEBUG_LEVEL 2
    #define _DEBUG(level, fmt, args...)                                      \
    do{                                                                      \
        if(level <= LIBPDUCB_DEBUG_LEVEL)                                    \
            printf("%s:%s:%d: "fmt,__FILE__,__FUNCTION__,__LINE__, ## args); \
    }while(0)
#else
    #define _DEBUG(level, fmt, args...)
#endif /* #ifdef LIBPDUCB_DEBUG */

typedef enum
{
    /** Common status OK. */
    RAW_OK = 0,      
    
    /** Common status failed. */
    RAW_FAIL,
    
    /** Common status busy. */
    RAW_BUSY,

    /** No device or device error. */
    RAW_DEVICE_NACK,

    /** device not supoort this feature. */
    RAW_DEVICE_NOT_SUPPORT,

    /** Arbitration Lost. */
    RAW_DEVICE_AL,

    /** Driver section. */
    RAW_DRIVER_BEGIN = 200,

    /** Channel Common Section. */
    RAW_CHANNEL_BEGIN = 300,

    /** IPMB Channel Section. */
    RAW_IPMB_CHANNEL_BEGIN = 400,

    /** KCS Channel Section. */
    RAW_KCS_CHANNEL_BEGIN = 500,

    /** LAN Channel Section. */
    RAW_LAN_CHANNEL_BEGIN = 600,

    /** UART Channel Section. */
    RAW_UART_CHANNEL_BEGIN = 600

    /* Misc Channel Section. */

    /* append your section from here. */
} RAWSTATUS;

#ifndef INT8
typedef char                INT8;   /**< type redefine INT8  */
typedef short int           INT16;  /**< type redefine INT16 */
typedef long int            INT32;  /**< type redefine INT32 */

typedef unsigned char       UINT8;  /**< type redefine UINT8  */
typedef unsigned short int  UINT16; /**< type redefine UINT16 */
typedef unsigned long int   UINT32; /**< type redefine UINT32 */
#endif



RAWSTATUS PDUCLI_AdminGetValueByKey(const char* string_data, const char* key, char* value, UINT16 value_buff_size);
RAWSTATUS PDUCLI_AdminGetPowerByKey(const char* string_data, const char* key, paPDU_POWER PDU_POWER);



