#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=1005;
struct edge{int v,c,f,n;edge(int _v,int _c,int _f,int _n):v(_v),c(_c),f(_f),n(_n){}edge(){}}e[maxn*maxn*4];
int h[maxn*2],te;
int S=0,T=2005;
void addedge(int s,int t,int c,int w)
{
	int e1=te++,e2=te++;
	e[e1]=edge(t,-c,w,h[s]),h[s]=e1;
	e[e2]=edge(s,c,0,h[t]),h[t]=e2;
}
int cnt[maxn],pay[maxn],val[maxn],n,k;
int dis[maxn*2],pre[maxn*2],edg[maxn*2],match[maxn*2],inq[maxn*2];
queue<int>Q;
bool spfa()
{
	int u,v,ed;
	memset(dis,0x3f,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	memset(edg,-1,sizeof(edg));
	Q.push(S);
	dis[S]=0;
	while (!Q.empty())
	{
		u=Q.front(),Q.pop();inq[u]=false;
		for (ed=h[u];~ed;ed=e[ed].n)
		{
			v=e[ed].v;
			if (e[ed].f && dis[v]>dis[u]+e[ed].c)
			{
//				printf("%d %d %d %d\n",u,v,dis[v],dis[u]+e[ed].c);
				dis[v]=dis[u]+e[ed].c;
				edg[v]=ed;pre[v]=u;
				if (!inq[v])
				{
					Q.push(v);
					inq[v]=true;
				}
			}
		}
	}
	return ~edg[T];
}
int maxflow()
{
	int u,v,ans=0,tf;
	while (spfa())
	{
		tf=2050;
		for (v=T,u=pre[v];~u;v=u,u=pre[u])
			e[edg[v]].f--,e[edg[v]^1].f++;
		ans+=dis[T];
	}
	return ans;
}
int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&cnt[i],&pay[i]);
		addedge(0,i,pay[i],1);
	}
	scanf("%d",&k);
	for (int i=1;i<=k;i++)
	{
		scanf("%d",&val[i]);
		addedge(i+n,T,0,1);
	}
	sort(&val[1],&val[k+1]);
	for (int i=1;i<=n;i++)
		for (int j=k;j>=1 && val[j]>=cnt[i];j--)
			addedge(i,n+j,0,1);
	int cnt=0,maxf=maxflow();
	for (int i=1;i<=n;i++)
		for (int ed=h[i];~ed;ed=e[ed].n)
			if (e[ed].f==0 && e[ed].v>n)
			{
				match[i]=e[ed].v,cnt++;
				break;
			}
	printf("%d %d\n",cnt,-maxf);
	for (int i=1;i<=n;i++)
		if (match[i])
			printf("%d %d\n",i,match[i]-n);
	return 0;
}
