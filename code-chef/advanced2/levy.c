//https://www.codechef.com/problems/LEVY
//Levy Conjecture

#include <stdio.h>

void one(int *ptr)
{
	for(int i=0;i<10000;i++)
		*(ptr+i) = 1;
}

int sieve(int *base, int *prime)
{
	int size=0;
	for(int i=2;i<10000;i++)
	{
		if(*(base+i))
		{
			*(prime+size)=i;
			size++;
			for(int p=i*i;p<10000;p+=i)
				*(base+p)=0;
		}
	}
	return size;
}

int search(int n, int *prime, int size)
{
	for(int i=0;i<size;i++)
		if(*(prime+i)==n)
			return 1;
	return 0;
}


int main()
{
	int n, base[10000], prime[10000],size,t,c=0,rem;
	
	one(base);
	one(prime);
	
	base[0]=base[1]=0;
	prime[0]=prime[1]=0;
	size=sieve(base,prime);
	
	scanf("%d",&t);

	while(t--)
	{
		c=0;
		scanf("%d",&n);
	
		if(n<5)
		{
			printf("0\n");
			continue;
		}

		for(int i=0;i<size;i++)
		{
			rem = n-prime[i];
			if(rem%2==0 && rem>=0)
			{
				if(base[rem/2])
				{
					c++;
				}
			}
		}
		printf("%d\n",c);
	}
	return 0;
}
