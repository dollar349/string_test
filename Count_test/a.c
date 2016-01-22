#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>


/**
 * Common functions
 */
#define INTEGER_BASE_FOR_SECOND_DECIMAL_POINT (100) 
#define ROUND_FOR_SECOND_DECIMAL_POINT (INTEGER_BASE_FOR_SECOND_DECIMAL_POINT / 2)
#define INTEGER_BASE_FOR_FIRSR_DECIMAL_POINT (10)
#define ROUND_FOR_FOR_FIRSR_DECIMAL_POINT (INTEGER_BASE_FOR_FIRSR_DECIMAL_POINT / 2)
/* CelsiusToFahrenheit 
 * 
 * Parameter
 *     vCelsius : (vCelsius unit is 0.01 celsius)
 * Retun value : value of Fahrenheit (the value has been rounded up)
 *
 */
int32_t CelsiusToFahrenheit(int32_t vCelsius) 
{
   return (((vCelsius*9 + 2/*for rounding*/) / 5) + ROUND_FOR_SECOND_DECIMAL_POINT ) /
   INTEGER_BASE_FOR_SECOND_DECIMAL_POINT + 32;
}

/* FahrenheitToCelsius 
 * 
 * Parameter
 *     vFahrenheit : (vFahrenheit unit is 1 Fahrenheit)
 * Retun value : value of Celsius (unit is 0.01 celsius)
 *
 */
int32_t FahrenheitToCelsius(int32_t vFahrenheit) 
{
   return ( ((vFahrenheit-32)*INTEGER_BASE_FOR_SECOND_DECIMAL_POINT*5) +4/*for rounding*/ )/ 9 ;
}

/* UnitCelsiusToFahrenheit 
 * 
 * Parameter
 *     vCelsius : (vCelsius unit is 0.01 celsius)
 * Retun value : value of Fahrenheit(unit is 0.1 Fahrenheit) (the value has been rounded up)
 *
 */
int32_t UnitCelsiusToFahrenheit(int32_t vCelsius) 
{
   return (((vCelsius*9 + 2/*for rounding*/) / 5) + ROUND_FOR_FOR_FIRSR_DECIMAL_POINT) / 
   INTEGER_BASE_FOR_FIRSR_DECIMAL_POINT ;
}

/* UnitFahrenheitToCelsius 
 * 
 * Parameter
 *     vFahrenheit : (vFahrenheit unit is 0.1 Fahrenheit)
 * Retun value : value of Celsius (unit is 0.01 celsius)
 *
 */
int32_t UnitFahrenheitToCelsius(int32_t vFahrenheit) 
{
   return ( ((vFahrenheit)*INTEGER_BASE_FOR_FIRSR_DECIMAL_POINT*5) +4/*for rounding*/ )/ 9 ;
}


int testfloat(char* ttt)
{
	float a = atof(ttt);
	return (int) (a * 100);
}

int teststrtok(char* ttt)
{
	char * pch;
	char * pch2;
	char ctmp[6];
	strcpy(ctmp,ttt);
	pch = strtok (ctmp,".");
	pch2 = strtok (NULL,".");
	return (atoi(pch)*100) + atoi(pch2);
}

int testforloop(char* ttt)
{
	
}

atoi_multiply_precision(char *strValue, u_int16_t precisionVal)
{
    char tmpValue[32];
    u_int16_t i, j, strLen;

    snprintf(tmpValue, sizeof(tmpValue), "%s", strValue);

    /* If decimal point found, move the decimal point right <precisionVal> digits.
     * If not found, append character '0' to the string. */
    if ( precisionVal > 0 ) {
        /* Seek for decimal point */
        for (i = 0; i < strlen(tmpValue); i++) {
            if ('.' == tmpValue[i])
                break;
        }
        /* Decimal point not found */
        if ( i == strlen(tmpValue) ) {
            /* string size check */
            if ( (i + precisionVal) < sizeof(tmpValue) -1 ) {
                j = i;
                /* The number multiply (10*precisionVal) */
                while (precisionVal--) {
                    tmpValue[j++] = '0';
                }
                tmpValue[j] = '\0';
            }
        }
        else {
            /* string size check */
            if ( (i + precisionVal) < sizeof(tmpValue) -1 ) {
                j = i;
                strLen = strlen(tmpValue);
                while (precisionVal--) {
                    tmpValue[j] = ( j < strLen -1 ) ? tmpValue[j+1] : '0';
                    j++;
                }
                tmpValue[j] = ( j < strLen -1 ) ? '.' : '\0';
            }
        }
    }
    return (int16_t)(atoi(tmpValue));
}


int main (int argc, char *argv[])
{
	char test_Srt[]="37.73";
    int idata;
	int count=10000;
    struct timeval start, end;
    gettimeofday( &start, NULL );
	while (count--){
    //idata = testfloat(test_Srt);
	idata = atoi_multiply_precision(test_Srt,2);
	}
    gettimeofday( &end, NULL );
    int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
    printf("time: %d us\n idata = %d \n", timeuse, idata);
 
    return 0;
}

