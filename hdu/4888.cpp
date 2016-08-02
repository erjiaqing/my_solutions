#include <bits/stdc++.h>
using namespace std;

const int maxn = 1020;

struct Graph{
	struct Adj{
		int v, c, b;
		Adj(int _v, int _c, int _b):
			v(_v), c(_c), b(_b){}
		Adj(){}
	};
	int n, S, T, h[maxn], cnt[maxn];
	vector<Adj> adj[maxn];
	void clear()
	{
		for (int i = 0; i < n; i++)
			adj[i].clear();
		n = 0;
	}
	int insert(int u, int v, int c, int d = 0)
	{
		n = max(n, max(u, v) + 1);
		adj[u].push_back(Adj(v, c, adj[v].size()));
		adj[v].push_back(Adj(u, c * d, adj[u].size() - 1));
		return adj[v].size() - 1;
	}
	int maxflow(int _S, int _T)
	{
		S = _S, T = _T;
		fill(h, h + n, 0);
		fill(cnt, cnt + n, 0);
		int flow = 0;
		while (h[S] < n)
			flow += dfs(S, 0x3f3f3f3f);
		return flow;
	}
	int dfs(int u, int flow)
	{
		if (u == T)
			return flow;
		int minh = n - 1, ct = 0;
		for (auto it = adj[u].begin(); flow && it != adj[u].end(); ++it)
		{
			if (it->c)
			{
				if (h[it->v] + 1 == h[u])
				{
					int k = dfs(it->v, min(it->c, flow));
					if (k)
					{
						it->c -= k;
						adj[it->v][it->b].c += k;
						flow -= k;
						ct += k;
					}
					if (h[S] >= n)
						return ct;
				}
				minh = min(minh, h[it->v]);
			}
		}
		if (ct)
			return ct;
		if (--cnt[h[u]] == 0)
			h[S] = n;
		h[u] = minh + 1;
		++cnt[h[u]];
		return 0;
	}
}G;

int hd[maxn], vis[maxn], n, m, k;
int ans[maxn][maxn], vis2[maxn][maxn];
bool dfs(int u, int fa)
{
	vis[u] = 1;
	for (int i = 0; i < G.adj[u].size(); i++)
	{
		if (vis2[u][i] == 0 && G.adj[u][i].c && G.adj[u][i].v != fa)
		{
			vis2[u][i] = 1;
			if (vis[G.adj[u][i].v])
				return true;
			if (dfs(G.adj[u][i].v, u))
				return true;
		}
	}
	vis[u] = 0;
	return false;
}

void sol()
{
	G.clear();
	int S = n + m, T = n + m + 1, su, sv;
	su = sv = 0;
	for (int i = 0; i < n; i++)
	{
		int tu = 0;
		scanf("%d", &tu);
		G.insert(S, i, tu);
		su += tu;
	}
	for (int i = 0; i < m; i++)
	{
		int tv = 0;
		scanf("%d", &tv);
		G.insert(n + i, T, tv);
		sv += tv;
	}
	if (su != sv)
	{
		printf("Impossible\n");
		return;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans[i][j] = G.insert(i, n + j, k);
	int mxf = G.maxflow(S, T);
	if (mxf != su)
	{
		printf("Impossible\n");
		return;
	}
	memset(vis, 0, sizeof(vis));
	memset(hd, 0, sizeof(hd));
	memset(vis2, 0, sizeof(vis2));
	for (int i = 0; i < n + m; i++)
		if (dfs(i, -1))
		{
			printf("Not Unique\n");
			return;
		}
	printf("Unique\n");
	for (int i = 0; i < n; i++)
	{
		int flg = 0;
		for (int j = 0; j < m; j++)
		{
			printf("%s%d", flg ? " " : "", G.adj[j + n][ans[i][j]].c);
			flg = 1;
		}
		printf("\n");
	}
}

int main()
{
	while (~scanf("%d%d%d", &n, &m, &k))
		sol();
	return 0;
}
