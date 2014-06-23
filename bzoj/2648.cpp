#include <bits/stdc++.h>
using namespace std;
struct node
{
	long long x,y;
	node(){}
	node(const long long & _x,const long long & _y):x(_x),y(_y){}
};
struct nodecompa
{
	bool operator ()(const node &a,const node &b)
	{return (a.x<b.x)||((a.x==b.x)&&(a.y<b.y));}
};
struct nodecompb
{
	bool operator ()(const node &a,const node &b)
	{return (a.y<b.y)||((a.y==b.y)&&(a.x<b.x));}
};
set<node,nodecompa>Sx;
set<node,nodecompb>Sy;
set<node,nodecompa>Sxx;
set<node,nodecompb>Syy;
long long Abs(const long long & x){return (x<0)?(-x):x;}
long long query(const long long &x,const long long &y)
{
	long long ans=0x3fffffffffffffffll;
	set<node,nodecompa>::iterator ia;
	set<node,nodecompb>::iterator ib;
	ia=Sx.lower_bound(node(x,y));
	if (ia!=Sx.end())
		ans=min(ans,Abs(x-ia->x)+Abs(y-ia->y));
	if (ia!=Sx.begin())
	{
		ia--;
		ans=min(ans,Abs(x-ia->x)+Abs(y-ia->y));
	}

	ia=Sx.lower_bound(node(-x,-y));
	if (ia!=Sxx.end())
		ans=min(ans,Abs(x-ia->x)+Abs(y-ia->y));
	if (ia!=Sxx.begin())
	{
		ia--;
		ans=min(ans,Abs(x-ia->x)+Abs(y-ia->y));
	}

	ib=Sy.lower_bound(node(x,y));
	if (ib!=Sy.end())
		ans=min(ans,Abs(x-ib->x)+Abs(y-ib->y));
	if (ib!=Sy.begin())
	{
		ib--;
		ans=min(ans,Abs(x-ib->x)+Abs(y-ib->y));
	}

	ib=Syy.lower_bound(node(-x,-y));
	if (ib!=Syy.end())
		ans=min(ans,Abs(x-ib->x)+Abs(y-ib->y));
	if (ib!=Syy.begin())
	{
		ib--;
		ans=min(ans,Abs(x-ib->x)+Abs(y-ib->y));
	}
	return ans;
}
int main()
{
	int n,m,t;
	long long x,y;
	scanf("%d%d",&n,&m);
	while (n--)
		scanf("%lld%lld",&x,&y),Sx.insert(node(x,y)),Sy.insert(node(x,y));
	while (m--)
	{
		scanf("%d%lld%lld",&t,&x,&y);
		if (t==2)
			printf("%lld\n",query(x,y));
		else
			Sx.insert(node(x,y)),Sy.insert(node(x,y)),
			Sxx.insert(node(-x,-y)),Syy.insert(node(-x,-y));
	}
	return 0;
}
