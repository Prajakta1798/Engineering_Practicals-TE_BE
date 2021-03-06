/*Ass no:06
Title: Deadlock Avoidance Using Semaphores: Implement the deadlock-free solution to Dining
Philosophers problem to illustrate the problem of deadlock and/or starvation that can occur when many
synchronized threads are competing for limited resources.*/


#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
 
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N
 
sem_t mutex;
sem_t S[N];
 
void * philospher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);
 
int state[N];
int phil_num[N]={0,1,2,3,4};
 
int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("Philosopher %d is thinkingn",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
 
void *philospher(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}
 
void take_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = HUNGRY;
    printf("\nPhilosopher %d is Hungryn",ph_num+1);
    test(ph_num);
    sem_post(&mutex);
    sem_wait(&S[ph_num]);
    sleep(1);
}
 
void test(int ph_num)
{
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[ph_num] = EATING;
        sleep(2);
        printf("\nPhilosopher %d takes fork %d and %dn",ph_num+1,LEFT+1,ph_num+1);
        printf("\nPhilosopher %d is Eatingn",ph_num+1);
        sem_post(&S[ph_num]);
    }
}
 
void put_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("\nPhilosopher %d putting fork %d and %d downn",ph_num+1,LEFT+1,ph_num+1);
    printf("\nPhilosopher %d is thinkingn",ph_num+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

/*------------------------OUTPUT----------------------------------------------

itcl118@itcl118-ThinkCentre-A58:~/Desktop$ gcc -pthread -o archana dining.c
dining.c: In function ???philospher???:
dining.c:44:9: warning: implicit declaration of function ???sleep??? [-Wimplicit-function-declaration]
         sleep(1);
         ^
itcl118@itcl118-ThinkCentre-A58:~/Desktop$ ./archana
Philosopher 1 is thinkingnPhilosopher 2 is thinkingnPhilosopher 3 is thinkingnPhilosopher 4 is thinkingnPhilosopher 5 is thinkingn
Philosopher 1 is Hungryn
Philosopher 1 takes fork 5 and 1n
Philosopher 1 is Eatingn
Philosopher 2 is Hungryn
Philosopher 4 is Hungryn
Philosopher 4 takes fork 3 and 4n
Philosopher 4 is Eatingn
Philosopher 3 is Hungryn
Philosopher 5 is Hungryn
Philosopher 1 putting fork 5 and 1 downn
*/
