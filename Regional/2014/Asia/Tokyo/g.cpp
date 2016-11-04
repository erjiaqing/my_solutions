#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <set>
using namespace std;
#define lb(x) ( (x) & (-(x)))
const int maxn = 300000 + 5;
set<int> s[2];
int n, q;
char str[maxn];
int pref[maxn];
int bufans[maxn];
int seg_tree[maxn * 4];
void add(int p, int v)
{
	for (; p <= n; p += lb(p))
		pref[p] += v;
}
int get(int p)
{
	int ret = 0;
	for (; p; p -= lb(p))
		ret += pref[p];
	return ret;
}
#define ls(x) ( ( x ) << 1 )
#define rs(x) ( ls(x) | 1 )
void update(int x, int ql, int qr, int l, int r)
{
	if (l <= ql && qr <= r)
	{
		bufans[seg_tree[x]] = get(seg_tree[x]);
		return;
	}
	int mid = (ql + qr) / 2;
	int lans = 0x7fffffff, rans = 0x7fffffff;
	if (r <= mid)
	{
		update(ls(x), ql, mid, l, r);
		lans = bufans[seg_tree[ls(x)]];
		rans = bufans[seg_tree[rs(x)]] = get(seg_tree[rs(x)]);
	} else if (mid < l)
	{
		update(rs(x), mid + 1, qr, l, r);
		rans = bufans[seg_tree[rs(x)]];
		lans = bufans[seg_tree[ls(x)]] = get(seg_tree[ls(x)]);
	} else
	{
		update(ls(x), ql, mid, l, mid);
		update(rs(x), mid + 1, qr, mid + 1, r);
		rans = bufans[seg_tree[rs(x)]];
		lans = bufans[seg_tree[ls(x)]];
	}
	seg_tree[x] = lans < rans ? seg_tree[ls(x)] : seg_tree[rs(x)];
}
int query(int x, int ql, int qr, int l, int r)
{
	if (l <= ql && qr <= r)
	{
		bufans[seg_tree[x]] = get(seg_tree[x]);
		return seg_tree[x];
	}
	int mid = (ql + qr) / 2;
	int lans = 0, rans = 0;
	if (r <= mid)
	{
		return query(ls(x), ql, mid, l, r);
	} else if (mid < l)
	{
		return query(rs(x), mid + 1, qr, l, r);
	} else
	{
		lans = query(ls(x), ql, mid, l, mid);
		rans = query(rs(x), mid + 1, qr, mid + 1, r);
		return bufans[lans] < bufans[rans] ? lans : rans;
	}
}
void build(int x, int ql, int qr)
{
	if (ql == qr)
	{
		seg_tree[x] = ql;
		bufans[seg_tree[x]] = get(ql);
		return;
	}
	int mid = (ql + qr) / 2;
	build(ls(x), ql, mid);
	build(rs(x), mid + 1, qr);
	seg_tree[x] = bufans[seg_tree[ls(x)]] < bufans[seg_tree[rs(x)]] ? seg_tree[ls(x)] : seg_tree[rs(x)];
}
void _swap(char &x)
{
	x = (x == ')') ? '(' : ')';
}
int main()
{
	while (~scanf("%d%d", &n, &q))
	{
		scanf("%s", str + 1);
		memset(pref, 0, sizeof(pref));
		s[0].clear();
		s[1].clear();
		add(1, 1);
		for (int i = 2; i < n; i++)
		{
			add(i, str[i] == '(' ? 1 : -1);
			s[str[i] == '('].insert(i);
		}
		add(n, -1);
		build(1, 1, n);
		for (int i = 0; i < q; i++)
		{
			int qu;
			scanf("%d", &qu);
			if (qu == 1 || get(qu) == 0)
			{
				printf("%d\n", qu);
				continue;
			}
			int flg = 0;
			flg = (str[qu] == '(');
			s[!flg].insert(qu);
			s[flg].erase(qu);
			auto ans = s[!flg].begin();
			if (!flg)
			{
				ans = s[!flg].upper_bound(query(1, 1, n, 1, qu));
				if (ans != s[!flg].end()) ans++;
				assert(get(*ans) == 2);
			} else
			{
				ans = s[!flg].begin();
			}
			if (ans == s[!flg].end() || *ans >= qu)
			{
				s[!flg].erase(qu);
				s[flg].insert(qu);
				printf("%d\n", qu);
			} else
			{
				_swap(str[*ans]);
				_swap(str[qu]);
				printf("%d\n", *ans);
				add(qu, flg ? -2 : 2);
				add(*ans, flg ? 2 : -2);
				update(1, 1, n, *ans, qu);
				s[flg].insert(*ans);
				s[!flg].erase(ans);
			}
#ifdef LOCAL
			for (auto r : s[0])
				cerr << r << ' ';
			cerr << endl;
			for (auto r : s[1])
				cerr << r << ' ';
			cerr << endl;
			for (int i = 1; i <= n; i++)
				cerr << get(i) << ' ';
			cerr << endl;
			cerr << (str + 1) << endl;
#endif
		}
	}
	return 0;
}
