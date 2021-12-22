#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>



typedef struct _VendorOption { 
    unsigned char opt_num;
    unsigned char opt_value_len;
    unsigned char opt_value[];
} VendorOption;

int main (int argc, char *argv[])
{
    char vendor_string[255]={0};
    char temp_str[255];
    unsigned char vendor_data[] = {0x01,0x04,0xc0,0xa8,0x0a,0x63,0x02,0x19,0x2a,0x2e,0x52,0x4d,0x78,0x2e,0x69,0x6e,0x74,0x65,0x72,0x62,0x6f,0x78,0x2e,0x76,0x65,0x72,0x74,0x69,0x76,0x2e,0x63,0x6f,0x6d};
    int vendor_data_len = sizeof(vendor_data);
    int Pos=0;

    for ( Pos = 0; Pos < vendor_data_len;  ){
            VendorOption *p_opt43 = vendor_data + Pos;
            switch (p_opt43->opt_num) 
            {
                    case 1:
                        /* ADX IP Address */
                        sprintf(vendor_string,"%sVERTIV_SIP_ADDRESS=%d.%d.%d.%d\n", vendor_string,
                                p_opt43->opt_value[0],
                                p_opt43->opt_value[1],
                                p_opt43->opt_value[2],
                                p_opt43->opt_value[3]);
                    break;
                    case 2:
                        /* ADX Server name */
                        strncpy(temp_str, p_opt43->opt_value, p_opt43->opt_value_len);
                        temp_str[p_opt43->opt_value_len]='\0';
                        sprintf(vendor_string,"%sVERTIV_SIP_DOMAIN=%s\n", vendor_string, temp_str);
                    break;
                    default:
                    printf("default\n");
                    break;
            }
            Pos = Pos + sizeof(p_opt43->opt_num) + sizeof(p_opt43->opt_value_len) + p_opt43->opt_value_len;
    }

    printf("%s",vendor_string);
}



