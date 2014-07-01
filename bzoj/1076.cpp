#include <bits/stdc++.h>
using namespace std;
double dp[105][1<<16];
int k,n,q,w;
int need[20],p[20];
int main()
{
	scanf("%d%d",&k,&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
		while (scanf("%d",&w),w) (need[i]|=(1<<(w-1)));
	}
	for (int i=k;i;i--)
	{
		for (int j=0;j<(1<<n);j++)
		{
			for (int q=0;q<n;q++)
				if ((j&need[q])==need[q])
					dp[i][j]+=max(dp[i+1][j],dp[i+1][j|(1<<q)]+p[q]);
				else
					dp[i][j]+=dp[i+1][j];
			dp[i][j]/=n;
		}
	}
	printf("%.6lf\n",dp[1][0]);
	return 0;
}
