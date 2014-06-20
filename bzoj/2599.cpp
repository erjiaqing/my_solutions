#include <bits/stdc++.h>
using namespace std;
const int maxn=200005,maxm=400005,maxc=1000005;
struct edge{
	int v,l,n,m;
	edge(){}
	edge(const int &_v,const int &_l,const int &_n):
		v(_v),l(_l),n(_n),m(1){}
}edg[maxm];
int tot,sz,cur,n,m,now,ans;
int h[maxn],s[maxn],f[maxn],d[maxn],v[maxc],c[maxc],e[maxn];
void addedge(int u,int v,int l)
{
	edg[tot]=edge(v,l,h[u]);h[u]=tot++;
	edg[tot]=edge(u,l,h[v]);h[v]=tot++;
}
void froot(int u,int p)
{
	s[u]=1;f[u]=0;
	for (int k=h[u];~k;k=edg[k].n)
	{
		if (edg[k].m && edg[k].v!=p)
		{
			froot(edg[k].v,u);
			s[u]+=s[edg[k].v];
			f[u]=max(f[u],s[edg[k].v]);
		}
	}
	f[u]=max(f[u],sz-s[u]);
	if (f[u]<f[cur])
		cur=u;
}
void dfs1(int u,int p)
{
	if (d[u]>m)
		return;
	if (v[m-d[u]]==now)
		ans=min(ans,c[m-d[u]]+e[u]);
	for (int k=h[u];~k;k=edg[k].n)
	{
		if (edg[k].m && edg[k].v!=p)
		{
			d[edg[k].v]=d[u]+edg[k].l;
			e[edg[k].v]=e[u]+1;
			dfs1(edg[k].v,u);
		}
	}
}
void dfs2(int u,int p)
{
	if (d[u]>m)
		return;
	if (v[d[u]] != now)
	{
		c[d[u]]=e[u];
		v[d[u]]=now;
	}else
	{
		c[d[u]]=min(c[d[u]],e[u]);
	}
	for (int k=h[u];~k;k=edg[k].n)
		if (edg[k].m && edg[k].v!=p)
			dfs2(edg[k].v,u);
}
void work(int u)
{
	v[0]=now=u+1;
	for (int k=h[u];~k;k=edg[k].n)
	{
		if (edg[k].m)
		{
			d[edg[k].v]=edg[k].l;
			e[edg[k].v]=1;
			dfs1(edg[k].v,u);
			dfs2(edg[k].v,u);
		}
	}
	froot(u,n);
	for (int k=h[u];~k;k=edg[k].n)
	{
		if (edg[k].m)
		{
			edg[k^1].m=false;
			f[n]=sz=s[edg[k].v];
			froot(edg[k].v,cur=n);
			work(cur);
		}
	}
}
int main()
{
	int u,v,l;
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
		scanf("%d%d%d",&u,&v,&l),addedge(u,v,l);
	ans=f[n]=sz=n;
	froot(0,cur=n);
	work(cur);
	printf("%d\n",ans<n?ans:-1);
	return 0;
}
