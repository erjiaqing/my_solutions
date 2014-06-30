#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
char sq[maxn];
int cnt;
int n,q,op,ql,qr;
int son[maxn][2],lmin[maxn],lmax[maxn],rmin[maxn],rmax[maxn],val[maxn],f[maxn],sum[maxn],sz[maxn],rev[maxn],inv[maxn],root;
int tn;
char str[maxn];
void update(int x)
{
	sz[x]=sz[son[x][0]]+sz[son[x][1]]+1;
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+val[x];
	lmin[x]=lmin[son[x][0]];
	lmin[x]=min(lmin[x],sum[son[x][0]]+val[x]);
	lmin[x]=min(lmin[x],sum[son[x][0]]+val[x]+lmin[son[x][1]]);
	lmax[x]=lmax[son[x][0]];
	lmax[x]=max(lmax[x],sum[son[x][0]]+val[x]);
	lmax[x]=max(lmax[x],sum[son[x][0]]+val[x]+lmax[son[x][1]]);
	rmin[x]=rmin[son[x][1]];
	rmin[x]=min(rmin[x],sum[son[x][1]]+val[x]);
	rmin[x]=min(rmin[x],sum[son[x][1]]+val[x]+rmin[son[x][0]]);
	rmax[x]=rmax[son[x][1]];
	rmax[x]=max(rmax[x],sum[son[x][1]]+val[x]);
	rmax[x]=max(rmax[x],sum[son[x][1]]+val[x]+rmax[son[x][0]]);
}
void build(int l,int r)
{
	int mid=(l+r)/2;
	if (l<mid)
		build(l,mid-1),son[mid][0]=(l+mid-1)/2,f[(l+mid-1)/2]=mid;
	if (mid<r)
		build(mid+1,r),son[mid][1]=(mid+r+1)/2,f[(mid+r+1)/2]=mid;
	update(mid);
}
void _rev(int x)
{
	rev[x]^=1;
	swap(son[x][0],son[x][1]);
	swap(lmin[x],rmin[x]);
	swap(rmax[x],rmax[x]);
}
void _inv(int x)
{
	inv[x]^=1;
	val[x]=-val[x];sum[x]=-sum[x];
	swap(lmin[x],lmax[x]);swap(rmin[x],rmax[x]);
	lmin[x]=-lmin[x];lmax[x]=-lmax[x];
	rmin[x]=-rmin[x];rmax[x]=-rmax[x];
}
void push_down(int x)
{
	if (rev[x])
	{
		if (son[x][0]) _rev(son[x][0]);
		if (son[x][1]) _rev(son[x][1]);
		rev[x]=0;
	}
	if (inv[x])
	{
		if (son[x][0]) _inv(son[x][0]);
		if (son[x][1]) _inv(son[x][1]);
		inv[x]=0;
	}
}
void rotate(int p,int x)
{
	int cx=(son[x][1]==p),y=son[p][cx^1],z=f[x];
	if (y) f[y]=x;
	son[z][(x==son[z][1])]=p;
	son[p][cx^1]=x;f[p]=z;son[x][cx]=y;f[x]=p;
	update(x);
}
void splay(int p,int k)
{
	push_down(p);
	while (f[p]!=k)
	{
		int x=f[p],y=f[x];
		push_down(y);push_down(x);push_down(p);
		if (y==k)
			rotate(p,x);
		else if ((p==son[x][0])^(x==son[y][0]))
			rotate(p,x),rotate(p,y);
		else
			rotate(x,y),rotate(p,x);
	}
	update(p);
	if (k==0)
		root=p;
}
int select(int rank,int k)
{
	int p=root;
	while (sz[son[p][0]]+1!=rank)
	{
		if (sz[son[p][0]]+1<rank)
		{
			rank-=sz[son[p][0]]+1;
			p=son[p][1];
		}
		else
		{
			p=son[p][0];
		}
		push_down(p);
	}
	splay(p,k);
	return p;
}
void hehe(int &l,int &r)
{
	l=select(l,0);r=select(r,l);
}
void Rev(int l,int r)
{
	hehe(l,r);_rev(son[r][0]);splay(son[r][0],0);
}
void Inv(int l,int r)
{
	hehe(l,r);_inv(son[r][0]);splay(son[r][0],0);
}
int Que(int l,int r)
{
	return hehe(l,r),(1-lmin[son[r][0]])/2+(1+rmax[son[r][0]])/2;
}
int main()
{
	scanf("%d%d",&n,&q);
	scanf("%s",str+2);
	for (int i=2;i<=n+1;i++) val[i]=(str[i]=='('?1:-1);
	n+=2;
	root=(1+n)/2;
	build(1,n);
	while (q--)
	{
		scanf("%d%d%d",&op,&ql,&qr);
		if (op==0)
			printf("%d\n",Que(ql,qr+2));
		else if (op==1)
			Inv(ql,qr+2);
		else if (op==2)
			Rev(ql,qr+2);
	}
	return 0;
}
