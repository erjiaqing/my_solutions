#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,m;
vector<int> e[maxn];
typedef vector<int>::iterator vii;
int dfn[maxn],low[maxn],sta[maxn],ins[maxn],scc[maxn],sze[maxn],scn,top,vid;
int ind[maxn];
void dfs(int u)
{
	dfn[u]=low[u]=++vid;
	sta[++top]=u;ins[u]=1;
	for (vii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!dfn[*v])
		{
			dfs(*v);
			low[u]=min(low[u],low[*v]);
		}else if (ins[*v])
		{
			low[u]=min(low[u],dfn[*v]);
		}
	}
	if (dfn[u]==low[u])
	{
		scn++;
		while (1)
		{
			scc[sta[top]]=scn;
			ins[sta[top]]=0;
			sze[scn]++;
			if (dfn[sta[top]]==low[sta[top]])
			{
				top--;break;
			}
			top--;
		}
	}
}
int main()
{
	int u,v,n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
		scanf("%d%d",&u,&v),e[u].push_back(v);
	for (int i=1;i<=n;i++) if (!dfn[i]) dfs(i);
	for (u=1;u<=n;u++)
		for (vii v=e[u].begin();v!=e[u].end();v++)
			if (scc[u]!=scc[*v])
				ind[scc[*v]]++;
	int ans=0;
	for (u=1;u<=scn;u++) if (ind[u]==0) ans++;
	for (u=1;u<=scn;u++) if (ans>1 && sze[u]==1 && ind[u]==0) {
		ans--;break;}
	printf("%.6lf\n",1-(double(ans))/n);
	return 0;
}
