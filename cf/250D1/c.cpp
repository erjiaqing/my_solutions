#include <bits/stdc++.h>
using namespace std;
typedef long long I64d;
const int maxn=205,mod=1000000007;
struct Point{
	I64d x,y;
	void Read(){scanf("%lld%lld",&x,&y);}
	Point(){}
	Point(I64d _x,I64d _y):x(_x),y(_y){}
	friend Point operator - (const Point a,const Point b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend I64d operator * (const Point a,const Point b)
	{
		return a.x*b.y-a.y*b.x;
	}
}P[maxn];
int n;
int v[maxn][maxn];
I64d f[maxn][maxn];
I64d dp(int l,int r)
{
	if (v[l][r])
		return f[l][r];
	v[l][r]=1;
	I64d &res=f[l][r];
	if (l==r-1)
		return res=1;
	for (int k=l+1;k<r;k++)
		if ((P[r]-P[l])*(P[r]-P[k])>0)
			(res+=dp(l,k)*dp(k,r))%=mod;
	return res;
}
int main()
{
	I64d area=0;
	scanf("%d",&n);
	for (int i=0;i<n;i++) P[i].Read();P[n]=P[0];
	for (int i=0;i<n;i++) area+=P[i]*P[i+1];
	if (area<0)
		reverse(&P[0],&P[n]),P[n]=P[0];
	printf("%lld\n",dp(0,n-1));
	return 0;
}

