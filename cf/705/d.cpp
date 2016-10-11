#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 * 4 + 2 + 5;
const int maxnn = 5000 + 2;
struct edge{
	int t; // target, cost, volume, next
	long long c;
	int v, n;
	edge(){}
	edge(int _t, long long _c, int _v, int _n):
		t(_t), c(_c), v(_v), n(_n){}
}e[maxn * 8];

long long dist[maxn];
int h[maxn], q[maxn], pre[maxn], ped[maxn], inq[maxn], qh, qt, te, tn;
int x[maxnn], a[maxnn], b[maxnn], c[maxnn], d[maxnn];
const int S = 0, T = 1;

void addedge(int s, int t, long long c, int v)
{
	int e1 = te++;
	int e2 = te++;
	e[e1] = edge(t, c, v, h[s]);h[s] = e1;
	e[e2] = edge(s, -c, 0, h[t]);h[t] = e2;
}

bool bfs()
{
	memset(dist, 0x3f, sizeof(long long) * (tn + 5));
	dist[S] = 0;
	qh = 0;qt = 0;
	q[qt++] = S;
	pre[S] = ped[S] = -1;
	while (qh != qt)
	{
		int u = q[qh++];
//		cerr << u << endl;
		if (qh == maxn) qh = 0;
		inq[u] = 0;
		for (int ee = h[u]; ~ee; ee = e[ee].n)
		{
			int tt = e[ee].t;
//			cerr << tt << ' ' << ee << endl;
			if (e[ee].v && dist[tt] > dist[u] + e[ee].c)
			{
				dist[tt] = dist[u] + e[ee].c;
				pre[tt] = u;
				ped[tt] = ee;
				if (!inq[tt])
				{
					q[qt++] = tt;
					inq[tt] = 1;
					if (qt == maxn) qt = 0;
				}
			}
		}
	}
	return dist[T] != 0x3f3f3f3f3f3f3f3fll;
}

long long mcmf()
{
	long long ans = 0, tmpf = 0;
	while (bfs())
	{
		long long tmpc = dist[T];
		for (int cur = T, cut = ped[T]; ~cut; cur = pre[cur], cut = ped[cur])
		{
			cerr << cur << "<-";
//			cerr << cut << ' ' << cur << endl;
			e[cut].v -= 1;
			e[cut ^ 1].v += 1;
		}
		cerr << S << endl;
		tmpf++;
		ans += tmpc;
	}
	cerr << tmpf << endl;
	return ans;
}

const int oo = 50000;

int main()
{
	int n, s, e;
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &s, &e);
	s--;e--;
	for (int i = 0; i < n; i++)
		scanf("%d", &x[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &c[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &d[i]);
	for (int i = 0; i < n; i++)
		if (i != e)
			addedge(S, i + 2, 0, 1);
	for (int i = 0; i < n; i++)
		if (i != s)
			addedge(i + n + 2, T, 0, 1);
	// Go to nodes smaller than it
	for (int i = 0; i < n; i++)
		addedge(i + 2, i + 2 * n + 2, ((long long)x[i]) + c[i], 1);
	// Go to nodes larger than it
	for (int i = 0; i < n; i++)
		addedge(i + 2, i + 3 * n + 2, ((long long)-x[i]) + d[i], 1);
	// Come from nodes larger than it
	// A.k.a Go to nodes smaller than it
	for (int i = 0; i < n - 1; i++)
		addedge(i + 2 * (n + 1) + 2, i + n + 2, ((long long)-x[i]) + b[i], 1);
	// Come from nodes smaller than it
	// A.k.a Go to nodes larger than it
	for (int i = 1; i < n; i++)
		addedge(i + 3 * (n - 1) + 2, i + n + 2, ((long long)x[i]) + a[i], 1);
	for (int i = 1; i < n; i++)
		addedge(i + 2 * n + 2, i + 2 * (n - 1) + 2, 0, oo);
	for (int i = 0; i < n - 1; i++)
		addedge(i + 3 * n + 2, i + 3 * (n + 1) + 2, 0, oo);
	tn = 4 * n + 2;
	printf("%lld\n", mcmf());
	return 0;
}
