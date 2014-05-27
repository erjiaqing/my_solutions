#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;
const int maxn=500005;
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
struct SegTree{int lc,rc,l,r,cs,same;}T[maxn*4];
int color[maxn];
//--
inline void pushdown(int);
inline void update(int);
inline void trans(int &);
void build(int,int,int);
void paint(int,int,int,int);
int getcount(int,int,int);
//--
inline void update(int rt)
{
	if (T[rt].l!=T[rt].r)
	{
		pushdown(ls(rt));
		pushdown(rs(rt));
		T[rt].lc=T[ls(rt)].lc;T[rt].rc=T[rs(rt)].rc;
		T[rt].cs=T[ls(rt)].cs+T[rs(rt)].cs-(T[ls(rt)].rc==T[rs(rt)].lc);
	}
}
inline void pushdown(int rt)
{
	if (~T[rt].same)
	{
		T[rt].lc=T[rt].rc=T[rt].same;
		T[rt].cs=1;
		if (T[rt].l!=T[rt].r)
			T[ls(rt)].same=T[rs(rt)].same=T[rt].same;
		T[rt].same=-1;
	}
}
void build(int rt,int l,int r)
{
	if (l==r)
	{
		T[rt].l=l;T[rt].r=r;
//		T[rt].lc=T[rt].rc=color[l];
		T[rt].cs=1;
		T[rt].same=-1;
		return;
	}
	int mid=(l+r)/2;
	build(ls(rt),l,mid);
	build(rs(rt),mid+1,r);
	T[rt].l=l;T[rt].r=r;
	T[rt].same=-1;
//	update(rt);
}
void paint(int rt,int l,int r,int c)
{
	int mid=(T[rt].l+T[rt].r)/2;
	pushdown(rt);
	if (T[rt].l==l && r==T[rt].r)
	{
		T[rt].same=c;
		pushdown(rt);
	}else
	{
		if (r<=mid)
			paint(ls(rt),l,r,c);
		else if (l>mid)
			paint(rs(rt),l,r,c);
		else
		{
			paint(ls(rt),l,mid,c);
			paint(rs(rt),mid+1,r,c);
		}
		update(rt);
	}
}
int getcount(int rt,int l,int r)
{
	int mid=(T[rt].l+T[rt].r)/2,ret=0;
	pushdown(rt);
	if (T[rt].l == l && r == T[rt].r)
		return T[rt].cs;
	else
	{
		if (r<=mid)
			ret=getcount(ls(rt),l,r);
		else if (l>mid)
			ret=getcount(rs(rt),l,r);
		else
		{
			ret+=getcount(ls(rt),l,mid);
			ret+=getcount(rs(rt),mid+1,r);
			if (T[ls(rt)].rc == T[rs(rt)].lc)
				ret--;
		}
	}
	update(rt);
	return ret;
}
int getcolor(int rt,int x)
{
	pushdown(rt);
	int mid=(T[rt].l+T[rt].r)/2;
	if (T[rt].l==T[rt].r)
		return T[rt].lc;
	if (x<=mid)
		return getcolor(ls(rt),x);
	else
		return getcolor(rs(rt),x);
}
int n,q,c,move,flip;
inline void trans(int &x)
{
	if (flip)
		x=n-x+2;
	x-=move;
	while (x<1)
		x+=n;
	while (x>n)
		x-=n;
}
int main()
{
	int k,c,l,r;
	char buf[20];
	scanf("%d%d",&n,&c);
	build(1,1,n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&c);
		paint(1,i,i,c);
	}
	scanf("%d",&q);
	while (q--)
	{
		scanf("%s",buf);
		if (buf[0] == 'R')
		{
			scanf("%d",&k);
			if (!flip)
				move+=k;
			else
				move-=k;
			while (move<1)
				move+=n;
			while (move>n)
				move-=n;
		}else if (buf[0] == 'F')
		{
			flip=!flip;
		}else if (buf[0] == 'S')
		{
			scanf("%d%d",&l,&r);
			trans(l);trans(r);
			int cl=getcolor(1,l);
			int cr=getcolor(1,r);
			paint(1,l,l,cr);
			paint(1,r,r,cl);
		}else if (buf[0] == 'P')
		{
			scanf("%d%d%d",&l,&r,&c);
			trans(l);trans(r);
			if (flip)
				swap(l,r);
			if (l<=r)
				paint(1,l,r,c);
			else
			{
				paint(1,1,r,c);
				paint(1,l,n,c);
			}
		}else if (buf[0] == 'C' && buf[1] == 'S')
		{
			scanf("%d%d",&l,&r);
			trans(l);trans(r);
			if (flip)
				swap(l,r);
			if (l<=r)
				c=getcount(1,l,r);
			else
			{
				c=0;
				c+=getcount(1,l,n);
				c+=getcount(1,1,r);
				if (T[1].lc == T[1].rc)
					c--;
			}
			printf("%d\n",c);
		}else
		{
			c=T[1].cs;
			if (c>1 && T[1].lc == T[1].rc)
				c--;
			printf("%d\n",c);
		}
	}
	return 0;
}
