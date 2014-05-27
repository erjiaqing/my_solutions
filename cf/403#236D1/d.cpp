#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1005;
const long long mod=1000000007;
long long dp[maxn+5][maxn+5];
long long frac[maxn];
long long c[maxn+5][maxn+5];
long long f[55][maxn];
int main()
{
	for (int i=f[0][0]=1;i<=50;i++)
		for (int j=i;j<maxn;j++)
			f[i][j]=(f[i][j-i]+f[i-1][j-i])%mod;
	for (int i=c[0][0]=1;i<maxn;i++)
		for (int j=c[i][0]=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	for (int i=frac[0]=1;i<maxn;i++)
		frac[i]=(frac[i-1]*i)%mod;
	for (int i=0;i<=50;i++)
		for (int j=0;j<maxn;j++)
		{
			for (int k=1;k<=j;k++)
				(dp[i][j]+=f[i][k]*c[j-k+i][j-k])%=mod;
			(dp[i][j]*=frac[i])%=mod;
		}
	int q,a,b;
	scanf("%d",&q);
	while (q--)
		scanf("%d%d",&a,&b),printf("%lld\n",b>50?0ll:dp[b][a]);
	return 0;
}
