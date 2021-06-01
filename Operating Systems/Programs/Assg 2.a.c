#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void mergeSort(int arr[],int low,int mid,int high);
void partition(int arr[],int low,int high);
void quicksort(int [10],int,int);

void main()
{
   int pid,ppid,a[10],size,i;
   printf("\nPARENT:My process-id is %d",getpid());
   printf("\n\nEnter the Number of element in array:");
   scanf("%d",&size);
   printf("\nEnter the %d element:",size);
   for(i=0;i<size;i++)
      scanf("%d",&a[i]);
   printf("\nFORKING NOW!");
   pid=fork();
   if(pid==0){
    printf("\nCHILD:My process id is %d.",getpid());
    printf("\nCHILD:My parents Process id is %d",getppid());
    quicksort(a,0,size-1);
    printf("\nSORTED ELEMENTS:");
    for(i=0;i<size;i++)
      printf("\n%d",a[i]);
    printf("\n--------------------------------------------------");
   //ORPHAN
    printf("\nCHILD:I am sleeping now.");
    sleep(5);
    printf("\n--------------------------------------------------");
    system("ps -A -H|grep a.out");
   /* //ZOMBIE
    printf("\nCHILD:I am Dying now");
    printf("\n--------------------------------------------------");
    system("ps -A -H|grep a.out");*/
   }
    else if(pid>0){
       system("wait");
       printf("\nPARENT:I am back.");
       printf("\nPARENT:MY process id is %d.",getpid());
       printf("\nPARENT:My child processs id is %d",pid);
       partition(a,0,size-1);
       //quicksort(a,0,size-1);
        printf("\n SORTED ELEMENT");
        for(i=0;i<size;i++)
          printf("\n%d",a[i]);
        printf("\n PARENT:I am dying now");
       //ORPHAN
         system("ps -A -H|grep a.out");
         exit(0);
      /* //ZOMBIE
       //printf("\n-----------------------------------------");
       printf("\n PARENT:I am sleeping now:");
       sleep(5);
       printf("\n----------------------------------------");
      system("ps -A -H|grep a.out");*/
   }
}
void quicksort(int a[10],int first,int last){
    int pivot,j,temp,i;
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

void partition(int arr[],int low,int high){
   int mid;
   if(low<high)
   {
     mid=(low+high)/2;
     partition(arr,low,mid);
     partition(arr,mid+1,high);
     mergeSort(arr,low,mid,high);
   }
}

void mergeSort(int arr[],int low,int mid,int high){
  int i,m,k,l,temp[10];
  l=low;
  i=low;
  m=mid+1;
  while((l<=mid)&&(m<=high)){
   if(arr[l]<=arr[m]){
      temp[i]=arr[l];
      l++;
  }
  else{
      temp[i]=arr[m];
      m++;
    }
    i++;
}
 if(l>mid){
      for(k=m;k<=high;k++)
      {
         temp[i]=arr[k];
          i++;
      }
}
else{
   for(k=l;k<=mid;k++)
   {
      temp[i]=arr[k];
      i++;
   }
}
for(k=low;k<=high;k++){
   arr[k]=temp[k];
}
}
    
