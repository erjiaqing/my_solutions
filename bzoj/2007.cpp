#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>

#define v first
#define c second

using namespace std;
const int maxn=505;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
typedef vpii::iterator vpiii;
vpii e[maxn*maxn];
int p[maxn][maxn],tp;
int inq[maxn*maxn];
int S,T,n;
int tmp;
long long dis[maxn*maxn];
long long spfa()
{
	memset(dis,0x2f,sizeof(dis));
	dis[S]=0;
	queue<int>Q;
	Q.push(S);
	int u;
	while (!Q.empty())
	{
		u=Q.front();Q.pop();inq[u]=false;
		for (vpiii v=e[u].begin();v!=e[u].end();v++)
		{
			if (dis[v->v]>dis[u]+v->c)
			{
				dis[v->v]=dis[u]+v->c;
				if (!inq[v->v])
				{
					inq[v->v]=true;
					Q.push(v->v);
				}
			}
		}
	}
	return dis[T];
}
int main()
{
	S=tp++;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			p[i][j]=tp++;
	T=tp++;
	//--
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		e[0].push_back(pii(p[1][i],tmp));
	}
	for (int i=1;i<n;i++)
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&tmp);
			e[p[i][j]].push_back(pii(p[i+1][j],tmp));
		}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		e[p[n][i]].push_back(pii(T,tmp));
	}
	//--
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		e[p[i][1]].push_back(pii(T,tmp));
		for (int j=1;j<n;j++)
		{
			scanf("%d",&tmp);
			e[p[i][j+1]].push_back(pii(p[i][j],tmp));
		}
		scanf("%d",&tmp);
		e[S].push_back(pii(p[i][n],tmp));
	}
	//--
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		e[p[1][i]].push_back(pii(0,tmp));
	}
	for (int i=2;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&tmp);
			e[p[i][j]].push_back(pii(p[i-1][j],tmp));
		}
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		e[T].push_back(pii(p[n][i],tmp));
	}
	//--
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		e[T].push_back(pii(p[i][1],tmp));
		for (int j=1;j<n;j++)
		{
			scanf("%d",&tmp);
			e[p[i][j]].push_back(pii(p[i][j+1],tmp));
		}
		scanf("%d",&tmp);
		e[p[i][n]].push_back(pii(S,tmp));
	}
	cout<<spfa()<<endl;
	return 0;
}
