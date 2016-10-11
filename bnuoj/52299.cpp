#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;

struct node{
	int v, l, r, u, d;
}nd[maxn * maxn];
int tp[maxn], lf[maxn];
int be[maxn], ed[maxn], lbe[maxn], red[maxn], tmp[maxn];
int n, q;
int main()
{
	scanf("%d%d", &n, &q);
	memset(nd, -1, sizeof nd);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int id = i * n + j;
			int lid = -1, uid = -1;
			nd[id].v = id;
			if (i != 0)
				uid = (i - 1) * n + j;
			else
			{
				uid = (n - 1) * n + j;
				tp[j] = id;
			}
			nd[uid].d = id;
			nd[id].u = uid;
			if (j != 0)
				lid = i * n + j - 1;
			else
			{
				lid = i * n + n - 1;
				lf[i] = id;
			}
			nd[lid].r = id;
			nd[id].l = lid;
		}
	}
	for (int i = 0; i < q; i++)
	{
		int t, l, r, d;
		scanf("%d%d%d%d", &t, &l, &r, &d);
		d %= n;
		if (d == 0) continue;
		if (t == 2)
		{
			int cur = tp[l];
			for (int i = 0; i < n; i++)
			{
				be[i] = cur;
				lbe[i] = nd[cur].l;
				cur = nd[cur].d;
			}
			cur = tp[r];
			for (int i = 0; i < n; i++)
			{
				ed[i] = cur;
				red[i] = nd[cur].r;
				cur = nd[cur].d;
			}
			cur = be[d];
			// Change begin of each row;
			for (int j = l; j <= r; j++)
			{
				tp[j] = cur;
				cur = nd[cur].r;
			}
			// Rotate
			for (int j = 0; j < n; j++)
				tmp[j] = be[(j + d) % n];
			if (l == 0)
				for (int j = 0; j < n; j++)
					lf[j] = tmp[j];
			if (l == 0 && r == n - 1) continue;
			for (int j = 0; j < n; j++)
			{
				nd[lbe[j]].r = tmp[j];
				nd[tmp[j]].l = lbe[j];
			}
			for (int j = 0; j < n; j++)
				tmp[j] = ed[(j + d) % n];
			for (int j = 0; j < n; j++)
			{
				nd[red[j]].l = tmp[j];
				nd[tmp[j]].r = red[j];
			}
		} else if (t == 1)
		{
			int cur = lf[l];
			for (int i = 0; i < n; i++)
			{
				be[i] = cur;
				lbe[i] = nd[cur].u;
				cur = nd[cur].r;
			}
			cur = lf[r];
			for (int i = 0; i < n; i++)
			{
				ed[i] = cur;
				red[i] = nd[cur].d;
				cur = nd[cur].r;
			}
			cur = be[d];
			// Change begin of each row;
			for (int j = l; j <= r; j++)
			{
				lf[j] = cur;
				cur = nd[cur].d;
			}
			// Rotate
			for (int j = 0; j < n; j++)
				tmp[j] = be[(j + d) % n];
			if (l == 0)
				for (int j = 0; j < n; j++)
					tp[j] = tmp[j];
			if (l == 0 && r == n - 1) continue;
			for (int j = 0; j < n; j++)
			{
				nd[lbe[j]].d = tmp[j];
				nd[tmp[j]].u = lbe[j];
			}
			for (int j = 0; j < n; j++)
				tmp[j] = ed[(j + d) % n];
			for (int j = 0; j < n; j++)
			{
				nd[red[j]].u = tmp[j];
				nd[tmp[j]].d = red[j];
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		int cur = lf[i];
		for (int j = 0; j < n; j++)
		{
			if (j) printf(" ");
			printf("%d", nd[cur].v);
			cur = nd[cur].r;
		}
		printf("\n");
	}
	return 0;
}
