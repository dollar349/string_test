#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


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




int main (int argc, char *argv[])
{
	unsigned int Fahrenheit, Celsius, Celsius2, Fahrenheit2;
	int aflag=0, bflag=0, cflag=0;
	int ch;
	while ((ch = getopt(argc, argv, "f:F:c:C:m:M:")) != -1)
	{
		switch (ch) {
			case 'c':
			Celsius = atoi(optarg);
			printf("UnitCelsiusToFahrenheit = %d\n", UnitCelsiusToFahrenheit(Celsius));
			break;
			
			case 'C':
			Celsius = atoi(optarg);
			printf("CelsiusToFahrenheit = %d\n", CelsiusToFahrenheit(Celsius));
			break;
			
			case 'f':
			Fahrenheit = atoi(optarg);
			printf("UnitFahrenheitToCelsius = %d\n", UnitFahrenheitToCelsius(Fahrenheit));
			break;	
			
			case 'F':
			Fahrenheit = atoi(optarg);
			printf("FahrenheitToCelsius = %d\n", FahrenheitToCelsius(Fahrenheit));			
			
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

