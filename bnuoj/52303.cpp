#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
typedef pair<int, int> pii;

struct edge{
	int v, n;
	edge(){}
	edge(int v, int n):
		v(v), n(n){}
}edg[(maxn + (maxn + 100)) * 2];

int h[maxn], h2[maxn], te;

int n, m, q;
int mark[maxn], fa[maxn], dst[205][maxn], anc[22][maxn], dep[maxn], vis[maxn], cn;
int tq[maxn], qh, qt;

int getfa(int x) {return (fa[x] == x) ? x : (fa[x] = getfa(fa[x]));}
int uni(int x, int y) {return fa[getfa(x)] = getfa(y);}

void addedge(int &u, int v)
{
	edg[te].v = v;
	edg[te].n = u;
	u = te++;
}

void bfs(int u, int *dst)
{
	memset(dst, 0x3f, (sizeof(int)) * (n + 3));
	dst[u] = 0;
	tq[qh = qt = 0] = u;
	while (qh <= qt)
	{
		int u = tq[qh++];
		for (int i = h2[u]; ~i; i = edg[i].n)
		{
			int v = edg[i].v;
			if (dst[v] == 0x3f3f3f3f)
			{
				dst[v] = dst[u] + 1;
				tq[++qt] = v;
			}
		}
	}
}
void build_tree(int u)
{
	vis[u] = 1;
	for (int i = h[u]; ~i; i = edg[i].n)
	{
		int v = edg[i].v;
		if (!vis[v])
		{
			anc[0][v] = u;
			dep[v] = dep[u] + 1;
			build_tree(v);
		}
	}
}
int getlca(int u, int v)
{
	if (dep[u] > dep[v]) swap(u, v);
	int hu = dep[u], hv = dep[v];
	int tu = u, tv = v;
	for (int det = hv - hu, i = 0; det; det >>= 1, i++)
		if (det & 1)
			tv = anc[i][tv];
	if (tu == tv) return tu;
	for (int i = 21; i >= 0; i--)
	{
		if (anc[i][tu] == anc[i][tv])
			continue;
		tu = anc[i][tu];
		tv = anc[i][tv];
	}
	return anc[0][tu];
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	memset(h, -1, sizeof(int) * (n + 2));
	memset(h2, -1, sizeof(int) * (n + 2));
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if (u == v) continue;
		if (getfa(u) == getfa(v))
			mark[u] = mark[v] = 1;
		else {
			uni(u, v);
			addedge(h[u], v);
			addedge(h[v], u);
		}
		addedge(h2[u], v);
		addedge(h2[v], u);
	}
	for (int i = 1; i <= n; i++)
		if (mark[i]) bfs(i, dst[cn++]);
	build_tree(1);
	for (int i = 1; i < 22; i++)
		for (int j = 1; j <= n; j++)
			anc[i][j] = anc[i - 1][anc[i - 1][j]];
	for (int i = 0; i < q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int anc = getlca(u, v);
		int ans = - dep[anc] * 2 + dep[u] + dep[v];
		for (int j = 0; j < cn; j++)
			ans = min(ans, dst[j][u] + dst[j][v]);
		printf("%d\n", ans);
	}
	return 0;
}
