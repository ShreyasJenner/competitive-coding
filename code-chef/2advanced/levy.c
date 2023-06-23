//https://www.codechef.com/problems/LEVY
//Levy Conjecture

#include <stdio.h>

int prime(int n)
{
	for(int i=2;i<n;i++)
		if(n%i==0)
			return 0;
	return 1;
}

int main()
{
	int n,t,c=0,i,j;

	scanf("%d",&t);

	while(t--)
	{
		c=0;
		scanf("%d",&n);
		if(n>=5 && n%2==1)
		{
			for(i=2;i<n;i++)
			{
				for(j=2;j<n-1;j++)
				{
					if(i+2*j==n && i!=j)
					{
						if(prime(i) && prime(j))
							c++;
					}
					else if(i+2*j>n)
						continue;
				}
			}
			printf("%d\n",c);
		}
		else
			printf("0\n");
	}

	return 0;
}
