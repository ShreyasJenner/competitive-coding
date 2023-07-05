//https://www.codechef.com/problems/DISTANCECOLO
//Distance Coloring

#include <stdio.h>

int main()
{
	const int mod = 1e+9+7;
	int n,k,i,t;
	long long int ans=1;
	scanf("%d",&t);

	while(t--)
	{
		ans = 1;
		scanf("%d %d",&n,&k);

		for(i=0;i<n;i++)
		{
			if(k>0)
			{
				ans = (ans*k)%mod;
				k--;
			}
			else
				break;
		}
		
		printf("%lld\n",ans);	
	}

	return 0;
}
