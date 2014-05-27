#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=2000005;
long long n,p;
long long g,c[maxn],prime[maxn],chk[maxn];
long long ksm(long long a,long long k)
{
	if (!k)
		return 1;
	long long r=1,b=a;
	while (k)
	{
		if (k&1)
			(r*=b)%=p;
		(b*=b)%=p;
		k>>=1;
	}
	return r;
}
void mul(int x)
{
	for (int i=0;i<g;i++)
	{
		int p=x;
		while (p)
			c[i]+=(p/=prime[i]);
	}
}
void div(int x)
{
	for (int i=0;i<g;i++)
	{
		int p=x;
		while (p)
			c[i]-=(p/=prime[i]);
	}
}
long long bi(int a,int b)
{
	memset(c,0,sizeof(c));
	mul(a);div(b);div(a-b);
	long long ret=1;
	for (int i=0;i<g;i++)
		(ret*=ksm(prime[i],c[i]))%=p;
	return ret;
}
int main()
{
	for (int i=2;i<maxn;i++)
	{
		if (!chk[i])
			prime[g++]=i;
		for (int j=0;j<g && prime[j]*i<maxn;j++)
		{
			chk[prime[j]*i]=true;
			if (!(i%prime[j]))
				break;
		}
	}
	scanf("%lld%lld",&n,&p);
	printf("%lld\n",(bi(2*n,n)-bi(2*n,n-1)+p)%p);
	return 0;
}
