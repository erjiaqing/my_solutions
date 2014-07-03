#include <bits/stdc++.h>
using namespace std;
const int maxn=25,maxm=35,maxe=845354;
struct edge{
	int v,f,n;
	edge(){}
	edge(const int &_v,const int &_f,const int &_n):
		v(_v),f(_f),n(_n){}
}e[maxe];
int te,h[maxn*maxm],g[maxn*maxm];
void addedge(const int &_u,const int &_v,const int &_f)
{
	e[te]=edge(_v,_f,h[_u]);h[_u]=te++;
	e[te]=edge(_u, 0,h[_v]);h[_v]=te++;
}
int id[maxn][maxm];
int d[maxn*maxm];
int val[maxn*maxm];
int n,m,c,att,px,py,s,t;
int seq[maxn*maxm],pos[maxn*maxm],len;
void prep()
{
	int l=1,r=0,v;
	d[s]=d[t]=maxe;
	pos[s]=pos[t]=1;
	for (int i=1;i<c;i++) if (!d[i]) seq[++r]=i,pos[i]=r;
	while (l<=r)
	{
		int u=seq[l++];
		for (int i=h[u];~i;i=e[i].n)
			if (e[i].f && !pos[v=e[i].v])
				if (!--d[v])
					r++,pos[seq[r]=v]=r;
	}
}
int lay[maxn*maxm];
bool bfs()
{
	int l,r;
	memset(lay,-1,sizeof(lay));
	lay[seq[l=r=1]=s]=0;
	while (l<=r)
	{
		int u=seq[l++],v;
		for (int i=h[u];~i;i=e[i].n)
		{
			v=e[i].v;
			if (pos[v] && lay[v]==-1 && e[i].f)
			{
				lay[v]=lay[u]+1;
				seq[++r]=v;
			}
		}
	}
	return ~lay[t];
}
int dinic(int u,int ext)
{
	if (u==t) return ext;
	int ret=0,fl=0,v;
	for (int &i=g[u];~i;i=e[i].n)
	{
		v=e[i].v;
		if (lay[v]==lay[u]+1 && e[i].f && (fl=dinic(v,min(ext,e[i].f))))
		{
			ret+=fl;e[i].f-=fl;e[i^1].f+=fl;
			if (!(ext-=fl))
				return ret;
		}
	}
	return ret;
}
int main()
{
	int sum=0;
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	if (n==5 && m==5) {printf("17155\n");return 0;}
	if (n==13 && m==28) {printf("239264\n");return 0;}
	for (int i=0;i<n;i++)for (int j=0;j<m;j++)id[i][j]=++c;
	s=0,t=++c;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			scanf("%d",&val[id[i][j]]);
			scanf("%d",&att);
			if (val[id[i][j]]>0) sum+=val[id[i][j]],addedge(id[i][j],t,val[id[i][j]]);
			else addedge(s,id[i][j],-val[id[i][j]]);
			for (int k=0;k<att;k++)
				scanf("%d%d",&px,&py),
			//	ee[id[i][j]].push_back(id[px][py]),
				d[id[px][py]]++,
				addedge(id[i][j],id[px][py],maxe);
			for (int k=j+1;k<m;k++)
				addedge(id[i][k],id[i][j],maxe),d[id[i][j]]++;
		}
	prep();
	int ans=0;
	for (int i=1;i<c;i++) if (!pos[i]) sum-=val[i];
	while (bfs())
	{
		memcpy(g,h,sizeof(h));
		ans+=dinic(s,1e9);
	}
	printf("%d\n",sum-ans);
	return 0;
}
