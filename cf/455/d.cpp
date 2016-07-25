#include <bits/stdc++.h>
using namespace std;
const int maxn = 101005;

struct lnk{
	int v;
	lnk *p, *n;
}lnnk[maxn];

//int part[maxn], pos[maxn];
int totlnk = 0;

int pppp;

#define part(x) (x / pppp)
#define pos(x) (x % pppp)

lnk *bg[400], *ed[400];
int cnt[400][maxn];

typedef lnk* lk_;

lk_ newlink()
{
	return &lnnk[totlnk++];
}

void addnode(lnk *pos, lnk *node)
{
	node->p = pos;
	node->n = pos->n;
	node->p->n = node;
	node->n->p = node;
}

void removenode(lnk *node)
{
	node->n->p = node->p;
	node->p->n = node->n;
}

lk_ remove_last(int p)
{
	lnk *nd = ed[p]->p;
	removenode(nd);
	cnt[p][nd->v]--;
	return nd;
}

void addfront(int p, lnk *node)
{
	addnode(bg[p], node);
	cnt[p][node->v]++;
}

lk_ getnth(int p, int n)
{
	lnk *cur = bg[p];
	for (int i = 0; i <= n; i++)
		cur = cur->n;
	return cur;
}

int countnth(int p, int n, int v)
{
	int res = 0;
	lnk *cur = bg[p];
	for (int i = 0; i <= n; i++)
	{
		cur = cur->n;
		res += (cur->v == v);
	}
	return res;
}

int operation2(int l, int r, int v)
{
	int pl = part(l);
	int pr = part(r);
	int cl = countnth(pl, pos(l) - 1, v);
	int cr = countnth(pr, pos(r), v);
	int ans = cr - cl;
	for (int i = pl; i < pr; i++)
		ans += cnt[i][v];
	return ans;
}

void operation1(int l, int r)
{
	int pl = part(l);
	int pr = part(r);
	lnk *tl = getnth(pl, pos(l) - 1);
	lnk *tr = getnth(pr, pos(r));
	removenode(tr);
	addnode(tl, tr);
	cnt[pr][tr->v]--;
	cnt[pl][tr->v]++;
	for (int pi = pl; pi < pr; pi++)
		addfront(pi + 1, remove_last(pi));
}

int main()
{
	int n;
	scanf("%d", &n);
	pppp = pow(n, 0.618);
	int totpart = (n - 1) / pppp;
	for (int i = 0; i <= totpart; i++)
	{
		bg[i] = newlink();
		ed[i] = newlink();
		bg[i]->n = ed[i];
		ed[i]->p = bg[i];
	}
	int ta = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &ta);
		lnk *l = newlink();
		l->v = ta;
		cnt[part(i)][ta]++;
		addnode(ed[part(i)]->p, l);
	}
	int q = 0;
	int last = 0;
	scanf("%d", &q);
	while (q--)
	{
		int op, x, y, v;
		scanf("%d", &op);
		if (op != 3)
		{
			scanf("%d%d", &x, &y);
			x = (last + x - 1) % n;
			y = (last + y - 1) % n;
			if (y < x) swap(x, y);
		}
		if (op == 1)
		{
			if (y != x)
				operation1(x, y);
		}
		else if (op == 2)
		{
			scanf("%d", &v);
			v = (last + v - 1) % n + 1;
			last = operation2(x, y, v);
			printf("%d\n", last);
		}
	}
	return 0;
}
