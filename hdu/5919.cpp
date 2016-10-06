#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

struct node{
	int val, l, r;
}segt[maxn * 20];
int rt[maxn], ans[maxn];
map<int, int> lst;
int tn;
int n, m;

void init()
{
	tn = 0;
	memset(rt, 0, (sizeof(int)) * (n + 1));
	lst.clear();
}

int newnode()
{
	tn++;
	segt[tn].val = segt[tn].l = segt[tn].r = 0;
	return tn;
}

void insert(int &x, int y, int l, int r, int q, int v)
{
	if (!x) x = newnode();
	if (l == r) {
		segt[x].val += v;
		return;
	}
	int mid = (l + r) / 2;
	segt[x].val = segt[y].val + v;
	if (q <= mid) {
		segt[x].r = segt[y].r;
		insert(segt[x].l, segt[y].l, l, mid, q, v);
	} else {
		segt[x].l = segt[y].l;
		insert(segt[x].r, segt[y].r, mid + 1, r, q, v);
	}
}

int query(int x, int y, int l, int r, int v)
{
	if (l >= v)
		return segt[x].val - segt[y].val;
	if (l == r) return 0;
	int mid = (l + r) / 2, ans = 0;
	if (mid >= v)
		ans += query(segt[x].l, segt[y].l, l, mid, v);
	ans += query(segt[x].r, segt[y].r, mid + 1, r, v);
	return ans;
}

void sol(int cas)
{
	init();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		int ai;
		scanf("%d", &ai);
		if (lst[ai])
			insert(rt[i], rt[i - 1], 1, n, lst[ai], 1);
		else
			rt[i] = rt[i - 1];
		lst[ai] = i;
	}
	int lastans = 0;
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + lastans) % n + 1;
		r = (r + lastans) % n + 1;
		if (l > r) swap(l, r);
		int totcnt = (r - l + 1) - query(rt[r], rt[l - 1], 1, n, l);
		int kk = (totcnt + 1) / 2;
		for (int j = 1 << 20; j; j >>= 1)
		{
			if (r - j < l) continue;
			if ((r - j - l + 1) - query(rt[r - j], rt[l - 1], 1, n, l) >= kk) r -= j;
		}
		ans[i] = lastans = r;
	}
	printf("Case #%d:", cas);
	for (int i = 1; i <= m; i++) printf(" %d", ans[i]);
	printf("\n");
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) sol(i);
	return 0;
}
