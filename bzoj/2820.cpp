#include <bits/stdc++.h>
using namespace std;
const int maxn=10000005;
long long u[maxn];
int f[maxn],g[maxn],h[maxn];
const int sgn[]={1,-1};
//vector<int>prime;
int prime[maxn],top;
int n,m;
void prep()
{
/*	memset(f,-1,sizeof(f));
	f[0]=f[1]=0;u[1]=1;
	for (int i=2;i<maxn;i++)
	{
		if (f[i])
		{
			u[i]=-1;
			for (int j=i+i;j<maxn;j+=i)
			{
				f[j]=0;
				if (!((j/i)%i))
					u[j]=0;
				else
					u[j]=-u[j/i];
			}
		}
	}
	for (int i=1;i<maxn;i++)
		u[i]+=u[i-1];
		*/
	for (int i=2;i<=maxn;i++)
	{
		if (!f[i])
		{
			g[i]=h[i]=1;
			prime[++top]=i;
		}
		for (int j=1;(j<=top)&&(prime[j]<=maxn/i);j++)
		{
			f[i*prime[j]]=1;
			if (i%prime[j]==0)
			{
				g[i*prime[j]]=g[i]+1;
				h[i*prime[j]]=h[i];
				break;
			}else
			{
				g[i*prime[j]]=g[i]+1;
				h[i*prime[j]]=h[i]+1;
			}
		}
	}
	for (int i=2;i<=maxn;i++)
	{
		int fx;
		if (g[i]==h[i])
			fx=sgn[(h[i]-1)&1]*h[i];
		else if (g[i]==h[i]+1)
			fx=sgn[h[i]&1];
		else
			fx=0;
		u[i]=u[i-1]+fx;
	}
}
long long calc(long long n,long long m)
{
	if (n>m)
		swap(n,m);
	long long ans=0;
	long long l,r;
	for (l=1;l<=n;l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		ans+=(u[r]-u[l-1])*(n/l)*(m/l);
	}
	return ans;
}
int main()
{
	int t,a,b;
	prep();
//	cerr<<"fi\n";
	scanf("%d",&t);
	while (~scanf("%d%d",&a,&b))
		printf("%lld\n",calc(a,b));
	return 0;
}
