#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

int dep[maxn], fa[22][maxn];

int n, m;

vector<int> e[maxn];
int vis[maxn];

struct que{
	int x, y, a, d;
	que(){}
	que(int _x, int _y, int _a, int _d):
		x(_x), y(_y), a(_a), d(_d){}
};

void dfs(int u, int f)
{
	fa[0][u] = f;
	for (int v : e[u])
		if (v != f)
		{
			dep[v] = dep[u] + 1;
			dfs(v, u);
		}
}

int lca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int c = 20; c >= 0; c--)
		if (dep[fa[c][u]] >= dep[v])
			u = fa[c][u];
	if (v == u) return v;
	for (int c = 20; c >= 0; c--)
		if (fa[c][u] != fa[c][v])
		{
			u = fa[c][u];
			v = fa[c][v];
		}
	return fa[0][u];
}

void mark(int u)
{
	vis[u] = 1;
	for (int v : e[u])
	{
		if (vis[v] || fa[0][u] == v) continue;
		mark(v);
	}
}

int sol()
{
	memset(dep, -1, sizeof(dep));
	memset(vis, 0, sizeof(vis));
	memset(fa, 0, sizeof(fa));
	dep[1] = 1;
	for (int i = 1; i < maxn; i++) e[i].clear();
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1, 1);
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= n; j++)
			if (fa[i - 1][j])
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
	vector<que> q;
	for (int i = 0; i < m; i++)
	{
		int u, v, a;
		scanf("%d%d", &u, &v);
		a = lca(u, v);
		q.push_back(que(u, v, a, dep[a]));
	}
	sort(q.begin(), q.end(), [](que &a, que &b){return a.d > b.d;});
	int ans = 0;
	for (auto qu : q)
	{
		//cerr << qu.x << ' ' << qu.a << ' ' << qu.y << endl;
		if (vis[qu.x] == 0 && vis[qu.y] == 0)
		{
			ans++;
			mark(qu.a);
		}
	}
	return ans;
}

int main()
{
	while (~scanf("%d%d", &n, &m))
		printf("%d\n", sol());
	return 0;
}
