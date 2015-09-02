#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 1000 + 5;
vector<int> e[maxn];
bool vis[maxn];
int n;
bool have_ham;
void dfs(int u, int dep)
{
	int nxt = 0;
	if (dep == n)
		have_ham = true;
	vis[u] = true;
	for (int i = 0; i < e[u].size(); i++)
		if (!vis[e[u][i]] && (nxt == 0 || e[nxt].size() > e[e[u][i]].size()))
			nxt = e[u][i];
	if (nxt)
		dfs(nxt, dep + 1);
}
void work()
{
	int u, v;
	have_ham = false;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		e[i].clear();
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	bool flg = true;
	int mindeg = 1e5;
	int mindegnode = 0;
	for (int i = 1; i <= n; i++)
	{
		if (e[i].size() < mindeg)
		{
			mindegnode = i;
			mindeg = e[i].size();
		}
	}
	dfs(mindegnode, 1);
	printf("%s", have_ham ? "YES\n" : "NO\n");
}
int main()
{
	while (~scanf("%d", &n))
		work();
	return 0;
}
