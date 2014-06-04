#include <bits/stdc++.h>
using namespace std;
typedef long long I64d;
const int maxn=262150;
const I64d Mod=998244353LL;
I64d dp[maxn],C[maxn];
vector<long long>a(maxn,0),b(maxn,0),c(maxn,0);
I64d fast_power(long long a,int k)
{
	long long ret=1;
	while (k)
	{
		if (k&1)
			(ret*=a)%=Mod;
		(a*=a)%=Mod;
		k>>=1;
	}
	return ret;
}
int fft_n;
I64d omega[maxn];
vector<long long>tmp(maxn,0);
void fft(vector<long long> &a,int s,int d)
{
	if (d==fft_n)
		return;
	fft(a,s,d<<1);
	fft(a,s+d,d<<1);
	for (int i=s,j=s,p=0;i<fft_n/2;i++,j+=d<<1,p+=d)
	{
		I64d y0=a[j],y1=a[j+d];
		tmp[i]=(y0+omega[p]*y1)%Mod;
		tmp[i+fft_n/2]=(y0+omega[p+fft_n/2]*y1)%Mod;
	}
	for (int i=s;i<fft_n;i++)
		a[i]=tmp[i];
}
vector<long long> vector_multi(vector<long long> &aa,vector<long long> &bb,int n)
{
	vector<long long> c(maxn,0);
	vector<long long> a(aa.begin(),aa.end()),b(bb.begin(),bb.end());
	fft_n=1;
	while (fft_n<n) fft_n<<=1;
	fft_n<<=1;
	omega[0]=1;
	omega[1]=fast_power(3,(Mod-1)/fft_n);
	for (int i=2;i<=fft_n;i++)
		omega[i]=omega[i-1]*omega[1]%Mod;
	fft(a,0,1);
	fft(b,0,1);
	for (int i=0;i<fft_n;i++)
		a[i]=a[i]*b[i]%Mod;
	for (int i=0;i<fft_n;i++)
		b[i]=a[i?(fft_n-i):0];
	fft(b,0,1);
	int inv=fast_power(fft_n,Mod-2);
	for (int i=0;i<fft_n;i++)
		c[i]=b[i]*inv%Mod;
	return c;
}
void solve(int l,int r)
{
	if (r==l+1)
		return;
	int mid=(l+r)/2;
	solve(l,mid);
	int need=r-l;
	for (int i=0;i<need;i++)
		a[i]=b[i]=0;
	if (need<=l)
	{
		for (int i=0;i<mid-l;i++)
			a[i]=dp[i+l];
		for (int i=0;i<need;i++)
			b[i]=dp[i];
		c=vector_multi(a,b,need);
		for (int i=0;i<need;i++)
		{
			c[i]*=2;
			if (c[i]>=Mod)
				c[i]-=Mod;
		}
	}else
	{
		for (int i=0;i<mid-l;i++)
			a[i]=b[i]=dp[i+l];
		c=vector_multi(a,b,need);
	}
	for (int i=0;i<need;i++)
	{
		a[i]=c[i];
		b[i]=C[i];
	}
	c=vector_multi(a,b,need);
	for (int i=mid;i<r;i++)
		(dp[i]+=c[i-l])%=Mod;
	solve(mid,r);
}
int main()
{
	int n,m,N=1,t;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&t),C[t]=1;
	while (N<=m) N<<=1;
	dp[0]=1;
	solve(0,N);
	for (int i=1;i<=m;i++)
		printf("%lld\n",dp[i]);
	return 0;
}
