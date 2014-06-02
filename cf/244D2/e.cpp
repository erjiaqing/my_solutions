#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1000005;
int x[maxn];
long long dp[maxn];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&x[i]);
	for (int i=n-1;i>=1;i--)
		dp[i]=dp[i+1]+(long long)(x[i+1]-x[i])*((n+m-i-1)/m);
	long long ans=dp[1],now=0;
	for (int i=2;i<=n;i++)
	{
		now+=(long long)(x[i]-x[i-1])*((i+m-2)/m);
		ans=min(ans,now+dp[i]);
	}
	printf("%lld\n",ans*2);
	return 0;
}

