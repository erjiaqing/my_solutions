#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

int segt[maxn * 4], lazy[maxn * 4], num[maxn];

#define ls( x ) ( ( x ) << 1 )
#define rs( x ) ( ls( x ) | 1 )

void push_down(int x)
{
	if (lazy[x])
	{
		segt[ls(x)] += lazy[x];
		segt[rs(x)] += lazy[x];
		lazy[ls(x)] += lazy[x];
		lazy[rs(x)] += lazy[x];
		lazy[x] = 0;
	}
}

void add(int x, int l, int r, int ql, int qr, int v)
{
	if (l == ql && r == qr)
	{
		segt[x] += v;
		lazy[x] += v;
		return;
	}
	push_down(x);
	int mid = (l + r) / 2;
	if (qr <= mid) add(ls(x), l, mid, ql, qr, v);
	else if (ql > mid) add(rs(x), mid + 1, r, ql, qr, v);
	else
		add(ls(x), l, mid, ql, mid, v),
		add(rs(x), mid + 1, r, mid + 1, qr, v);
	segt[x] = max(segt[ls(x)], segt[rs(x)]);
}

int get(int x, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
		return segt[x];
	push_down(x);
	int mid = (l + r) / 2;
	if (qr <= mid) return get(ls(x), l, mid, ql, qr);
	else if (ql > mid) return get(rs(x), mid + 1, r, ql, qr);
	else
		return max(get(ls(x), l, mid, ql, mid),
					get(rs(x), mid + 1, r, mid + 1, qr));
}

int main()
{
	int n;
	scanf("%d", &n);
	memset(num, -1, sizeof(num));
	for (int i = 1; i <= n; i++)
	{
		int o, p, s;
		scanf("%d%d", &p, &o);
		p = n - p + 1;
		if (o)
		{
			scanf("%d", &num[p]);
			add(1, 1, n, p, n, 1);
		}
		if (!o)
		{
			o = -1;
			add(1, 1, n, p, n, -1);
		}
		s = n + 1;
		for (int j = 1 << 25; j; j >>= 1)
			if ((s - j) > 0 && get(1, 1, n, 1, s - j) >= 1)
					s -= j;
		printf("%d\n", num[s]);
	}
	return 0;
}
