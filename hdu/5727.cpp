#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
int seq[9];
int mp[10][10];
int n, m;

int match[maxn * 2], check[maxn * 2], pre[maxn * 2];
vector<int> e[maxn * 2];

bool dfs(int u)
{
	for (int v : e[u])
		if (!check[v])
		{
			check[v] = 1;
			if (match[v] == -1 || dfs(match[v]))
			{
				match[v] = u;
				match[u] = v;
				return true;
			}
		}
	return false;
}

int hungarian()
{
	int ans = 0;
	memset(match, -1, sizeof(int) * (n * 2));
	for (int u = 0; u < n * 2; u++)
		if (match[u] == -1)
		{
			memset(check, 0, sizeof(int) * (n * 2));
			if (dfs(u))
				ans++;
		}
	return ans;
}

int hungarian_()
{
	queue<int> q;
	int ans = 0;
	memset(match, -1, sizeof(int) * (n * 2));
	memset(check, -1, sizeof(int) * (n * 2));
	for (int i = 0; i < n * 2; i++)
	{
		if (match[i] == -1)
		{
			while (!q.empty()) q.pop();
			q.push(i);
			pre[i] = -1;
			bool flag = false;
			while (!q.empty() && !flag)
			{
				int u = q.front();
				for (int v : e[u])
				{
					if (check[v] != i)
					{
						check[v] = i;
						q.push(match[v]);
						if (~match[v])
							pre[match[v]] = u;
						{
							int d = u, e = v;
							while (d != -1)
							{
								int t = match[d];
								match[d] = e;
								match[e] = d;
								d = pre[d];
								e = t;
							}
							break;
						}
					}
				}
				q.pop();
			}
			if (~match[i])
				ans++;
		}
	}
	return ans;
}

int checkans()
{
	for (int i = 0; i < n; i++) e[i].clear(), e[i + n].clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mp[seq[j]][i] == 0 && mp[seq[(j + 1) % n]][i] == 0)
				e[j].push_back(i + n),
				e[i + n].push_back(j);
	return hungarian();
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		int a, b;
		memset(mp, 0, sizeof(mp));
		while (m--)
		{
			scanf("%d%d", &a, &b);
			mp[b - 1][a - 1] = 1;
		}
		for (int i = 0; i < n; i++)
			seq[i] = i;
		int ans = n - checkans();
		while (next_permutation(&seq[0], &seq[n - 1]))
			ans = min(ans, n - checkans());
		printf("%d\n", ans);
	}
	return 0;
}
