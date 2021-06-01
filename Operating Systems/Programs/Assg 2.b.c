#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void quicksort(int[10],int,int);
void main()
{
  int pid,ppid,a[5],size,i=0,j=0,status;
  char *argv[12];
  for(i=0;i<12;i++)
   {
    argv[i]=(char *)malloc(20);
   }
  printf("\n\nTHE main of the parent process\n My process id is %d",getpid());
  printf("\nEnter the size of array");
  scanf("%d",&size);
  printf("Size =%d",size);
  printf("\nEnter elements");
  for(j=0;j<size;j++)
   {
      scanf("%d",&a[j]);
     // printf("\n%d",j);
   }
  quicksort(a,0,size-1);
  printf("\n sorted element:");
  for(i=0;i<size;i++)
  printf("\n%d",a[i]);
  printf("\nPARENT:I am calling my child for searching now\n");
  printf("----------------------------------------");
  pid=fork();
  if(pid==0)
  {
  printf("\nCHILD:IN Child process My process-id is %d\n",getpid());
  printf("\nCHILD:my parents process-id is %d \n\n",getppid());
  printf("\nCHILD:Calling searching prgram using execv now.I will be overlayed!\n");
  for(i=0;i<size;i++)
      
      sprintf(argv[i+1],"%d",a[i]);
      argv[0]="./b_binarysearch";
      argv[size+2]=NULL;
      execv("./b_binarysearch",argv);
      printf("\nERROR");
      printf("\nCHILD:I am dying now\n");
      printf("----------------------------------\n\n");
   }
  else if(pid>0){
   wait(0);
   printf("\nPARENT:I am dying now\n");
   printf("\n-----------------------------------\n\n");
  }
}
void quicksort(int a[10],int first,int last)
{
  int pivot,i,temp,j;
  if(first<last){
   pivot=first;
   i=first;
   j=last;
  while(i<j){
   while(a[i]<=a[pivot]&&i<last)
      i++;
   while(a[j]>a[pivot])
     j--;
   if(i<j){
      temp=a[i];
      a[i]=a[j];
      a[j]=temp;
    }
}
  temp=a[pivot];
  a[pivot]=a[j];
  a[j]=temp;
  quicksort(a,first,j-1);
  quicksort(a,j+1,last);
}
}

   
