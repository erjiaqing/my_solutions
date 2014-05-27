#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
const int maxn=20005;
int f[8388610][25];
int need[25],d[25][25],dist[maxn];
int inq[maxn];
vector <pair<int,int> >e[maxn];
typedef vector <pair<int,int> >::iterator piii;
int n,m,k;
int tu,tv,td;
void spfa(int s)
{
	memset(inq,0,sizeof(inq));
	memset(dist,0x3f,sizeof(dist));
	queue <int> Q;
	Q.push(s);
	dist[s]=0;
	int u;
	while (!Q.empty())
	{
		u=Q.front();Q.pop();inq[u]=false;
		for (piii v=e[u].begin();v!=e[u].end();v++)
		{
			if (dist[v->first]>dist[u]+v->second)
			{
				dist[v->first]=dist[u]+v->second;
				if (!inq[v->first])
					Q.push(v->first);
				inq[v->first]=true;
			}
		}
	}
}
int dp(int gone,int u)
{
	if (f[gone][u]!=-1)
		return f[gone][u];
	if (gone==(1<<k)-1)
		return d[u][k+1];
	f[gone][u]=0x3fffffff;
	for (int i=0;i<k;i++)
		if ((gone&(1<<i))==0&&(need[i]&gone)==need[i])
			f[gone][u]=min(f[gone][u],dp(gone|(1<<i),i+1)+d[u][i+1]);
	return f[gone][u];
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&tu,&tv,&td);
		tu--;tv--;
		e[tu].push_back(make_pair(tv,td));
		e[tv].push_back(make_pair(tu,td));
	}
	scanf("%d",&td);
	for (int i=0;i<td;i++)
	{
		scanf("%d%d",&tu,&tv);
		tu-=2;tv-=2;
		need[tv]|=1<<tu;
	}
	for (int i=0;i<=k;i++)
	{
		spfa(i);
		for (int j=0;j<=k;j++)
			d[i][j]=dist[j];
		d[i][k+1]=d[k+1][i]=dist[n-1];
	}
	memset(f,-1,sizeof(f));
	printf("%d\n",dp(0,0));
	return 0;
}
