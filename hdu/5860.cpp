#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000005;

int cnt[maxn * 4];
int res[maxn];

#define ls(x) ( ( x ) << 1 )
#define rs(x) ( ( x ) << 1 | 1 )

void build(int x, int l, int r)
{
	if (l == r)
	{
		cnt[x] = 1;
		return;
	}
	int mid = (l + r) / 2;
	build(ls(x), l, mid);
	build(rs(x), mid + 1, r);
	cnt[x] = cnt[ls(x)] + cnt[rs(x)];
}

int get(int x, int l, int r, int k)
{
	cnt[x]--;
	if (l == r)
		return l;
	int mid = (l + r) / 2;
	if (cnt[ls(x)] >= k)
		return get(ls(x), l, mid, k);
	else
		return get(rs(x), mid + 1, r, k - cnt[ls(x)]);
}

void getans()
{
	int n, q, k, m;
	scanf("%d%d%d", &n, &k, &m);
	build(1, 1, n);
//	int last = get(1, 1, n, 1);
	int query = n + 3;
	for (int i = 1; i <= n; i++)
	{
		query += k;
		if (query > cnt[1])
			query = 1;
		res[i] = get(1, 1, n, query);
		query--;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &q);
		printf("%d\n", res[q]);
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		getans();
	return 0;
}
