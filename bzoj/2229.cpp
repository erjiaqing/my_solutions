#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxm=3005,maxn=155;
struct edge{int t,v,n;edge(){}edge(int _t,int _v,int _n){t=_t;v=_v;n=_n;}};
edge e[maxm*2];int h[maxn],tote;
int m,n;
int Cut[maxn][maxn];
int cl,p[maxn],vis[maxn],st[maxn];
void addedge(int s,int t,int v)
{
	int e1=tote++,e2=tote++;
	e[e1]=edge(t,v,h[s]);h[s]=e1;
	e[e2]=edge(s,0,h[t]);h[t]=e2;
}
void set()
{
	tote=0;
	memset(h,-1,sizeof(h));
	memset(Cut,0x3f,sizeof(Cut));
}
void read()
{
	int tu,tv,tc;
	set();
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&tu,&tv,&tc);
		addedge(tu,tv,tc);
	}
}
int dep[maxn];
const int inf=24154818;
int S,T;
bool bfs(int s,int t)
{
	int u,v;
	vis[s]=++cl;
	memset(dep,-1,sizeof(dep));
	queue<int>Q;
	Q.push(s);dep[s]=0;
	while (!Q.empty())
	{
		u=Q.front();Q.pop();
		for (int te=h[u];~te;te=e[te].n)
		{
			if (e[te].v && dep[e[te].t]==-1)
			{
				vis[e[te].t]=cl;
				dep[e[te].t]=dep[u]+1;
				Q.push(e[te].t);
			}
		}
	}
	return vis[t]==cl;
}
int dfs(int u,int ma)
{
	if (u==T||!ma)
		return ma;
	int f,flow=0;
	for (int i=h[u];~i;i=e[i].n)
	{
		if (dep[e[i].t]==dep[u]+1 && (f=dfs(e[i].v,min(e[i].v,ma))))
		{
			flow+=f;
			ma-=f;
			e[i].v-=f;e[i^1].v+=f;
			if (!ma)
				return flow;
		}
	}
	dep[u]=inf;
	return flow;
}
int dinic()
{
	int ans=0;
	while (bfs(S,T))
		ans+=dfs(S,inf);
	return ans;
}
void work(int L,int R)
{
	if (L==R)
		return;
	S=st[L];T=st[R];
	for (int i=0;i<tote;i+=2)
	{
		(e[i].v+=e[i^1].v)>>=1;
		e[i^1].v=e[i].v;
	}
	int ans=dinic();
	int LT=L-1,RT=R+1;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			if (vis[i]!=vis[j])
				Cut[i][j]=min(Cut[i][j],ans);
	for (int i=1;i<=n;i++)
	{
		if (p[i]>R||p[i]<L)
			continue;
		if (vis[i]!=cl)
			st[++LT]=i,p[i]=LT;
		else
			st[--RT]=i,p[i]=RT;
	}
	work(L,LT);work(RT,R);
}
void solve(int K)
{
	for (int i=1;i<=n;i++)
		st[i]=p[i]=i;
	work(1,n);
	int q,k,ans;
	scanf("%d",&q);
	while (q--)
	{
		ans=0;
		scanf("%d",&k);
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				ans+=(Cut[i][j]<=k);
		printf("%d\n",ans);
	}
	if (K)
		printf("\n");
}
int main()
{
	int t;
	scanf("%d",&t);
	while (t--)
		read(),solve(t);
}
