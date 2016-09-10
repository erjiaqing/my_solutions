#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

int c[maxn], vis[maxn];
set<int> s[2], sr;

vector<int> e[maxn];

bool dfs(int u, int c)
{
	if (::c[u] != -1 && ::c[u] != c) return false;
//	cerr << "--" << u << ' ' << c << endl;
	s[c].insert(u);
	::c[u] = c;
	vis[u] = 1;
	for (int v : e[u])
		if (!vis[v])
		{
//			cerr << "   " << u << " -> " << v << endl;
			if (!dfs(v, c ^ 1))
				return false;
		} else if (::c[v] != (c ^ 1))
			return false;
	return true;
}

int main()
{
	memset(c, -1, sizeof c);
	int n, m;
	int ans = true;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int u, v, cc;
		scanf("%d%d%d", &u, &v, &cc);
//		cerr << u << "<-->" << v << endl;
		if (cc != 1)
		{
			if (c[u] == -1) c[u] = (cc == 2);
			if (c[v] == -1) c[v] = (cc == 2);
			ans = ans && (c[u] == (cc == 2));
			ans = ans && (c[v] == (cc == 2));
		} else {
			e[u].push_back(v);
			e[v].push_back(u);
		}
	}
	if (!ans)
	{
		puts("impossible");
		return 0;
	}
	for (int i = 1; i <= n; i++)
		if (c[i] != -1 && !vis[i])
		{
			s[0].clear();s[1].clear();
//			cerr << i << ' ' << c[i] << endl;
			ans = ans && dfs(i, c[i]);
//			int flg = (s[1].size() < s[0].size());
			sr.insert(s[1].begin(), s[1].end());
		}
	if (!ans)
	{
		puts("impossible");
		return 0;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
		{
			s[0].clear();s[1].clear();
			ans = ans && dfs(i, 0);
			int flg = (s[1].size() < s[0].size());
			sr.insert(s[flg].begin(), s[flg].end());
		}
	if (!ans)
	{
		puts("impossible");
		return 0;
	}
	printf("%d\n", (int) sr.size());
	return 0;
}
