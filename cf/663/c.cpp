#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;
const int maxn = 100000 + 1;

typedef pair<int, bool> pib;

#define v first
#define c second

int n, m, c[maxn];

vector<int> s[2], ts[2];
vector<pib> e[maxn];

bool dfs(int tar, int u)
{
	for (pib edg : e[u])
	{
		if (c[edg.v] == -1)
		{
			c[edg.v] = (c[u] ^ edg.c ^ tar);
			ts[c[edg.v]].push_back(edg.v);
			if (!dfs(tar, edg.v)) return false;
		} else {
			if (c[edg.v] != (c[u] ^ edg.c ^ tar))
				return false;
		}
	}
	return true;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		char cc[3];
		cin >> u >> v >> cc;
		e[u].push_back(pib(v, cc[0] == 'B'));
		e[v].push_back(pib(u, cc[0] == 'B'));
	}
	
	bool res[2] = {1, 1};
	for (int t = 0; t < 2; t++)
	{
		memset(c, -1, sizeof(c));
		for (int i = 1; i <= n; i++)
		{
			if (c[i] == -1)
			{
				c[i] = 0;
				ts[0].push_back(i);
				res[t] = (res[t] && dfs(t, i));
				bool flg = (ts[0].size() > ts[1].size());
				s[t].insert(s[t].end(), ts[flg].begin(), ts[flg].end());
				ts[0].clear();
				ts[1].clear();
			}
		}
	}

	// I thought
	// if res[0] = false then
	//   we must have res[1] = false

	int flg = ((res[0] && res[1]) ? (s[0].size() > s[1].size()) : (res[0] ? 0 : (res[1] ? 1 : -1)));
	if (~flg)
	{
		printf("%lu\n", s[flg].size());
		for (int v : s[flg])
			printf("%d ", v);
		printf("\n");
	} else {
		printf("-1\n");
	}
	return 0;
}
