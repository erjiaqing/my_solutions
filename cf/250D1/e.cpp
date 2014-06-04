#include <bits/stdc++.h>
using namespace std;
const int maxn=2621500;
const long long mod=998244353;
//--  /======   /======   /======\
//--  |         |            ||
//--  |======   |======      ||
//--  |         |            ||
//--  |         |            ||
int fft_size;
long long tmp[maxn],w[maxn],fft_a[maxn],fft_b[maxn];
long long fast_power(long long a,int k)
{
	long long ret=1;
	while (k)
	{
		if (k&1) (ret*=a)%=mod;
		(a*=a)%=mod;k>>=1;
	}
	return ret;
}
void fft(long long *a,int s,int d)
{
	if (d==fft_size)
		return;
	fft(a,s,d<<1);
	fft(a,s+d,d<<1);
	for (int i=s,j=s,p=0;i<fft_size/2;i+=d,j+=d<<1,p+=d)
	{
		int y0=a[j],y1=a[j+d];
		tmp[i]=(y0+y1*w[p])%mod;
		tmp[i+fft_size/2]=(y0+y1*w[p+fft_size/2])%mod;
	}
	for (int i=s;i<fft_size;i+=d)
		a[i]=tmp[i];
}
void vector_mult(long long *aa,long long *bb,long long *c,int n)
{
	for (int i=0;i<n;i++)
		fft_a[i]=aa[i],fft_b[i]=bb[i];
	fft_size=1;
	while (fft_size<n) fft_size<<=1;
	fft_size<<=1;
	w[0]=1;
	w[1]=fast_power(3,(mod-1)/fft_size);
	for (int i=2;i<=fft_size;i++)
		w[i]=w[i-1]*w[1]%mod;
	fft(fft_a,0,1);
	fft(fft_b,0,1);
	for (int i=0;i<fft_size;i++)
		(fft_a[i]*=fft_b[i])%=mod;
	for (int i=0;i<fft_size;i++)
		(fft_b[i]=fft_a[i?(fft_size-i):0]);
	fft(fft_b,0,1);
	int inv=fast_power(fft_size,mod-2);
	for (int i=0;i<fft_size;i++)
	{
		c[i]=fft_b[i]*inv%mod;
		fft_a[i]=fft_b[i]=0;
	}
}
long long a[maxn],b[maxn],c[maxn],C[maxn],dp[maxn];
int n,m,t,N;
void solve(int l,int r)
{
	if (l+1==r)
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
		vector_mult(a,b,c,need);
		for (int i=0;i<need;i++)
			(c[i]*=2)%=mod;
	}else
	{
		for (int i=0;i<mid-l;i++)
			a[i]=b[i]=dp[i+l];
		vector_mult(a,b,c,need);
	}
	for (int i=0;i<need;i++)
	{
		a[i]=c[i];
		b[i]=C[i];
	}
	vector_mult(a,b,c,need);
	for (int i=mid;i<r;i++)
		(dp[i]+=c[i-l])%=mod;
	solve(mid,r);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&t),C[t]=1;
	dp[0]=1;
	N=1;
	while (N<=m) N<<=1;
	solve(0,N);
	for (int i=1;i<=m;i++)
		printf("%lld\n",dp[i]);
	return 0;
}
