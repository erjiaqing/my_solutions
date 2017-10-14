#include <bits/stdc++.h>
using namespace std;

const int maxn = 400000 + 5;

int upsize[maxn], dnsize[maxn], ll[maxn], rr[maxn], pos[maxn], ipos[maxn];
int segt[maxn * 4];

vector<int> e[maxn];
int ans[maxn];
int tn;

int n;

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)

void insert(int x, int l, int r, int p, int v)
{
	if (l == r)
	{
		segt[x] = ((v <= n / 2) ? v : 0);
		return;
	}
	int mid = (l + r) / 2;
	if (p <= mid) insert(ls(x), l, mid, p, v);
	else insert(rs(x), mid + 1, r, p, v);
	segt[x] = max(segt[ls(x)], segt[rs(x)]);
}

int query(int x, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
		return segt[x];
	int mid = (l + r) / 2;
	if (qr <= mid) return query(ls(x), l, mid, ql, qr);
	else if (ql > mid) return query(rs(x), mid + 1, r, ql, qr);
	else return max(query(ls(x), l, mid, ql, mid), query(rs(x), mid + 1, r, mid + 1, qr));
}

void dfs(int u, int f)
{
	ipos[ll[u] = pos[u] = ++tn] = u;
	for (int v : e[u])
		if (v != f)
			dfs(v, u);
	rr[u] = tn;
}

void dfs2(int u, int f)
{
	if (f) insert(1, 1, n, pos[f], upsize[u]);
	int flg = 1;
	if (upsize[u] > n / 2)
	{
		int mx = max(ll[u] > 1 ? query(1, 1, n, 1, ll[u] - 1) : 0, rr[u] < n ? query(1, 1, n, rr[u] + 1, n) : 0);
		flg = flg && (upsize[u] - mx <= n / 2);
	}
	for (int v : e[u])
	{
		if (v != f)
		if (dnsize[v] > n / 2)
		{
			int mx = query(1, 1, n, ll[v], rr[v]);
			flg = flg && (dnsize[v] - mx <= n / 2);
		}
	}
	ans[u] = flg;
	for (int v : e[u])
		if (v != f) dfs2(v, u);
	insert(1, 1, n, pos[u], dnsize[u]);
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
	dfs(1, 0);
	for (int i = 1; i <= n; i++) insert(1, 1, n, pos[i], dnsize[i] = rr[i] - ll[i] + 1);
	for (int i = 1; i <= n; i++) upsize[i] = n - dnsize[i];
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}
