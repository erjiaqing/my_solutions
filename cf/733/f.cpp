#include <bits/stdc++.h>
using namespace std;

namespace ejq{

const int maxn = 200000 + 5;

struct edge{
	int u, v, w, c, id;
}edg[maxn];

typedef pair<int, int> pii;

vector<int> e[maxn];
int dep[maxn];
int fa[maxn], link[maxn], son[maxn], top[maxn], id[maxn], rev[maxn], index;
pii val[maxn];

void dfs1(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	ejq::fa[u] = fa;
	for (int v : e[u])
	{
		if (v == fa) continue;
		dfs1(v, u);
		if (link[v] + 1 > link[u])
		{
			link[u] = link[v] + 1;
			son[u] = v;
		}
	}
}

void dfs2(int u, int fa)
{
	id[u] = ++index;
	rev[index] = u;
	if (son[u])
	{
		top[son[u]] = top[u];
		dfs2(son[u], u);
	}
	for (int v : e[u])
	{
		if (v == fa || v == son[u]) continue;
		top[v] = v;
		dfs2(v, u);
	}
}

pii segt[maxn * 4];

#define ls(x) ((x) * 2)
#define rs(x) (ls(x) + 1)
pii query(int x, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr) return segt[x];
	int mid = (l + r) / 2;
	if (qr <= mid) return query(ls(x), l, mid, ql, qr);
	else if (ql > mid) return query(rs(x), mid + 1, r, ql, qr);
	else return max(query(ls(x), l, mid, ql, mid), query(rs(x), mid + 1, r, mid + 1, qr));
}

void build_segt(int x, int l, int r)
{
	if (l == r)
	{
		segt[x] = val[rev[l]];
		return;
	}
	int mid = (l + r) / 2;
	build_segt(ls(x), l, mid);
	build_segt(rs(x), mid + 1, r);
	segt[x] = max(segt[ls(x)], segt[rs(x)]);
}

pii query(int u, int v)
{
	int fu = top[u], fv = top[v];
	pii ans = pii(-1, -1);
	while (fu != fv)
	{
		if (dep[fu] < dep[fv])
		{
			swap(fu, fv);
			swap(u, v);
		}
		ans = max(ans, query(1, 1, index, id[fu], id[u]));
		u = fa[fu];
		fu = top[u];
	}
	if (dep[u] > dep[v]) swap(u, v);
	if (u != v)
		ans = max(ans, query(1, 1, index, id[u] + 1, id[v]));
	return ans;
}

typedef pair<int, int> pii;
int st[maxn];

set<int> res;
pii curans;
long long ans, rans;

int n, m, s;

int dsu_find(int u)
{
	return (st[u] == u) ? u : (st[u] = dsu_find(st[u]));
}

void dsu_union(int u, int v)
{
	st[dsu_find(u)] = dsu_find(v);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) st[i] = i;
	for (int i = 0; i < m; i++) edg[i].id = i;
	for (int i = 0; i < m; i++)
		scanf("%d", &edg[i].w);
	for (int i = 0; i < m; i++)
		scanf("%d", &edg[i].c);
	for (int i = 0; i < m; i++)
		scanf("%d%d", &edg[i].u, &edg[i].v);
	scanf("%d", &s);
	sort(&edg[0], &edg[m],
			[](const edge &a, const edge &b) {
				return a.w < b.w;
			});
	for (int i = 0; i < m; i++)
	{
		if (dsu_find(edg[i].u) != dsu_find(edg[i].v))
		{
			dsu_union(edg[i].u, edg[i].v);
			ans += edg[i].w;
			e[edg[i].u].push_back(edg[i].v);
			e[edg[i].v].push_back(edg[i].u);
			res.insert(i);
		}
	}
	dfs1(1, -1);
	dfs2(1, -1);
	memset(val, -1, sizeof val);
	for (int i : res)
	{
		int u = edg[i].u;
		int v = edg[i].v;
		if (dep[u] > dep[v])
			val[u] = pii(edg[i].w, i);
		else
			val[v] = pii(edg[i].w, i);
	}

	build_segt(1, 1, index);
	long long rans = ans;
	for (int i = 0; i < m; i++)
	{
		pii tans = query(edg[i].u, edg[i].v);
		long long newedg = edg[i].w - s / edg[i].c;
		if (ans - tans.first + newedg < rans)
		{
			rans = ans - tans.first + newedg;
			curans = pii(tans.second, i);
		}
	}
	printf("%lld\n", rans);
	for (int r : res)
	{
//		cerr << r << endl;
		if (r == curans.first)
			printf("%d %d\n", edg[curans.second].id + 1, edg[curans.second].w - s / edg[curans.second].c);
		else
			printf("%d %d\n", edg[r].id + 1, edg[r].w);
	}
	return 0;
}

}

int main()
{
	return ejq::main();
}
