#include <bits/stdc++.h>
using namespace std;
const int maxn=500005,inf=1000000007;
struct point{
	int d[2],mk;
	void read(int f)
	{
		mk=f;
		scanf("%d%d",&d[0],&d[1]);
	}
}p[maxn*2],w[maxn],q;
struct kdt{
	int mx[2],mn[2];
	kdt *l,*r,*f;
	point p;
	void update()
	{
		for (int i=0;i<2;i++)
			mx[i]=max(p.mk?-inf:p.d[i],max(l->mx[i],r->mx[i])),
			mn[i]=min(p.mk? inf:p.d[i],min(l->mn[i],r->mn[i]));
	}
}node[maxn*2],*pos[maxn],*rt,*tot=node;
int d,ans;
bool operator < (const point &a,const point &b)
{
	return a.d[d]<b.d[d];
}
void query(kdt *x,int dep)
{
	d=dep;
	if (!x->p.mk)
		ans=min(ans,abs(x->p.d[0]-q.d[0])+abs(x->p.d[1]-q.d[1]));
	if (q<x->p)
	{
		if (x->l!=node)
			query(x->l,dep^1);
		d=dep^1;
		if (x->r!=node && x->r->mn[d^1]-q.d[d^1]+((x->r->mn[d]>q.d[d])?(x->r->mn[d]-q.d[d]):(q.d[d]>x->r->mx[d]?q.d[d]-x->r->mx[d]:0))<ans)
			query(x->r,dep^1);
	}else
	{
		if (x->r!=node)
			query(x->r,dep^1);
		d=dep^1;
		if (x->l!=node && (q.d[d^1]-x->l->mx[d^1])+(x->l->mn[d]>q.d[d]?x->l->mn[d]-q.d[d]:(q.d[d]>x->l->mx[d]?q.d[d]-x->l->mx[d]:0))<ans)
			query(x->l,dep^1);
	}
}
void build(kdt *&x,int l,int r,int dep)
{
	if (l>r)
	{
		x=node;
		return;
	}
	d=dep;
	int mid=(l+r)/2;
	nth_element(&p[l],&p[mid],&p[r+1]);
	(x=++tot)->p=p[mid];
	pos[x->p.mk]=x;
	build(x->l,l,mid-1,dep^1);
	x->l->f=x;
	build(x->r,mid+1,r,dep^1);
	x->r->f=x;
	x->update();
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		p[i].read(0);
	int cnt=n;
	for (int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		w[i].read(x==2);
		if (!w[i].mk)
		{
			p[++cnt]=w[i];
			p[cnt].mk=i;
		}
	}
	node->mx[0]=node->mx[1]=-inf;
	node->mn[0]=node->mn[1]=inf;
	build(rt,1,cnt,0);
	for (int i=1;i<=m;i++)
	{
		if (w[i].mk)
		{
			q=w[i];
			ans=inf;
			query(rt,0);
			printf("%d\n",ans);
		}else
		{
			kdt *x=pos[i];
			x->p.mk=0;
			for (;x!=rt;x=x->f)
				x->update();
			rt->update();
		}
	}
	return 0;
}
