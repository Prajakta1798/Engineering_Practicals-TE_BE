/*
Program By:
Assignment No:7(b)
Pipes : FIFOs: Full duplex communication between two independent processes. First process accepts
sentences and writes on one pipe to be read by second process and second process counts
number of characters, number of words and number of lines in accepted sentences, writes this
output in a text file and writes the contents of the file on second pipe to be read by first process
and displays on standard output.*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "fifo1"
#define FIFO_NAME1 "fifo2"

int main(void)
{
    char s[300]="this is mohini from te it\n MCOERC\n eklahare nashik"; 
		char s1[300];
    int num, fd,fd1;
		 mkfifo(FIFO_NAME, 0666
    printf("THIS IS FIRST PROCESS\n");
    fd = open(FIFO_NAME,O_WRONLY);
    printf("Sent some sentences to Second Process using FIFO\n");

	write(fd,s,strlen(s));
	 mkfifo(FIFO_NAME1, 0666);

    //fd1 = open(FIFO_NAME1, O_RDONLY);
 fd1 = open(FIFO_NAME1, O_RDONLY);
        if ((num = read(fd1, s1, 300)) == -1)
 {
	printf("error read");
	exit(0);
}
        else {
            s1[num] = '\0';
            printf("Result of Second Process is shown by First Process by using FIFO===>\n \"%s\"\n", s1);
        }
    return 0;
}

