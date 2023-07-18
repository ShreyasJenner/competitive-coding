//https://www.codechef.com/problems/GREG
//Greg and Grid

#include <stdio.h>

void sieve(int *arr, int n)
{
	int p,i;
	for(p=2;p*p<=n;p++)
		if(*(arr+p))
			for(i=p*p;i<=n;i+=p)
				*(arr+i)=0;
}

int main()
{
	int n,m,count=0;
	scanf("%d %d",&n,&m);
	int arr[n+m+1];
	for(int i=0;i<n+m+1;i++)
		arr[i]=1;

	sieve(arr,n+m);

	for(int i=2;i<n+m+1;i++)
		if(arr[i])
			count++;
	
	printf("%d\n",count);

	return 0;
}
