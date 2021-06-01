/*
Program By:
Assignment No:8(b)
Inter-process Communication using Shared Memory using System V. Application to
demonstrate: Client and Server Programs in which server process creates a shared memory segment and
writes the message to the shared memory segment. Client process reads the message from the shared
memory segment and displays it to the screen.*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE     27
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main()
{
    int shmid;
    key_t key;
    char *shm, *s;
 
    key = 7678;
 
    if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)
        die("shmget");
 
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        die("shmat");
 
    //Now read what the server put in the memory.
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');
 
    /*
     *Change the first character of the
     *segment to '*', indicating we have read
     *the segment.
     */
    *shm = '*';
 
    exit(0);
}
