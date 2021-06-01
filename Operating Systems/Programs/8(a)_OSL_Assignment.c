/*
Program By:
Assignment No:8(a)
Inter-process Communication using Shared Memory using System V. Application to
demonstrate: Client and Server Programs in which server process creates a shared memory segment and
writes the message to the shared memory segment. Client process reads the message from the shared
memory segment and displays it to the screen.*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
 
#define MAXSIZE     27
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main()
{
    char c[10]={'i','n','d','i','a'};
    int shmid,i;
    key_t key;
    char *shm, *s;
 
    key = 7678;
 
    if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
        die("shmget");
 
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        die("shmat");
 
    /*
     *      * Put some things into the memory for the
     *        other process to read.
     *        */
    s = shm;  
for (i=0;i<=9;i++)
        *s++ = c[i];
 
 
    /*
     * Wait until the other process
     * changes the first character of our memory
     * to '*', indicating that it has read what
     * we put there.
     */
    while (*shm != '*')
        sleep(1);
 
   exit(0);
}
