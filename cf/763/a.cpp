#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
vector<int> e[maxn];
int c[maxn];
int bel[maxn], sz[maxn], flg[maxn], cnt;
int n;
void dfs(int u, int cc)
{
	bel[u] = cc;
	sz[cc]++;
	for (int v : e[u])
		if (bel[v] == 0 && c[v] == c[u])
			dfs(v, cc);
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	for (int i = 1; i <= n; i++)
		if (bel[i] == 0)
		{
			cnt++;
			dfs(i, i);
		}
	if (cnt == 1)
	{
		printf("YES\n1\n");
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		int tsz = sz[bel[i]];
		flg[bel[i]] = i;
		for (int v : e[i])
		{
			if (flg[bel[v]] != i)
			{
				tsz += sz[bel[v]];
				flg[bel[v]] = i;
			}
		}
//		cerr << tsz << endl;
		if (tsz == n)
		{
			printf("YES\n%d\n", i);
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
