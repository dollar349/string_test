#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>


int main (int argc, char *argv[])
{
    const char *input = "/etc/obmc-console/server.ttyEcho.conf";

    //const char *format = "XFR 3 NS %15[0-9.]:%5[0-9]";
    const char *format = "/etc/obmc-console/server.%[^.]";
    char name[16] = { 0 }; 


    if(sscanf(input, format, name ) != 1)
        printf("parsing failed\n");
    else printf("name = %s\n", name);

    return 0;
}

