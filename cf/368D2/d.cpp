#include <bits/stdc++.h>
using namespace std;

const int maxq = 100000 + 5, maxn = maxq * 10;

struct node{
	int l, r;
	short v;
	void init()
	{
		l = r = -1;
		v = 0;
	}
}nodes[43 * maxn];

int n, m;
int head[maxq], head2[maxq], head3[maxq], tn;
int opans[maxq];

int getid(int i, int j)
{
	return m * (i - 1) + j - 1;
}

int get_node()
{
//	cerr << "req: assign" << tn + 1 << endl;
	nodes[++tn].init();
	return tn;
}

int get(int x, int l, int r, int p)
{
	if (l == r) return nodes[x].v;
	int mid = (l + r) / 2;
	if (p <= mid) return get(nodes[x].l, l, mid, p);
	else return get(nodes[x].r, mid + 1, r, p);
}

int get(int x, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr) return nodes[x].v;
	int mid = (l + r) / 2;
	if (qr <= mid) return get(nodes[x].l, l, mid, ql, qr);
	else if (ql > mid ) return get(nodes[x].r, mid + 1, r, ql, qr);
	else return get(nodes[x].l, l, mid, ql, mid) + 
		get(nodes[x].r, mid + 1, r, mid + 1, qr);
}

void update(int &x, int y, int l, int r, int p, int v)
{
	if (x == -1) x = get_node();
//	printf("update: x%d y%d l%d r%d p%d v%d\n", x, y, l, r, p, v);
	nodes[x].v = nodes[y].v;
	if (l == r)
	{
//		cerr << "before: " << nodes[x].v << endl;
		if (v == 1)
			nodes[x].v = 1;
		else if (v == 2)
			nodes[x].v = 0;
		else if (v == 0)
			nodes[x].v ^= 1;
		return;
	}
	int mid = (l + r) / 2;
	if (p <= mid)
	{
		nodes[x].r = nodes[y].r;
		update(nodes[x].l, nodes[y].l, l, mid, p, v);
	} else
	{
		nodes[x].l = nodes[y].l;
		update(nodes[x].r, nodes[y].r, mid + 1, r, p, v);
	}
	nodes[x].v = nodes[nodes[x].l].v + nodes[nodes[x].r].v;
}

int main()
{
	int q;
	scanf("%d%d%d", &n, &m, &q);
	int proc = 0;
	memset(head, -1, sizeof head);
	memset(head2, -1, sizeof head2);
	head[0] = head2[0] = 0;
	while (q--)
	{
		proc++;
		int op;
		scanf("%d", &op);
		if (op == 1 || op == 2)
		{
			int i, j;
			scanf("%d%d", &i, &j);
			int curstate = get(head2[proc - 1], 1, n, i);
			opans[proc] = opans[proc - 1];
			if (curstate == 1)
			{
				op = 3 - op;
				opans[proc] -= m - get(head[proc - 1], 0, n * m - 1, getid(i, 1), getid(i, m));
			} else
				opans[proc] -= get(head[proc - 1], 0, n * m - 1, getid(i, 1), getid(i, m));
//			printf(">> %d %d %d --> id = %d\n", op, i, j, getid(i, j));
			update(head[proc], head[proc - 1], 0, n * m - 1, getid(i, j), op);
			if (curstate == 1)
				opans[proc] += m - get(head[proc], 0, n * m - 1, getid(i, 1), getid(i, m));
			else
				opans[proc] += get(head[proc], 0, n * m - 1, getid(i, 1), getid(i, m));
			head2[proc] = head2[proc - 1];
		} else if (op == 3)
		{
			int i;
			scanf("%d", &i);
			update(head2[proc], head2[proc - 1], 1, n, i, 0);
			head[proc] = head[proc - 1];
			int curstate = get(head2[proc], 1, n, i);
			int curbook = get(head[proc], 0, n * m - 1, getid(i, 1), getid(i, m));
//			printf(">> %d %d --> curstate = %d\n", op, i, curstate);
			opans[proc] = opans[proc - 1];
			if (curstate == 0)
				opans[proc] -= m - curbook * 2;
			else
				opans[proc] += m - curbook * 2;
		} else
		{
			int i;
			scanf("%d", &i);
			opans[proc] = opans[i];
			head[proc] = head[i];
			head2[proc] = head2[i];
//			tn = head3[i];
		}
//		head3[proc] = tn;
		printf("%d\n", opans[proc]);
	}
	return 0;
}
