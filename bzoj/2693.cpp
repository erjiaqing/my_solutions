#include <bits/stdc++.h>
using namespace std;
const int maxn=10000005,mod=100000009;
long long u[maxn],f[maxn],g[maxn],h[maxn];//μ
long long prime[maxn];
int top;
long long sum(long long a,long long b)
{
	return ((((a)*(a+1)/2)%mod)*(((b)*(b+1)/2)%mod))%mod;
}
void prep()
{
	long long k;
	u[1]=1;
	for (long long i=2;i<maxn;i++)
	{
		if (!f[i])
			prime[top++]=i,u[i]=i*(1-i+mod)%mod,g[i]=i;
		for (int j=0;j<top && i*prime[j]<=maxn;j++)
		{
			k=i*prime[j];
			f[k]=1;
			if (i%prime[j]==0)
			{
				g[k]=g[i]*prime[j];
				if (k == g[k])
					u[k]=(k*(1-prime[j]+mod))%mod;
				else
					u[k]=(u[g[k]]*u[k/g[k]])%mod;
				break;
			}
			u[k]=(u[i]*u[prime[j]])%mod;
			g[k]=prime[j];
		}
	}
	for (int i=1;i<maxn;i++) h[i]=(h[i-1]+u[i])%mod;
}
long long query(long long a,long long b)
{
	if (a>b)
		swap(a,b);
	long long nxt;long long ans=0;
	for (long long i=1;i<=a;i=nxt+1)
	{
		nxt=min(a/(a/i),b/(b/i));
		(ans+=((h[nxt]-h[i-1]+mod)%mod*sum(a/i,b/i))%mod)%=mod;
	}
	return ans;
}
int main()
{
	prep();
	int t,n,m;
	scanf("%d",&t);
	while (t--)
		scanf("%d%d",&n,&m),printf("%lld\n",query(n,m));
	return 0;
}
