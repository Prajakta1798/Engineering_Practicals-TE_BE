#include<stdio.h>

struct xyz
{
	int min;
	int max;
};

struct xyz minmax(int first, int last, int a[]);

void main()
{
	int a[5],i;
	struct xyz mm;
	
	printf("\nEnter 5 elements:");
	for(i=0;i<5;i++)
		scanf("%d",&a[i]);

	printf("\nArray elements:");
	for(i=0;i<5;i++)
		printf("\t%d",a[i]);

	mm=minmax(0,4,a);
	printf("\nMinimum = %d\nMaximum = %d\n",mm.min,mm.max);

}

struct xyz minmax(int first, int last, int a[5])
{
	struct xyz mm,mml,mmr;
	int mid;

	/*single element*/
	if(first==last)
	{
		mm.min=a[first];
		mm.max=a[first];
		return(mm);
	}
	
	/*two elements*/
	if(first==last-1)
	{
		if(a[first]<a[last])
		{
			mm.min=a[first];
			mm.max=a[last];
		}			
		else
		{
			mm.min=a[last];
			mm.max=a[first];
		}
		return(mm);			
	}

	/*more thn two elements*/
	mid=(first+last)/2;
	mml=minmax(first,mid-1,a);
	mmr=minmax(mid,last,a);	

	/*min and max from complete array*/
	if(mml.min<mmr.min)
		mm.min=mml.min;
	else
		mm.min=mmr.min;
	
	if(mml.max<mmr.max)
		mm.max=mmr.max;
	else
		mm.max=mml.max;
	
	return(mm);
}

