#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 1000 + 5;
int deepcnt[maxn];
vector<int> e[maxn];
int n;
void dfs(int u, int fa, int dep)
{
	deepcnt[dep]++;
	for (int i = 0; i < e[u].size(); i++)
		if (e[u][i] != fa)
			dfs(e[u][i], u, dep + 1);
}
void work()
{
	int u, v;
	memset(deepcnt, 0, sizeof(deepcnt));
	for (int i = 1; i <= n; i++)
		e[i].clear();
	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, -1, 1);
	bool flg = true;
	for (int i = 2; i <= n; i++)
		if (deepcnt[i] && deepcnt[i - 1] != 1)
		{
			flg = false;
			break;
		}
		else if (!deepcnt[i])
			break;
	printf("%s", flg ? "YES\n" : "NO\n");
}
int main()
{
	while (~scanf("%d", &n))
		work();
	return 0;
}
