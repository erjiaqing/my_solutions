#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;
vector<int> e[maxn];
int color[maxn];
int colo;

set<int> availcolor;

void dfs(int u, int fa, int facolo)
{
	vector<int> tc;
	availcolor.erase(color[u]);
	for (int v : e[u])
	{
		if (v == fa) continue;
		tc.push_back(color[v] = *availcolor.begin());
		availcolor.erase(availcolor.begin());
	}
	availcolor.insert(tc.begin(), tc.end());
	if (facolo != -1) availcolor.insert(facolo);
	for (int v : e[u])
	{
		if (v == fa) continue;
		dfs(v, u, color[u]);
	}
	if (facolo != -1) availcolor.erase(facolo);
	availcolor.insert(color[u]);
}

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) availcolor.insert(i);
	color[1] = 1;
	dfs(1, -1, -1);
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, color[i]);
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++) printf("%d%c", color[i], " \n"[i == n]);
	return 0;
}
