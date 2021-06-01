#include<stdio.h>
#define SIZE 20 
void msort(int [],int ,int );
void merge(int [],int ,int ,int ,int );
 
void main()
{
	int a[SIZE],p,t,i,j,tape[10][10],j1,ind,i1,sum[10],k,p1;
	int s1=0,s2=0,z;
	printf("Enter no of programs:");
	scanf("%d",&p);
	printf("Enter length of %d programs:\n",p);
	p1=p;

	for(i=0;i<p;i++)
	scanf("%d",&a[i]);

	msort(a,0,p-1);

	printf("\nSorted array is :");
	for(i=0;i<p;i++)
		printf("%d ",a[i]);

	printf("\nEnter number of tapes::");
	scanf("%d",&t);

	ind=0;
	i=0;
	j=0;

	while(ind<p)
	{
		tape[i][j]=a[ind];
		i++;
		ind++;
		if(i==t)
		{
			i=0;
			j++;
		}
	}

	for(i1=i;i<t;i++)
	{
		tape[i][j]=0;
	}
	
	//ending 0
	for(i=0;i<t;i++)
		tape[i][j+1]=0;

	j1=j;
	printf("\nTape:\n");
	for(i=0;i<t;i++)
	{
		for(j=0;j<=j1;j++)
			printf("%d\t",tape[i][j]);
		printf("\n");
	}
	i=0;
	j=0;
	ind=0;
	while(ind<=p1 && i<t)
	{
		if(tape[i][j]!=0)
		{
			s1+=tape[i][j];
			s2+=s1;
			j++;
			ind++;
		}
		else
		{
			printf("Mean time of tape %d = %d\n",i,s2);
			i++;
			j=0;
			s1=0;
			s2=0;
		}
	}
}
 
void msort(int a[],int f,int l)
{
	int mid;

	if(f<l)
	{
		mid=(f+l)/2;
		msort(a,f,mid);  
		msort(a,mid+1,l);
		merge(a,f,mid,mid+1,l);  
	}
}
 
void merge(int a[],int f1,int l1,int f2,int l2)
{
	int w[SIZE];
	int i,j,k;
	i=f1;
	j=f2;
	k=0;

	while(i<=l1 && j<=l2)
	{
		if(a[i]<a[j])
		{
			w[k]=a[i];
			k++;
			i++;
		}
		
		else
		{
			w[k]=a[j];
			k++;
			j++;
		}
	}

	while(i<=l1)
	{  
		w[k]=a[i];
		k++;
		i++;
	}

	while(j<=l2)
	{  
		w[k]=a[j];
		k++;
		j++;
	}

	for(i=f1,j=0;i<=l2;i++,j++)
		a[i]=w[j];
}

