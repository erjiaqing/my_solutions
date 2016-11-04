#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
const int maxn = 300000 + 5;
struct node
{
	int mn, lz, an;
	node(){}
	node(const int _mn, const int _lz, const int _an):
		mn(_mn), lz(_lz), an(_an){}
	void pd(const int _v)
	{
		lz += _v;
		mn += _v;
	}
}seg_tree[maxn * 4];
int val[maxn];
char str[maxn];
int n, Q;
set<int> s[2];
#define ls(x) ( ( x ) << 1 )
#define rs(x) ( ls(x) | 1 )
void push_down(int x)
{
	if (seg_tree[x].lz)
	{
		seg_tree[ls(x)].pd(seg_tree[x].lz);
		seg_tree[rs(x)].pd(seg_tree[x].lz);
		seg_tree[x].lz = 0;
	}
}
void add(int x, int l, int r, int ql, int qr, int v)
{
	if (ql <= l && r <= qr)
	{
		seg_tree[x].lz += v;
		seg_tree[x].mn += v;
		return;
	}
	push_down(x);
	int mid = (l + r) / 2;
	if (qr <= mid)
		add(ls(x), l, mid, ql, qr, v);
	else if (mid < ql)
		add(rs(x), mid + 1, r, ql, qr, v);
	else
	{
		add(ls(x), l, mid, ql, mid, v);
		add(rs(x), mid + 1, r, mid + 1, qr, v);
	}
	seg_tree[x].an = 
		seg_tree[ls(x)].mn < 
		seg_tree[rs(x)].mn ?
		seg_tree[ls(x)].an :
		seg_tree[rs(x)].an;
	seg_tree[x].mn = min(seg_tree[ls(x)].mn, seg_tree[rs(x)].mn);
}
int query(int x, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr)
		return x;
	push_down(x);
	int mid = (l + r) / 2;
	if (qr <= mid)
		return query(ls(x), l, mid, ql, qr);
	else if (mid < ql)
		return query(rs(x), mid + 1, r, ql, qr);
	else
	{
		int la = query(ls(x), l, mid, ql, mid),
			ra = query(rs(x), mid + 1, r, mid + 1, qr);
		/*
		printf("query x=%d l=%d r=%d ql=%d qr=%d\n",
				x, l, r, ql, qr);
		printf("la = %d mn = %d | ra = %d mn = %d\n", la, seg_tree[la].mn,
				ra, seg_tree[ra].mn);
		*/
		return seg_tree[la].mn < seg_tree[ra].mn ? la : ra;
	}
}
void build(int x, int l, int r)
{
//	printf("[%d]", x);
	if (l == r)
	{
		seg_tree[x] = node(val[l], 0, l);
//		printf("<%d>", l);
		return;
	}
	int mid = (l + r) / 2;
//	printf("(", x);
	build(ls(x), l, mid);
	build(rs(x), mid + 1, r);
//	printf(")");
	seg_tree[x] = 
		seg_tree[ls(x)].mn < 
		seg_tree[rs(x)].mn ?
		seg_tree[ls(x)] :
		seg_tree[rs(x)];
}
int main()
{
	while(~scanf("%d%d", &n, &Q))
	{
		scanf("%s", str + 1);
		s[0].clear();
		s[1].clear();
		for (int i = 1; i <= n; i++)
		{
			val[i] = val[i - 1] + (str[i] == '(' ? 1 : -1);
			s[str[i] == ')'].insert(i);
		}
		build(1, 0, n);
		while (Q--)
		{
			int q;
			scanf("%d", &q);
			if (str[q] == '(')
			{
				s[1].insert(q);
				s[0].erase(q);
				int ans = *s[1].begin();
				add(1, 0, n, q, n, -2);
				add(1, 0, n, ans, n, 2);
				s[1].erase(ans);
				s[0].insert(ans);
				str[q] = ')';
				str[ans] = '(';
				printf("%d\n", ans);
			} else {
				int ans = seg_tree[query(1, 0, n, 0, q)].an;
				if (ans != q)
				{
					ans += 2;
					add(1, 0, n, q, n, 2);
					add(1, 0, n, ans, n, -2);
					str[q] = '(';
					str[ans] = ')';
					s[0].insert(q);
					s[1].erase(q);
					s[0].erase(ans);
					s[1].insert(ans);
				}
				printf("%d\n", ans);
			}			
		}
	}
	return 0;
}
