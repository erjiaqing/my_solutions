#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 55;

struct segtnode{
	int l, r, val;
}pool[maxn * 40];

int totnode;

int newnode()
{
	return ++totnode;
}

typedef pair<int, int> pii;
vector<pii> e[maxn];
vector<long long> dep;
int root[maxn];
int a[maxn], ans[maxn], dfsid[maxn], minusid[maxn], dfsindex;
int n, m;

void push_up(int x)
{
	if (x)
	{
		pool[x].val = pool[pool[x].l].val + pool[pool[x].r].val;
//		cerr << x << endl;
	}
}

void plus1(int &x, int y, int l, int r, int q)
{
	if (x == 0)
	{
		x = newnode();
		pool[x].val = pool[y].val + 1;
	}
	if (l == r)
	{
//		pool[x].val++;
		return;
	}
	int mid = (l + r) / 2;
	if (q <= mid)
	{
		pool[x].r = pool[y].r;
		plus1(pool[x].l, pool[y].l, l, mid, q);
	}
	else
	{
		pool[x].l = pool[y].l;
		plus1(pool[x].r, pool[y].r, mid + 1, r, q);
	}
	push_up(x);
}

int query(int x, int y, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
		return pool[x].val - pool[y].val;
	int mid = (l + r) / 2;
	if (qr <= mid)
		return query(pool[x].l, pool[y].l, l, mid, ql, qr);
	else if (ql > mid)
		return query(pool[x].r, pool[y].r, mid + 1, r, ql, qr);
	else
		return query(pool[x].l, pool[y].l, l, mid, ql, mid) +
			query(pool[x].r, pool[y].r, mid + 1, r, mid + 1, qr);
}

void dfs1(int u, long long deep)
{
	dep.push_back(deep - a[u]);
	minusid[u] = dfsindex;
	for (pii v : e[u])
		dfs1(v.first, deep + v.second);
	dfsid[u] = ++dfsindex;
}

void dfs2(int u, long long deep)
{
	for (pii v : e[u])
		dfs2(v.first, deep + v.second);
	int addid = lower_bound(dep.begin(), dep.end(), deep - a[u]) - dep.begin() + 1;
	int queryid = upper_bound(dep.begin(), dep.end(), deep) - dep.begin();
//	cerr << addid << ' ' << queryid << ' ' << dfsid[u] << ' ' << minusid[u] << endl;
	plus1(root[dfsid[u]], root[dfsid[u] - 1], 1, n + 5, addid);
	ans[u] = query(root[dfsid[u]], root[minusid[u]], 1, n + 5, 1, queryid) - 1;
//	plus1(root[dfsid[u]], root[dfsid[u] - 1], 1, n + 5, addid);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(pii(i, v));
	}
	dfs1(1, 0);
	dep.push_back(0x8000000000000000);
	sort(dep.begin(), dep.end());
	dfs2(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
//	for (int i = 1; i <= n; i++)
//	{
//		printf("%d - %d\n", dfsid[i], minusid[i]);
//	}
	return 0;
}
