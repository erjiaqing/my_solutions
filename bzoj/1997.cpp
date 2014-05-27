#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=205;
int Map[maxn][maxn];
struct edge{
	int x,y;
	edge(){}
	edge(int _x,int _y):
		x(_x),y(_y){}
}e2[maxn*maxn];
vector<int>e[maxn],d[10005];
typedef vector<int>::iterator ii;
int h[maxn],pos[maxn];
int n,m,u,v;
int te2;
bool flag;
int c[10005];
void clear()
{
	memset(Map,0,sizeof(Map));
	memset(c,-1,sizeof(c));
	for (int i=1;i<maxn;i++)
		e[i].clear();
	te2=0;
}
bool hehe(int x1,int y1,int x2,int y2)
{
	if (x1==x2||x1==y2||y1==x2||y1==y2)
		return false;
	x1=pos[x1],y1=pos[y1];
	x2=pos[x2],y2=pos[y2];
	if (x1>y1)swap(x1,y2);
	return (x1<x2 && x2<y1)!=(x1<y2 && y2<y1);
}
void color(int x,int cc)
{
	for (ii y=d[x].begin();y!=d[x].end();y++)
		if (~c[*y])
		{
			if (c[*y]!=1-cc)
			{
				flag=false;
				return;
			}
		}else 
			color(*y,1-cc);
}
void work()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i=1;i<=n;i++)
		scanf("%d",&h[i]),pos[h[i]]=i;
	for (int i=2;i<=n;i++)
		Map[h[i-1]][h[i]]=Map[h[i]][h[i-1]]=1;
	Map[h[n]][h[1]]=Map[h[1]][h[n]]=1;
	if (m>n*3-6)
	{
		printf("NO\n");
		return;
	}
	for (u=1;u<=n;u++)
		for (ii v=e[u].begin();v!=e[u].end();v++)
			if (!Map[u][*v])
				e2[++te2]=edge(u,*v);
	for (int i=1;i<=te2;i++)
		d[i].clear();
	for (int i=1;i<=te2;i++)
		for (int j=i+1;j<=te2;j++)
			if (hehe(e2[i].x,e2[i].y,e2[j].x,e2[j].y))
				d[i].push_back(j),d[j].push_back(i);
	flag=true;
	for (int i=1;i<=te2;i++)
	{
		if (c[i]==-1)
		{
			color(i,1);
			if (!flag)
				break;
		}
	}
	printf("%s\n",(flag)?("YES"):("NO"));
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
		work();
	return 0;
}
