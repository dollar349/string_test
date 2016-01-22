#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>



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

