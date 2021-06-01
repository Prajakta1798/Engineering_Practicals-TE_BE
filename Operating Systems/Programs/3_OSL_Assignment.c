/*Program By:-
Assignment No:-3
Thread management using pthread library.
Implement matrix multiplication using multithreading. Application should have pthread_create, pthread_join, pthread_exit. In the program, every thread must return the value and must be collected in pthread_join in the main function. Final sum of row-column multiplication must be done by main thread (main function).*/
//--------------------------------------------------------------------------------------------------------------------------------------

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define M 3
#define K 2
#define N 3
#define NUM_THREADS 10

int A[M][K]={{1,4},{2,5},{3,6}};
int B[K][N]={{8,7,6},{5,4,3}};
int C[M][N];

struct v{
  int i;//row
  int j;//column
};

void *runner(void *param); /*the thread*/

int main(int argc,char *argv[]){

int i,j,count=0;
for(i=0;i<M;i++){
 for(j=0;j<N;j++){
//Assign a row and column for each thread
struct v *
data=(struct v *)malloc(sizeof(struct v));
data->i=i;
data->j=j;
/*Now create the thread passing it data as a parameter*/
pthread_t tid;//Thread ID
pthread_attr_t attr;//set of thread attributes

//Get the default attributes
pthread_attr_init(&attr);

//Create the thread
pthread_create(&tid,&attr,runner,data);

//Make sure the parent waits for all thread to complete
pthread_join(tid,NULL);
//count++;
}
}
//print out resulting matrix
for(i=0;i<M;i++)
{
for(j=0;j<N;j++)
{
printf("\t");
printf("%d",C[i][j]);
}
printf("\n");
}
}
//the thread will begin control in this function
void *runner(void *param){
struct v *data=param;//the structure that holds our data
int n,sum=0;//the counter and sum

//Row multiplied by column
for(n=0;n<K;n++)
{
   sum+=A[data->i][n]*B[n][data->j];
}

//assign the sum to its coordinate
C[data->i][data->j]=sum;

//Exit the thread
pthread_exit(0);
}
/**********OUTPUT******************
mcoer@Mcoer:~$ gcc -c ass2.c
mcoer@Mcoer:~$ gcc -pthread -o ass2 ass2.c
mcoer@Mcoer:~$ ./ass2
	28	23	18
	41	34	27
	54	45	36
*/
