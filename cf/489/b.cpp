#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;

int n, m, a[maxn], b[maxn];
vector<int> e[maxn + maxn];
int check[maxn + maxn], pre[maxn + maxn], match[maxn + maxn];


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
	memset(match, -1, sizeof(int) * (n + m));
	for (int u = 0; u < n + m; u++)
		if (match[u] == -1)
		{
			memset(check, 0, sizeof(int) * (n + m));
			if (dfs(u))
				ans++;
		}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d", &b[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (abs(a[i] - b[j]) <= 1)
			{
				e[i].push_back(n + j);
				e[n + j].push_back(i);
			}
	printf("%d\n", hungarian());
	return 0;
}
