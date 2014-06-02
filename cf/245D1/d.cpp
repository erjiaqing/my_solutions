#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=100005;
const long long inf=0x7fffffffffffffffll;
long long sum[maxn],a[maxn],maxa=0;
struct Point{
	long long x,y;
	Point(){}
	Point(long long _x,long long _y):x(_x),y(_y){}
	bool operator < (const Point &a) const {return (a.x==x)?(y<a.y):(x<a.x);}
	long long operator * (const Point &a) const {return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);}
}P[maxn],Q[maxn];
int main()
{
	int n,pi,qi;
	long long ans=inf;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
		P[i]=Point(i,sum[i]);
		Q[i]=Point(sum[i],i);
	}
	sort(&P[1],&P[n+1]);
	sort(&Q[1],&Q[n+1]);
	long long tans=0,ta,tb,tc,td;
	for (int i=1;i<=n;i++)
	{
		pi=lower_bound(&P[1],&P[n+1],P[i])-&P[0];
		qi=lower_bound(&Q[1],&Q[n+1],Point(P[i].y,P[i].x))-&Q[0];
		ta=P[i]*P[pi-1];
		tb=P[i]*P[pi+1];
		tc=P[i]*Point(Q[qi+1].y,Q[qi+1].x);
		td=P[i]*Point(Q[qi-1].y,Q[qi-1].x);
		if (pi==1) ta=inf;
		if (pi==n) tb=inf;
		if (qi==n) tc=inf;
		if (qi==1) td=inf;
		ans=min(ans,min(min(ta,tb),min(tc,td)));
	}
	printf("%lld\n",ans);
	return 0;
}
