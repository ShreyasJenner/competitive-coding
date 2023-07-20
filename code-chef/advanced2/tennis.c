//https://www.codechef.com/problems/EXUNB
//Tennis Tournament

#include <stdio.h>

int main()
{
	int n,i,j,wins=0,run,t;
	scanf("%d",&t);

	while(t--)
	{
		wins=0;
		scanf("%d",&n);

		if(n%2==0)
			printf("NO\n");
		else
		{
			printf("YES\n");
			int arr[n][n];
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					arr[i][j]=0;
			
			for(j=1;j<n;j+=2)
			{
				arr[0][j]=1;
				wins++;
			}

			for(i=1;i<n;i++)
			{
				run=wins;
				j=i+1;
				while(run--)
				{
					if(j>=n)
						j %= n;
					arr[i][j]=1;
					j+=2;
				}
			}

			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
					printf("%d",arr[i][j]);
				printf("\n");
			}
		}
	}

	return 0;
}
	
