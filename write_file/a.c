#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/file.h>


#define fifoFile "/home/dollar/20160621"

int main (int argc, char *argv[])
{
	int fifoFd = 0, totalLen = 0, len = 0, res = 0;
	char tmp_string[500];
	char *wPtr = NULL;
    /* Write event to FIFO */
    fifoFd = open(fifoFile, O_WRONLY | O_NONBLOCK, 0);
    if(fifoFd < 0)
    {
        printf("Cannot open event fifo file[%s] ERROR= %s \n", fifoFile, strerror(errno));
        return -1;
    }
    sprintf(tmp_string,"hello this test string \n My name is Dollar");
    wPtr = (u_int8_t*)tmp_string;
    totalLen = strlen(tmp_string)+1;	
    while(totalLen)
    {
        if((len = write(fifoFd, wPtr, totalLen)) < 0)
        {
            printf("Cannot write to fifo file[%s] ERROR= %s \n", fifoFile, strerror(errno));
            res = -1;
            break;
        }
        totalLen -= len;
        wPtr += len;
    }	
	close(fifoFd);
	return res;
}

