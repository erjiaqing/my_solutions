#include <bits/stdc++.h>
using namespace std;
const int maxm=6005,maxn=1005;
const double eps=1e-8,inf=1e10;
struct edge
{
	int v;
	double f;
	int n;
	edge(){}
	edge(const int _v,const double _f,const int _n):
		v(_v),f(_f),n(_n){}
}edg[maxm*10];
pair<int,int> e[maxm];int tot;
int h[maxm],g[maxm];
void addedge(int u,int v,double f)
{
//	int e1=tot++,e2=tot++;
	edg[tot]=edge(v,f,h[u]);h[u]=tot++;
	edg[tot]=edge(u,0,h[v]);h[v]=tot++;
}
int lay[maxm],que[maxm],ql,qr;
int s,t;
bool bfs()
{
	int u,v,ee;
	memset(lay,-1,sizeof(lay));
	que[ql=qr=0]=s;
	lay[s]=0;
	while (ql<=qr)
	{
		u=que[ql++];
		for (ee=h[u];~ee;ee=edg[ee].n)
		{
			v=edg[ee].v;
			if (edg[ee].f && !~lay[v])
				lay[que[++qr]=v]=lay[u]+1;
		}
	}
	return ~lay[t];
}
double dfs(int u,double f)
{
	if (u==t)
		return f;
	double fl,rt=0;
	int v;
	for (int &ee=g[u];~ee;ee=edg[ee].n)
	{
		v=edg[ee].v;
		if (edg[ee].f && lay[v]==lay[u]+1 && (fl=dfs(v,min(edg[ee].f,f))))
		{
			rt+=fl;
			edg[ee].f-=fl;
			edg[ee^1].f+=fl;
			if (!(f-=fl))
				return rt;
		}
	}
	return rt;
}
int m,n;
double dinic(int mid)
{
	double fl=tot=0;
	memset(h,-1,sizeof(h));
	for (int i=1;i<=n;i++)
		addedge(i,t,mid);
	for (int i=1;i<=m;i++)
	{
		addedge(s,n+i,1);
		addedge(n+i,e[i].first,inf);
		addedge(n+i,e[i].second,inf);
	}
	while (bfs())
	{
		memcpy(g,h,sizeof(h));
		fl+=dfs(s,inf);
	}
	return m-fl;
}
int main()
{
	scanf("%d%d",&n,&m);
	if (!m)
	{
		printf("1\n");
		return 0;
	}
	s=0;
	t=n+m+1;
	for (int i=1;i<=m;i++)
		scanf("%d%d",&e[i].first,&e[i].second);
	double l=0,r=m;
	while (r-l>eps)
	{
		double mid=(l+r)/2;
	//	cerr<<mid<<endl;
		if (dinic(mid)>0)
			l=mid;
		else
			r=mid;
	}
//	if (dinic(l+1)<0)
	dinic(l);
	int cnt=0;
	for (int i=1;i<=n;i++)
		if (~lay[i])
			++cnt;
	printf("%d\n",cnt);
	return 0;
}
