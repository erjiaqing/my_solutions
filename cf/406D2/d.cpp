#include <bits/stdc++.h>
using namespace std;

const int maxn = 1048579;

typedef pair<int, int> pii;
typedef pair<long long, int> pli;
vector<pii> e[maxn * 4];
int eid[maxn];
long long ans[maxn];

#define ls(x) ( ( x ) << 1 )
#define rs(x) ( ( x ) << 1 | 1 )

void range_add(int x, int ql, int qr, int l, int r, int v, int w, int dir)
{
	if (ql == l && qr == r)
	{
		if (dir) e[x].push_back(pii(v, w));
		else e[v].push_back(pii(x + 524288, w));
		return;
	}
	int mid = (l + r) / 2;
	if (qr <= mid) range_add(ls(x), ql, qr, l, mid, v, w, dir);
	else if (ql > mid) range_add(rs(x), ql, qr, mid + 1, r, v, w, dir);
	else
		range_add(ls(x), ql, mid, l, mid, v, w, dir),
		range_add(rs(x), mid + 1, qr, mid + 1, r, v, w, dir);
}

void build(int x, int l, int r)
{
	e[x].push_back(pii(x / 2, 0));
	e[(x / 2) + 524288].push_back(pii(x + 524288, 0));
	if (l == r)
	{
		e[x].push_back(pii(x + 524288, 0));
		e[x + 524288].push_back(pii(x, 0));
		eid[l] = x;
		return;
	}
	int mid = (l + r) / 2;
	build(ls(x), l, mid);
	build(rs(x), mid + 1, r);
}

int main()
{
	ios::sync_with_stdio(0);
	int n, m, s;
	cin >> n >> m >> s;
	build(1, 1, n);
	for (int i = 0; i < m; i++)
	{
		int t, l, r, x, w;
		cin >> t;
		if (t > 1)
		{
			cin >> x >> l >> r >> w;
			range_add(1, l, r, 1, n, eid[x], w, t & 1);
		} else
		{
			cin >> x >> l >> w;
			e[eid[x]].push_back(pii(eid[l], w));
		}
	}
	priority_queue<pli, vector<pli>, greater<pli> > pq;
	pq.push(pli(0, eid[s]));
	memset(ans, 0x3f, sizeof ans);
	ans[eid[s]] = 0;
	while (!pq.empty())
	{
		pli ux = pq.top();pq.pop();
		if (ux.first != ans[ux.second]) continue;
		long long uv = ux.first;
		int u = ux.second;
		for (pii& v : e[u])
			if (v.second + uv < ans[v.first])
				pq.push(pli(ans[v.first] = v.second + uv, v.first));
	}
	for (int i = 1; i <= n; i++) printf("%lld%c", ans[eid[i]] == 0x3f3f3f3f3f3f3f3f ? -1 : ans[eid[i]], " \n"[i == n]);
	return 0;
}

