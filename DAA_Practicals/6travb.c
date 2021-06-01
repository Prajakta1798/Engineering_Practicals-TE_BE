#include<stdio.h>

int matrix[25][25],temp_mat[25][25], visited_cities[10], limit, cost = 0,cost_node[10],path[10];

int row_reduction(int c_matrix[25][25],int flag)
{
    int min[10],rr=0,i,j;

    for(i = 0; i < limit; i++)
	{
        min[i]=999;
		for(j = 0; j < limit; j++)
        {
            if(min[i]>c_matrix[i][j])
            {
                min[i]=c_matrix[i][j];
            }
        }
	}

	for(i = 0; i < limit; i++)
	{
        for(j = 0; j < limit; j++)
		{
			if(min[i]!=0 && min[i]!=999)
            {
                if(c_matrix[i][j]!=999)
                {
                    c_matrix[i][j]=c_matrix[i][j]-min[i];
                }
            }
		}
		if(min[i]!=999)
		rr=rr+min[i];
    }

    if(flag==1)
        for(i = 0; i < limit; i++)
            for(j = 0; j < limit; j++)
                matrix[i][j]=c_matrix[i][j];
    else
        for(i = 0; i < limit; i++)
            for(j = 0; j < limit; j++)
                temp_mat[i][j]=c_matrix[i][j];

    return rr;
}
int col_reduction(int c_matrix[25][25],int flag)
{
    int min[10],cr=0,i,j;
    for(i = 0; i < limit; i++)
	{
        min[i]=999;
		for(j = 0; j < limit; j++)
        {
            if(min[i]>c_matrix[j][i])
            {
                min[i]=c_matrix[j][i];
            }
        }
	}

	for(i = 0; i < limit; i++)
	{
        for(j = 0; j < limit; j++)
		{
			if(min[i]!=0 && min[i]!=999)
            {
                if(c_matrix[j][i]!=999)
                {
                    c_matrix[j][i]=c_matrix[j][i]-min[i];
                }
            }
		}
        if(min[i]!=999)
            cr=cr+min[i];
    }

     if(flag==1)
        for(i = 0; i < limit; i++)
            for(j = 0; j < limit; j++)
                matrix[i][j]=c_matrix[i][j];
    else
        for(i = 0; i < limit; i++)
            for(j = 0; j < limit; j++)
                temp_mat[i][j]=c_matrix[i][j];
    return cr;
}

int tsp(int c)
{
	int count, nearest_city = 999,rr,cr,i,j,min[10];
	int minimum = 999, temp;
	for(count = 0; count < limit; count++)
	{
		cr=rr=0;
		if( matrix[c][count]!=999 && visited_cities[count] == 0)
		{
            for(i = 0; i < limit; i++)
            {
                for(j = 0; j < limit; j++)
                {
                    if(i==count && j==0)
                        temp_mat[i][j]=999;
                    else if(i==c || j==count)
                        temp_mat[i][j]=999;
                    else
                        temp_mat[i][j]=matrix[i][j];
                }
            }

            rr=row_reduction(temp_mat,2);
            cr=col_reduction(temp_mat,2);

            cost=matrix[c][count]+rr+cr;
            if(cost < minimum)
            {
                minimum = cost;
                nearest_city=count;
            }
        }
    }
	return nearest_city;
}

void minimum_cost(int city,int cnt)
{
	int nearest_city,temp,i,j,rr,cr;
	visited_cities[city] = 1;
	path[cnt]=city;
	nearest_city = tsp(city);
	if(nearest_city == 999)
	{
		return;
	}
	else
    {
        temp=matrix[city][nearest_city];
        for(i = 0; i < limit; i++)
        {
            for(j = 0; j < limit; j++)
            {
                if(i==city || j==nearest_city)
                {
                    matrix[i][j]=999;
                }
            }
        }
        rr=row_reduction(matrix,1);
        cr=col_reduction(matrix,1);
        cost_node[cnt+1]=temp+rr+cr+cost_node[cnt];
        minimum_cost(nearest_city,cnt+1);
    }
}
int main()
{
	int i, j,rr,cr;
	printf("Enter Total Number of Cities:\t");
	scanf("%d", &limit);
	printf("\nEnter Cost Matrix\n");
	for(i = 0; i < limit; i++)
	{
		printf("\nEnter %d Elements in Row[%d]\n", limit, i + 1);
		for(j = 0; j < limit; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
		visited_cities[i] = 0;
	}
	printf("\nEntered Cost Matrix\n");
	for(i = 0; i < limit; i++)
	{
		printf("\n");
		for(j = 0; j < limit; j++)
		{
			printf("%d ", matrix[i][j]);
		}
	}

    rr=row_reduction(matrix,1);
    cr=col_reduction(matrix,1);

	cost_node[0]=rr+cr;
	path[0]=0;
	minimum_cost(0,0);
	printf("\n\nPath:\t");
	for(i=0;i<limit;i++)
    {
        printf("%d\t==>", path[i]+1);
    }
    printf("1");
	printf("\n\nMinimum Cost: \t%d",cost_node[i-1]);
	return 0;
}

