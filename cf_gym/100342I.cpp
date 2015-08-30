#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
const int maxn = 20000 + 1;
typedef pair<int, int> pii;
vector<int> e[maxn];
vector<int> ce[maxn];
vector<int> eu[maxn * 2];
int flg[maxn];
int low[maxn], dfn[maxn], vis[maxn];
int sze[maxn];
int ans[maxn];
int up[maxn * 2], dn[maxn * 2], sz[maxn * 2];
bool cut[maxn];
void dfs(int u, int father, int dep)
{
	vis[u] = 1;
	dfn[u] = low[u] = dep;
	int children = 0;
	for (int i = 0; i < e[u].size(); i++)
	{
		int v = e[u][i];
		if (vis[v] == 1) low[u] = min(low[u], dfn[v]);
		if (vis[v] == 0)
		{
			dfs(i, dep + 1);
			children++;
			if (low[v] < low[u]) low[u] = low[v];
			if ((father == -1 && children > 1) || (father != -1 && low[v] > dfn[u]))
				cut[u] = true;
			if (low[v] > dfn[u])
			{
				ce[u].push_back(v);
				ce[v].push_back(u);
			}
		}
	}
	vis[u] = 2;
}
void build_dfs_tree(int u, int nid)
{
	flg[u] = true;
	if (cur[u])
	{
		sze[u] = 1;
		eu[u].push_back[nid];
		eu[nid].push_back[u];
	}else
	{
		sze[nid]++;
	}
	for (int i = 0; i < e[u].size(); i++)
	{
		int v = e[u][i];
		if (!flg[v])
			build_dfs_tree(v, nid);
	}
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			dfs(1, -1, 0);
	for (int i = 1; i <= n; i++)
		if (!flg[i])
			build_dfs_tree(i, n + i);
	return 0;
}
