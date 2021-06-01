#include<stdio.h>
#include<math.h>
int b[100];
	void print(int n);
	int fun(int r, int c);
int main()
{
	int n,i,j;
	void place(int r,int n);
	printf("no of queens you want to place:");
	scanf("%d",&n);
	place(1,n);
return 0;
}
void print(int n)
{
int i,j;
printf("solution is:\n");
for(i=1;i<=n;++i)
  printf("\t%d",i);
 
 for(i=1;i<=n;++i)
 {
  printf("\n\n%d",i);
  for(j=1;j<=n;++j) 
  {
   if(b[i]==j)
    printf("\tQ"); 
   else
    printf("\t-"); 
  }
 }
}
int fun(int r, int c)
{
int i;
 for(i=1;i<=r-1;++i)
 {
  //checking column and digonal conflicts
  if(b[i]==c)
   return 0;
  else
   if(abs(b[i]-c)==abs(i-r))
    return 0;
 }
 
 return 1; 
}
void place(int r,int n)
{
int c;
 for(c=1;c<=n;++c)
 {
  if(fun(r,c))
  {
   b[r]=c; 
   if(r>=n) 
    print(n); 
   else 
    place(r+1,n);
  }
 }
}


