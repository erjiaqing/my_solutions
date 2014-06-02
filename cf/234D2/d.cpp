#include <bits/stdc++.h>
using namespace std;
const int maxn=100005,maxk=505;
struct edge{
	int u,v,c;
	edge(){}
	void read()
	{
		scanf("%d %d %d",&u,&v,&c);
	}
	bool operator < (const edge &a) const{return c<a.c;}
}e[maxn];
vector <pair<int,int> > ve[maxn];
typedef vector <pair<int,int> >::iterator vii;
int dist[maxk][maxk];
int ci[maxn];
int belong[maxn];
int vis[maxn];
int c2333[maxk];
int n,m,k,tot;
void check(int u)
{
	vis[u]=true;
	for (vii v=ve[u].begin();v!=ve[u].end();v++)
		if (!vis[v->first] && v->second==0)
			check(v->first);
}
void GetInner()
{
	sort(&e[0],&e[m]);
	for (int i=1;i<=k;i++)
		dist[i][i]=0;
	for (int i=0;i<m;i++)
	{
		if (belong[e[i].u]!=belong[e[i].v])
		{
			dist[belong[e[i].u]][belong[e[i].v]]=min(dist[belong[e[i].u]][belong[e[i].v]],e[i].c);
			dist[belong[e[i].v]][belong[e[i].u]]=dist[belong[e[i].u]][belong[e[i].v]];
		}
	}
}
int main()
{
	memset(dist,0x3f,sizeof(dist));
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=k;i++)
		scanf("%d",&ci[i]);
	for (int i=0;i<m;i++)
	{
		e[i].read();
		ve[e[i].u].push_back(make_pair(e[i].v,e[i].c));
		ve[e[i].v].push_back(make_pair(e[i].u,e[i].c));
	}
	tot=1;
	for (int i=1;i<=k;i++)
	{
		memset(vis,0,sizeof(vis));
		for (int j=tot;j<tot+ci[i];j++)
			belong[j]=i;
		check(tot);
		for (int j=tot;j<tot+ci[i];j++)
			if (!vis[j])
			{
				printf("No\n");
				return 0;
			}
		tot+=ci[i];
	}
	GetInner();
	for (int l=1;l<=k;l++)
		for (int i=1;i<=k;i++)
			for (int j=1;j<=k;j++)
				dist[i][j]=min(dist[i][l]+dist[l][j],dist[i][j]);
	printf("Yes\n");
	for (int i=1;i<=k;i++)
		for (int j=1;j<=k;j++)
			printf("%d%c",dist[i][j]==0x3f3f3f3f?-1:dist[i][j],j==k?'\n':' ');
	return 0;
}
