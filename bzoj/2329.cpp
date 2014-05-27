#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=100005;
int ts,n,m;
char v[100005];
//--SPLAY
int val[maxn],sz[maxn],sum[maxn];
int lmin[maxn],lmax[maxn],rmin[maxn],rmax[maxn];
int son[maxn][2],fa[maxn];
int Swp[maxn],Inv[maxn],Rep[maxn],Set[maxn];
int root;
//--
void update(int x)
{
	sz[x]=sz[son[x][0]]+sz[son[x][1]]+1;
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+val[x];
	lmin[x]=rmin[x]=lmax[x]=rmax[x]=0;
	if (son[x][0])
	{
		lmin[x]=min(lmin[x],lmin[son[x][0]]);
		lmax[x]=max(lmax[x],lmax[son[x][0]]);
		lmin[x]=min(lmin[x],sum[son[x][0]]+val[x]);
		lmax[x]=max(lmax[x],sum[son[x][0]]+val[x]);
		if (son[x][1])
		{
			lmin[x]=min(lmin[x],sum[son[x][0]]+val[x]+lmin[son[x][1]]);
			lmax[x]=max(lmax[x],sum[son[x][0]]+val[x]+lmax[son[x][1]]);
		}
	}else
	{
		lmin[x]=min(lmin[x],val[x]);
		lmax[x]=max(lmax[x],val[x]);
		if (son[x][1])
		{
			lmin[x]=min(val[x],val[x]+lmin[son[x][1]]);
			lmax[x]=max(val[x],val[x]+lmax[son[x][1]]);
		}
	}
	if (son[x][1])
	{
		rmin[x]=min(rmin[x],rmin[son[x][1]]);
		rmax[x]=max(rmax[x],rmax[son[x][1]]);
		rmin[x]=min(rmin[x],sum[son[x][1]]+val[x]);
		rmax[x]=max(rmax[x],sum[son[x][1]]+val[x]);
		if (son[x][0])
		{
			rmin[x]=min(rmin[x],sum[son[x][1]]+val[x]+rmin[son[x][0]]);
			rmax[x]=max(rmax[x],sum[son[x][1]]+val[x]+rmax[son[x][0]]);
		}
	}else
	{
		rmin[x]=min(rmin[x],val[x]);
		rmax[x]=max(rmax[x],val[x]);
		if (son[x][0])
		{
			rmin[x]=min(val[x],rmin[son[x][0]]+val[x]);
			rmax[x]=max(val[x],rmax[son[x][0]]+val[x]);
		}
	}
}
void update1(int x)//Reverse
{
	Swp[x]^=1;
	swap(son[x][0],son[x][1]);
	swap(lmin[x],rmin[x]);
	swap(lmax[x],rmax[x]);
}
void update2(int x)//Inverse
{
	Inv[x]^=1;
	val[x]=-val[x];sum[x]=-sum[x];Set[x]=-Set[x];
	swap(lmin[x],lmax[x]);swap(rmin[x],rmax[x]);
	lmin[x]=-lmin[x];lmax[x]=-lmax[x];
	rmin[x]=-rmin[x];rmax[x]=-rmax[x];
}
void update3(int x,int k)//Replace
{
	Rep[x]=1;Set[x]=k;
	val[x]=k;sum[x]=k*sz[x];Inv[x]=0;
	if (Set[x]==-1)
	{
		lmin[x]=rmin[x]=sum[x];
		lmax[x]=rmax[x]=0;
	}else if (Set[x]==1)
	{
		lmin[x]=rmin[x]=0;
		lmax[x]=rmax[x]=sum[x];
	}
}
void push_down(int x)
{
	if (Swp[x])
	{
		if (son[x][0]) update1(son[x][0]);
		if (son[x][1]) update1(son[x][1]);
		Swp[x]=0;
	}
	if (Inv[x])
	{
		if (son[x][0]) update2(son[x][0]);
		if (son[x][1]) update2(son[x][1]);
		Inv[x]=0;
	}
	if (Rep[x])
	{
		if (son[x][0]) update3(son[x][0],Set[x]);
		if (son[x][1]) update3(son[x][1],Set[x]);
		Rep[x]=0;
	}
}
void rotate(int p,int x)
{
	int cx=(p==son[x][1]),y=son[p][cx^1],z=fa[x];
	if (y)
		fa[y]=x;
	if (x==son[z][0]) son[z][0]=p;
	if (x==son[z][1]) son[z][1]=p;
	son[p][cx^1]=x;fa[p]=z;son[x][cx]=y;fa[x]=p;
	update(x);
}
void splay(int p,int k)
{
	push_down(p);
	while (fa[p]!=k)
	{
//		cerr<<x<<endl;
		int x=fa[p],y=fa[x];
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
	int x=root;
	push_down(x);
	while (sz[son[x][0]]+1!=rank)
	{
//		cerr<<x<<endl;
		if (sz[son[x][0]]+1<rank)
		{
			rank=rank-sz[son[x][0]]-1;
			x=son[x][1];
		}else
		{
			x=son[x][0];
		}
		push_down(x);
	}
	splay(x,k);
	return x;
}
void build(int l,int r)
{
	int mid=(l+r)/2;
	if (l<mid)
		build(l,mid-1),
			son[mid][0]=(l+mid-1)/2,
			fa[(l+mid-1)/2]=mid;
	if (mid<r)
		build(mid+1,r),
			son[mid][1]=(mid+1+r)/2,
			fa[(mid+1+r)/2]=mid;
	update(mid);
}
void hehe(int &l,int &r)
{
	l=select(l,0);r=select(r,l);
}
void SWAP(int l,int r)
{
	hehe(l,r);
	update1(son[r][0]);splay(son[r][0],0);
}
void INVERT(int l,int r)
{
	hehe(l,r);
	update2(son[r][0]);splay(son[r][0],0);
}
void REPLACE(int l,int r,int k)
{
	hehe(l,r);
	update3(son[r][0],(k=='('?1:-1));splay(son[r][0],0);
}
int QUERY(int l,int r)
{
	hehe(l,r);
	return (1-lmin[son[r][0]])/2+(rmax[son[r][0]]+1)/2;
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",v+2);
	for (int i=2;i<=n+1;i++)
		val[i]=(v[i]=='('?1:-1);
	n+=2;
	root=(1+n)/2;
	build(1,n);
	char op[20],pp[20];
	int l,r;
	while (m--)
	{
//		printf("Query%d\n",i);
		scanf("%s",op);
		if (op[0]=='R')
		{
			scanf("%d%d%s",&l,&r,pp);
			REPLACE(l,r+2,pp[0]);
		}else if (op[0]=='S')
		{
			scanf("%d%d",&l,&r);
			SWAP(l,r+2);
		}else if (op[0]=='I')
		{
			scanf("%d%d",&l,&r);
			INVERT(l,r+2);
		}else if (op[0]=='Q')
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",QUERY(l,r+2));
		}
	}
	return 0;
}

