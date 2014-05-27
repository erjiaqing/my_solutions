#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxm=1000005,maxn=1000005,mod=100000007;
long long g[maxm],f[maxm],t[maxn];
int n,m;
long long Pow(long long a,long long k)
{
	long long r=1;
	while (k)
	{
		if (k&1)
			(r*=a)%=mod;
		(a*=a)%=mod;
		k>>=1;
	}
	return r;
}
int main()
{
	scanf("%d%d",&n,&m);
	t[0]=1;g[0]=1;
	for (int i=1;i<=n;i++)
		t[i]=(t[i-1]*2)%mod;
	for (int i=1;i<=m;i++)
		g[i]=(g[i-1]*(t[n]-i))%mod;
	for (int i=3;i<=m;i++)
		f[i]=(g[i-1]-f[i-1]-f[i-2]*(i-1)%mod*(t[n]-i+1+mod)%mod+2*mod)%mod;
	long long tt=1;
	for (int i=1;i<=m;i++)
		(tt*=i)%=mod;
	(f[m]*=Pow(tt,mod-2))%=mod;
	printf("%lld\n",f[m]);
	return 0;
}
