#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=2005;
bool vis[maxn];
vector<int> e[maxn];
typedef vector<int>::iterator ii;
int n;
int stack[maxn],stop;
int scc,dfn[maxn],low[maxn],fi[maxn],did;
void dfs(int u)
{
	int vv;
	dfn[u]=low[u]=++did;
	stack[++stop]=u;
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!fi[*v]) continue;
		if (!dfn[*v])
		{
			dfs(*v);
			low[u]=min(low[u],low[*v]);
		}else
		{
			low[u]=min(low[u],dfn[*v]);
		}
	}
	if (dfn[u]==low[u])
	{
		scc++;
		do
		{
			vv=stack[stop--];
			fi[vv]=false;
		}while (vv!=u);
	}
}
int main()
{
	int u;
	memset(fi,-1,sizeof(fi));
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&u);
			if (u) e[i].push_back(j);
		}
//	bool flag=true;
	for (int i=1;i<=n;i++) if (!dfn[i]) dfs(1);
	printf("%s\n",(scc==1)?"YES":"NO");
	return 0;
}
