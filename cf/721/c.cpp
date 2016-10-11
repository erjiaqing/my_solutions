#include <bits/stdc++.h>
using namespace std;

const int maxn = 5002;

vector<int> e1[maxn];
vector<pair<int, int> > e2[maxn];
int prev[maxn][maxn], len[maxn][maxn];
int seq[maxn];
int deg[maxn];
int n, m, t;

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 0; i < m; i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		if (v != 1 && u != n)
		{
			deg[v]++;
			e1[u].push_back(v);
			e2[u].push_back(make_pair(v, c));
		}
	}
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0)
			q.push(i);
	for (int i = 1; i <= n; i++)
	{
		int u = q.front();q.pop();
		seq[i] = u;
		for (int v : e1[u])
		{
			deg[v]--;
			if (deg[v] == 0)
				q.push(v);
		}
	}
	memset(len, 0x3f, sizeof len);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		for (auto nx : e2[seq[i]])
		{
		}
	}
	return 0;
}
