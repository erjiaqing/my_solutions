#include <bits/stdc++.h>
using namespace std;
const int maxn=55;
const double inf=1e10;
struct edge{
	int v;
	double f;
	int n;
	edge(){}
	edge(const int &_v,const double &_f,const int &_n):
		v(_v),f(_f),n(_n){}
}e[maxn*maxn*4*2*5];
int h[maxn*maxn],te;
int up[maxn][maxn],lt[maxn][maxn],vv[maxn][maxn];
int id[maxn][maxn];
int s,t,p,m,n;
void addedge(int u,int v,double f1,double f2)
{
	e[te]=edge(v,f1,h[u]);h[u]=te++;
	e[te]=edge(u,f2,h[v]);h[v]=te++;
}
int lay[maxn*maxn],g[maxn*maxn],que[maxn*maxn],ql,qr;
bool bfs()
{
	memset(lay,-1,sizeof(lay));
	lay[que[ql=qr=0]=s]=0;
	while (ql<=qr)
	{
		for (int edg=h[que[ql]];~edg;edg=e[edg].n)
			if (e[edg].f && lay[e[edg].v]==-1)
				lay[que[++qr]=e[edg].v]=lay[que[ql]]+1;
		ql++;
	}
	return ~lay[t];
}
double dfs(int u,double flw)
{
	double ret=0,flow;
	if (u==t)
		return flw;
	for (int &edg=g[u];~edg;edg=e[edg].n)
	{
		if (e[edg].f && lay[e[edg].v]==lay[u]+1 && (flow=dfs(e[edg].v,min(flw,e[edg].f))))
		{
			e[edg].f-=flow,e[edg^1].f+=flow,ret+=flow;
			if (!(flw-=flow))
				return ret;
		}
	}
	return ret;
}
double dinic(double r)
{
	double ret=0;te=0;
	memset(h,-1,sizeof(h));
	for (int i=0;i<=n+1;i++)
		for (int j=0;j<=m+1;j++)
			if (i<1 || n<i || j<1 || m<j)
				addedge(id[i][j],t,inf,0);
			else
				addedge(s,id[i][j],vv[i][j],0),ret+=vv[i][j];
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=m;j++)
			addedge(id[i-1][j],id[i][j],r*up[i][j],r*up[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m+1;j++)
			addedge(id[i][j-1],id[i][j],r*lt[i][j],r*lt[i][j]);
	while (bfs())
		memcpy(g,h,sizeof(h)),ret-=dfs(s,inf);
	return ret;
}
int main()
{
	//--prep
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&vv[i][j]);
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&up[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m+1;j++)
			scanf("%d",&lt[i][j]);
	for (int i=0;i<=n+1;i++)
		for (int j=0;j<=m+1;j++)
			id[i][j]=s++;
	t=s++;
	//--finished
	double l=0,r=n*m*100,mid;
	while (r-l>1e-5)
	{
		mid=(r+l)/2;
		if (dinic(mid)>0)
			l=mid;
		else
			r=mid;
	}
	printf("%.3lf\n",l);
	return 0;
}
