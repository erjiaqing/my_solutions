#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
const int maxn=105,maxm=505;
int f[maxn],scc[maxn],low[maxn],dfn[maxn];
int w[maxn],v[maxn],d[maxn],ind;
int n,m;
vector <int> e[maxn];
vector <int> E[maxn];
typedef vector <int> ::iterator ii;
stack<int> S;
void tarjan(int u)
{
	S.push(u);
	f[u]=true;
	dfn[u]=low[u]=ind++;
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!dfn[*v])
		{
			tarjan(*v);
			low[u]=min(low[u],low[*v]);
		}else if (f[*v])
			low[u]=min(low[u],low[*v]);
	}
	if (dfn[u]==low[u])
	{
		int k;
		do
		{
			k=S.top();
			S.pop();
			f[k]=false;
			scc[k]=u;
		}while (k!=u);
	}
}
int dp[maxn][maxm][2];
void ejqismoe233(int u)
{
	int k=0;
	dp[u][v[u]][0]=w[u];
	for (ii t=E[u].begin();t!=E[u].end();t++)
	{
		ejqismoe233(*t);
		for (int j=0;j<=m;j++)
			dp[u][j][k^1]=dp[u][j][k];
		for (int i=0;i<=m-v[u];i++)
			if (dp[*t][i][1])
			{
				for (int j=v[u];j<=m-i;j++)
				{
					dp[u][j+i][k^1]=max(dp[u][j+i][k^1],
							dp[u][j][k]+dp[*t][i][1]);
				}
			}
		k^=1;
	}
	for (int i=0;i<=m;i++)
		dp[u][i][1]=dp[u][i][k];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&d[i]);
		if (d[i])
			e[i].push_back(d[i]);
	}
	for (int i=1;i<=n;i++)
		if (!dfn[i])
			tarjan(i);
	for (int i=1;i<=n;i++)
	{
		if (scc[i]!=i)
		{
			w[scc[i]]+=w[i];
			v[scc[i]]+=v[i];
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (scc[i]==i)
		{
			if (scc[d[i]]==i)
				E[0].push_back(i);
			else
				E[scc[d[i]]].push_back(i);
		}
	}
	ejqismoe233(0);
	int ans=0;
	for (int i=0;i<=m;i++)
		ans=max(dp[0][i][1],ans);
	printf("%d\n",ans);
	return 0;
}
