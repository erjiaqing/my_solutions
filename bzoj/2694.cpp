#include <bits/stdc++.h>
using namespace std;
const int mod=1<<30,maxn=4000005;
long long u[maxn],f[maxn],g[maxn];
int prime[maxn],top;
long long sum(long long a,long long b)
{
	return (((a*(a+1)/2)%mod)*((b*(b+1)/2)%mod))%mod;
}
void prep()
{
	long long k;
	u[1]=1;
	//g(1)=1,g(p_i)=p_i-p_i^2
	for (long long i=2;i<maxn;i++)
	{
		if (!f[i])
			prime[top++]=i,
			u[i]=-1;
		for (int j=0;j<top && i*prime[j]<maxn;j++)
		{
			k=i*prime[j];
			f[k]=1;
			if (i%prime[j]==0)
			{
				u[i*prime[j]]=0;
				break;
			}else
			{
				u[i*prime[j]]=-u[i];
			}
		}
	}
	for (int i=1;i<maxn;i++)
	{
		if (u[i]) f[i]=i;
		else f[i]=0;
//		u[i]=(u[i]+mod)%mod;
		u[i]=((((i*i)%mod)*u[i])%mod+mod)%mod;
	}
	for (int i=1;i*i<maxn;i++)
		for (int j=i;i*j<maxn;j++)
			if (j==i)
				(g[i*j]+=((f[i]*u[i])%mod))%=mod;
			else
				(g[i*j]+=(((f[i]*u[j])%mod)+((f[j]*u[i])%mod))%mod)%=mod;
	for (int i=1;i<maxn;i++)
		g[i]=(g[i-1]+g[i])%mod;
}
long long calc(long long a,long long b)
{
	long long i,nxt,ans=0;
	if (a>b) swap(a,b);
	for (i=1;i<=a;i=nxt+1)
	{
		nxt=min(a/(a/i),b/(b/i));
		(ans+=((((g[nxt]-g[i-1]+mod)%mod)*sum(a/i,b/i))%mod))%=mod;
	}
	return ans;
}
int main()
{
//	cerr<<mod<<endl;
	prep();
	int n,a,b;
	scanf("%d",&n);
	while (n--)
		scanf("%d%d",&a,&b),printf("%lld\n",calc(a,b));
	return 0;
}
