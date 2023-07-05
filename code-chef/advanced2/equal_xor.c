//https://www.codechef.com/problems/EQBYXOR
//Equal by XORing

#include <stdio.h>

int main()
{
	int a,b,n,t,m;
	scanf("%d",&t);

	while(t--)
	{
		scanf("%d %d %d",&a,&b,&n);
		m = a^b;

		if(a==b)
			printf("0\n");
		else if(m<n)
			printf("1\n");
		else if((m^(n-1))<n)
			printf("2\n");
		else
			printf("-1\n");
	}
		
	return 0;
}
