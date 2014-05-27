#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
const int maxn=1e6+5;
long long inf=0x7fffffffffffffffLL;
long long x[maxn],y[maxn],m[maxn],ans,move;
bool A[maxn],B[maxn];
long long check(int l,int r,int a,int b)
{
	long long ret=0;
	for (int i=1;i<=n;i++)
	{
		if (!(x[i]>=l&&x[i]<=r&&y[i]>=a&&y[i]<=b))
		{
			if (!(x[i]>=a&&x[i]<=b&&y[i]>=l&&y[i]<=r))
				return inf;
			ret+=m[i];
			A[i]=true;
		}else
			A[i]=false;
	}
	return ret;
}
void work()
{
	long long ret=inf;
	move=inf;
	long long xx,yy,l=inf,r=0,a=inf,b=0;
	for (int i=1;i<=n;i++)
	{
		xx=x[i];yy=y[i];
		if (xx>yy)
			swap(xx,yy);
		l=min(l,xx);r=max(r,xx);
		a=min(a,yy);b=max(b,yy);
	}
	ans=(r-l+b-a)*2;
	//--case1
	ret=check(l,r,a,b);
	if (ret<move)
	{
		move=ret;
		for (int i=1;i<=n;i++)
			B[i]=A[i];
	}
	//--case2
	ret=check(a,r,l,b);
	if (ret<move)
	{
		move=ret;
		for (int i=1;i<=n;i++)
			B[i]=A[i];
	}
	//--case3
	ret=check(l,b,a,r);
	if (ret<move)
	{
		move=ret;
		for (int i=1;i<=n;i++)
			B[i]=A[i];
	}
	//--case4
	ret=check(a,b,l,r);
	if (ret<move)
	{
		move=ret;
		for (int i=1;i<=n;i++)
			B[i]=A[i];
	}
	//move=ret;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&x[i],&y[i],&m[i]);
	work();
	printf("%lld %lld\n",ans,move);
	for (int i=1;i<=n;i++)
		printf("%d",B[i]);
	printf("\n");
	return 0;
}
