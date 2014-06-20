#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=4005;
struct Point{
	int x,y;
	Point (){}
	Point (const int &_x,const int &_y):
		x(_x),y(_y){}
	friend bool operator < (const Point &a,const Point &b)
	{return (a.x<b.x)||(a.x==b.x && a.y<b.y);}
}p[maxn];
struct edge{
	short v,f,c;
	int n;
	edge(){}
	edge(const short &_v,const short &_f,const short &_c,const int &_n):
		v(_v),f(_f),c(_c),n(_n){}
}e[5000000];
int h[maxn],te,tp;
int n,tx,ty;
void addedge(const int &u,const int &v,const int &f,const int &c)
{
	int e1=te++,e2=te++;
	e[e1]=edge(v,f, c,h[u]);h[u]=e1;
	e[e2]=edge(u,0,-c,h[v]);h[v]=e2;
}
void addsingle(const int &u,const int &v,const int &f,const int &c)
{
	e[te]=edge(v,f,c,h[u]);h[u]=te++;
}
short dis[maxn];
bool inq[maxn];
int pre[maxn],edg[maxn],s,t,ss;
queue<int>Q;
bool spfa()
{
	int u,v,ve;
	memset(dis,-1,sizeof(dis));
//	memset(pre,-1,sizeof(pre));
//	memset(edg,-1,sizeof(edg));
	Q.push(0);dis[0]=0;pre[0]=-1;
	while (!Q.empty())
	{
		u=Q.front();Q.pop();inq[u]=false;
		for (ve=h[u];~ve;ve=e[ve].n)
		{
			v=e[ve].v;
			if (e[ve].f && dis[v]<dis[u]+e[ve].c)
			{
				dis[v]=dis[u]+e[ve].c;
				pre[v]=u;
				edg[v]=ve;
				if (!inq[v])
					Q.push(v),inq[v]=true;
			}
		}
	}
	return ~dis[t];
}
int maxflow()
{
	short u,v,tf=10000,ans=0;
	while (spfa())
	{
		tf=10000;
		for (u=pre[v=t];~u;u=pre[v=pre[v]])
			tf=min(tf,e[edg[v]].f);
		ans+=dis[t]*tf;
		for (u=pre[v=t];~u;u=pre[v=pre[v]])
			e[edg[v]].f-=tf,e[edg[v]^1].f+=tf;
	}
	return ans;
}
int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d",&n);
	s=0;t=n*2+3;/*ss=t-2;*/
	for (int i=1;i<=n;i++)
		scanf("%d%d",&tx,&ty),p[i]=Point(tx,ty);
	sort(&p[1],&p[n+1]);
	for (int i=1;i<=n;i++) dis[i]=1;
	for (int i=1;i<=n;i++) pre[i]=-1;
	for (int i=2;i<=n;i++)
		for (int j=1;j<i;j++)
			if (p[i].y>=p[j].y && dis[i]<dis[j]+1)
				dis[i]=dis[j]+1,pre[i]=j;
	int ans=0,now=0;
	int st,ed;
	for (int i=1;i<=n;i++) 
		if (dis[i]>ans)
			ans=dis[i],now=i;
	ed=now;
	bool bl[maxn];memset(bl,0,sizeof(bl));
	while (~now)
	{
		bl[now]=true;
		st=now;
		now=pre[now];
	}
	for (int i=1;i<=n;i++)
		if (bl[i])
			addedge(i+n,i,1,-1);
		else
			addedge(i,i+n,1,1);
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			if (p[i].x <= p[j].x && p[i].y <= p[j].y)
			{
				if (bl[i] && bl[j] && pre[j]==i)
					addedge(j,i+n,1,0);
				else
					addedge(i+n,j,1,0);
			}
	addsingle(s,t-2,1,0);addsingle(t-2,s,1,0);
	addsingle(t-1,t,1,0);addsingle(t,t-1,1,0);
	for (int i=1;i<=n;i++)
	{
		if (i!=st)
			addedge(t-2,i,1,0);
		else
			addedge(i,t-2,1,0);
		if (i!=ed)
			addedge(i+n,t-1,1,0);
		else
			addedge(t-1,i+n,1,0);
	}
	memset(bl,0,sizeof(bl));
	ans+=maxflow();
	printf("%d\n",ans);
	return 0;
}
