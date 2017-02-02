#include <bits/stdc++.h>
using namespace std;
const int maxn = 35;

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int n;
vector<int> e[maxn], e2[maxn];
long long X[maxn], Y[maxn];
int vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for (int v : e[u])
	{
		if (!vis[v])
		{
			e2[u].push_back(v);
			dfs(v);
		}
	}
}
void dfs(int u, long long x, long long y, int cd, long long len)
{
	(cd += 1) %= 4;
	X[u] = x;
	Y[u] = y;
	for (int v : e2[u])
	{
		dfs(v, x + dx[cd] * len, y + dy[cd] * len, (cd + 2) % 4, len / 2 - 1);
		(cd += 1) %= 4;
	}
}
int main()
{
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
	{
		if (e[i].size() > 4)
		{
			puts("NO");
			return 0;
		}
	}
	dfs(1);
	dfs(1, 0, 0, 0, 1ll << 50);
	puts("YES");
	for (int i = 1; i <= n; i++)
		cout << X[i] << ' ' << Y[i] << '\n';
	return 0;
}
