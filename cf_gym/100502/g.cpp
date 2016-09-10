#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;

int c[maxn], cs[maxn], css[maxn], vis[maxn], x[maxn], fa[maxn], dp[maxn][maxn * 2];
int sz, tc;

void dfs(int u)
{
	vis[u] = 1;
	int v = x[u];
	if (vis[v] == 1)
	{
		int tmp = u;
		c[u] = ++tc;
		while (tmp != v)
		{
			sz++, tmp = fa[tmp];
			c[tmp] = tc;
		}
		css[tc] = sz + 1;
	} else if (vis[v] == 0)
	{
		fa[v] = u;
		dfs(v);
	}
	vis[u] = 2;
}

int dfs2(int u)
{
	if (c[u]) return c[u];
	return c[u] = dfs2(x[u]);
}

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			sz = 0;
			dfs(i);
		}
	}
	for (int i = 1; i <= n; i++)
		dfs2(i);
	for (int i = 1; i <= n; i++)
		cs[c[i]]++;
//	for (int i = 1; i <= tc; i++) cerr << css[i] << ' ' << cs[i] << endl;
	for (int i = 1; i <= tc; i++)
	{
		int lst = 0;
		for (int j = 0; j <= 1000; j++)
		{
			if (dp[i - 1][j])
			{
				for (int kk = max(lst, j + css[i]); kk <= j + cs[i]; kk++)
					dp[i][kk] = 1;
				lst = max(lst, j + cs[i]);
			}
		}
		for (int j = 0; j <= 1000; j++)
			if (dp[i - 1][j])
				dp[i][j] = 1;
	}
	int ans = 0;
	for (int i = 0; i <= k; i++) if (dp[tc][i]) ans = i;
	cout << ans << endl;
	return 0;
}

