#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define int32_t int
#define int16_t short int
#define u_int16_t unsigned short int

int16_t atoi_multiply_precision(char *strValue, u_int16_t precisionVal)
{
    char *dotPos;
    int16_t res;
    u_int16_t strLen = strlen(strValue);
    char *tmpStr = malloc(strLen);
    if(tmpStr == NULL)
    {
        return -1;
    }

    memset(tmpStr, 0x0, strLen);
    strncpy(tmpStr, strValue, strLen);

    dotPos = strchr(tmpStr, '.');
    if(dotPos == NULL)
    {
        //Input is a integer
        res = (int16_t)(atoi(tmpStr) * precisionVal);
    }
    else
    {
        //Input is a float
        if((strchr((dotPos+1), '.') != NULL))
        {
            //String format error
            free(tmpStr);
            return -1;
        }

        dotPos[0] = '\0';
        dotPos++;
        printf("Integer part = %d, dot part = %d\n", atoi(tmpStr), atoi(dotPos));
        res = (int16_t)((atoi(tmpStr) * precisionVal) + atoi(dotPos));
    }

    free(tmpStr);
    return res;
}

int32_t itoa_divide_precision(char *targetValue, int32_t maxHStrLen, int16_t tempCalibration, u_int16_t precisionVal)
{
    /* Positive number skip sign character */
    if(precisionVal == 0)
    {
        return -1;
    }

    if (tempCalibration >= 0)
    {
        snprintf(targetValue, maxHStrLen, "%d.%d", tempCalibration/precisionVal, tempCalibration%precisionVal);
    }
    else
    {
        snprintf(targetValue, maxHStrLen, "-%d.%d", (-tempCalibration)/precisionVal, (-tempCalibration)%precisionVal);
    }

    return 0;
}


int main (int argc, char *argv[])
{
	unsigned int Fahrenheit, Celsius, Celsius2, Fahrenheit2;
	int aflag=0, bflag=0, cflag=0;
	int ch;
        char TempStr[100] = { 0 };
	while ((ch = getopt(argc, argv, "f:F:c:C:m:M:S:s:")) != -1)
	{
		switch (ch) {
                        case 'S':
                        Celsius = atoi(optarg);
                        itoa_divide_precision(TempStr, 100, (int16_t)Celsius, 100);
                        printf("Temp: int to str = %s\n", TempStr);
                        break;

                        case 's':
printf("%s\n", optarg);
                        printf("Temp: str to int = %d\n", atoi_multiply_precision(optarg, 100));
                        break;

			case 'c':
			Celsius = atoi(optarg);
//			printf("UnitCelsiusToFahrenheit = %d\n", UnitCelsiusToFahrenheit(Celsius));
//			break;
			
			case 'C':
			Celsius = atoi(optarg);
//			printf("CelsiusToFahrenheit = %d\n", CelsiusToFahrenheit(Celsius));
//			break;
			
			case 'f':
			Fahrenheit = atoi(optarg);
//			printf("UnitFahrenheitToCelsius = %d\n", UnitFahrenheitToCelsius(Fahrenheit));
//			break;	
			
			case 'F':
			Fahrenheit = atoi(optarg);
//			printf("FahrenheitToCelsius = %d\n", FahrenheitToCelsius(Fahrenheit));			
			
			case 'M':
			Celsius = atoi(optarg);
			Celsius = ((Celsius +5 )/10) *10;
			printf("Celsius = %d\n", Celsius);

			case 'm':
			Celsius = atoi(optarg);			
			
			break;
			case '?':
			printf("Unknown option: %c\n",(char)optopt);
			break;
		}
	}
    return 0;
}

