
/*Ass no:04
Title: Thread synchronization using counting semaphores. Application to demonstrate:
producer-consumer problem with counting semaphores and mutex.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>	//shared memory facility
#include <sys/stat.h>
#include <string.h>

 
#define NITERS 5
void *producer(void *argp);	//prdoucer function
void *consumer(void *argc);	//consumer function

typedef struct
{
	int buff;
	sem_t full, empty;		//sem_t datatype or class of semphore for creating semphore thread. 
}
Shared;

Shared Sh;

int main()
{
	pthread_t ptid,ctid;		//for storing thread id

	sem_init(&Sh.empty,0,1);	//for inintializing semphore first parameter for address pointer for semphore second parameter for 						//semphore is shared between threads of process or between processes, third parameter for initial 						//value. 

	sem_init(&Sh.full,0,0); 	//same as empty

	pthread_create(&ptid,NULL,producer,NULL); 	//create thread for producer and pass null attributes for that

	pthread_create(&ctid,NULL,consumer,NULL); 	//create thread for consumer and pass null attributes for that

	pthread_join(ptid,NULL); 			//wait for terminating other thread

	pthread_join(ctid,NULL); 			//wait for terminating other thread
	return 0;
}


void *producer(void *argp)
{
	int i,item;

	for(i=0;i<NITERS;i++)
	{
		item=i;
	 	printf("produced %d \n",item);

		sem_wait(&Sh.empty);			//Lock the buffer
		
		Sh.buff=item;				//Insert the item in buffer

		sem_post(&Sh.full);			//Unlock the buffer
	}

	return NULL;
}

void *consumer(void *argc)
{

	int i,item;

	for(i=0;i<NITERS;i++)
	{
		sem_wait(&Sh.full);			//Lock the buffer
		
		item=Sh.buff;				//Consume the item from buffer
		
		sem_post(&Sh.empty);			//Unlock the buffer
		
		printf("Consumed %d\n ",item);
	}
  return NULL;
}

/* outpot
mcoerc@IT-SL-3-14:~/Desktop$ cc -c prod_cons.c
mcoerc@IT-SL-3-14:~/Desktop$ cc -pthread -o prod_cons prod_cons.c
mcoerc@IT-SL-3-14:~/Desktop$ ./prod_cons
produced 0 
produced 1 
produced 2 
Consumed 0
 Consumed 1
 Consumed 2
 produced 3 
produced 4 
Consumed 3
 Consumed 4

*/

