//https://www.codechef.com/problems/MXMEDIAN
//Median of adjacent maximum numbers

//program stores the array values and then finds the largest number that is not on an even index 'i'
//that number if larger than number located on even indices as given by 'loc' replaces the element on loc
//this way the even index is largest for all pairs of elements in the array
//median is determined by making an array with these elements after sorting them in ascending order

#include <stdio.h>

int largest(int arr[], int n)				//function to find largest number in array that is not on even indices
{
	int max=-1,loc=-1;
	for(int i=0;i<n;i++)
	{
		if(arr[i]>max && i%2!=0)
		{
			max = arr[i];
			loc=i;
		}
	}
	return loc;
}

int main()
{
	int n,i,j,temp,loc=0,max,t; 		 
	scanf("%d",&t);

	while(t--)
	{
		loc=0;
		scanf("%d",&n);
		int arr[2*n], store[n];

		for(i=0;i<2*n;i++)
			scanf("%d",&arr[i]);

		for(j=0;j<n;j++)			//loop that replaces element on even indices with a larger one
		{
			max = largest(arr,2*n);
			if(arr[max]>arr[2*loc])
			{
				temp = arr[max];
				arr[max] = arr[2*loc];
				arr[2*loc] = temp;
			}
			loc++;
		}

		for(i=0;i<2*n;i+=2)			//sort all the even position indices in ascending order
		{
			for(j=0;j<2*n;j+=2)
			{
				if(arr[i]<arr[j])
				{
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
		
		j=0;
		for(i=0;i<2*n;i+=2)				//loop that creates a new array
			store[j++] = arr[i];

		if(n%2==0)							//code to calculate median
			printf("%d\n",(store[n/2]+store[(n/2)-1])/2);
		else
			printf("%d\n",store[n/2]);

		for(i=0;i<2*n;i++)
			printf("%d ",arr[i]);
		printf("\n");
	}

	return 0;
}

