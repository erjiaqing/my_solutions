#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int inf=732158268;
const int maxn=1005,maxm=20005;
struct edge
{
	int v,n,w,c;
	edge(int _v,int _n,int _w,int _c):
		v(_v),n(_n),w(_w),c(_c){}
	edge(){}
}e[maxm];
int n,m,k,tot;
int S,T;
int h[maxn];
void addedge(int s,int t,int w,int c)
{
	int e1=tot++,e2=tot++;
	e[e1]=edge(t,h[s], w,c);h[s]=e1;
	e[e2]=edge(s,h[t],-w,0);h[t]=e2;
}
int pre[maxn],edg[maxn],dis[maxn],inq[maxn];
bool spfa(int s)
{
	queue<int>Q;
	Q.push(s);
	int u,v;
	memset(dis,0x3f,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	memset(inq,0,sizeof(inq));
	dis[s]=0;
	while (!Q.empty())
	{
		u=Q.front();Q.pop();
		inq[u]=false;
		for (int j=h[u];~j;j=e[j].n)
		{
			v=e[j].v;
			if (e[j].c&&(dis[v]>dis[u]+e[j].w))
			{
				dis[v]=dis[u]+e[j].w;
				pre[v]=u;
				edg[v]=j;
				if (!inq[v])
				{
					inq[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[T]!=0x3f3f3f3f;
}
void maxflow()
{
	int tv;
	int maxflow=0,ans1=0,cost=0,tmpflow;
	while (spfa(1))
	{
		tmpflow=inf;
		for (tv=T;~pre[tv];tv=pre[tv])
		{
			tmpflow=min(tmpflow,e[edg[tv]].c);
		}
		if (dis[T])
			break;
		for (tv=T;~pre[tv];tv=pre[tv])
		{
			e[edg[tv]].c-=tmpflow;
			e[edg[tv]^1].c+=tmpflow;
		}
		maxflow+=tmpflow;
	}
	ans1=maxflow;
	while (spfa(0))
	{
		tmpflow=inf;
		for (tv=T;~pre[tv];tv=pre[tv])
			tmpflow=min(tmpflow,e[edg[tv]].c);
		for (tv=T;~pre[tv];tv=pre[tv])
		{
			e[edg[tv]].c-=tmpflow;
			e[edg[tv]^1].c+=tmpflow;
		}
		cost+=tmpflow*dis[T];
	}
	printf("%d %d\n",ans1,cost);
}
int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d%d%d",&n,&m,&k);
	addedge(0,1,0,k);
	int ts,tt,tw,tc;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d%d",&ts,&tt,&tc,&tw);
		addedge(ts,tt,tw,inf);
		addedge(ts,tt,0,tc);
	}
	T=n;
	maxflow();
	return 0;
}
