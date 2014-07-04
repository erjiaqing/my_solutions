#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=200005;
long long c[maxn];
int v[maxn],t[maxn];
int n,now,T,lay=1;
long long w,ans,w0,earn;
int main()
{
	scanf("%d%lld%d",&n,&w,&T);w0=w;
	for (int i=1;i<=n;i++)
		scanf("%lld%d%d",&c[i],&t[i],&v[i]);
	now=0;ans=w;
	long long x=0,y=T,z=w,a;
	for (int i=1;i<=n;i++)
	{
		ans=max(ans,z+x*y);
		if (i==n+1 || z+x*y<c[i]) break;
		if (z<c[i])
		{
			a=(c[i]-z-1)/x+1;
			y-=a,z+=a*x;
		}
		z-=c[i];
		if (y<t[i]) break;
		z+=t[i]*x;
		y-=t[i];
		x+=v[i];
	}
	ans=max(ans,w);
	printf("%lld\n",ans-w0);
}
