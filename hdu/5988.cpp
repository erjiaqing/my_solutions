#include <bits/stdc++.h>
using namespace std;

namespace ejq{
	const int maxn = 128, maxm = maxn * maxn;
	int cnt[maxn][maxn];
	struct edge{
		int s, t, v;
		double c;
		int n;
		edge(int s, int t, int v, double c, int n):
			s(s), t(t), v(v), c(c), n(n){}
		edge(){}
	}e[maxm];
	int h[maxn], te;

	int prev[maxn], pred[maxn], inq[maxn];

	int qh, qt, que[maxn + 5];

	double dist[maxn];

	int n, m, s, t;

	int front()
	{
		return que[qh % maxn];
	}

	void pop()
	{
		qh++;
	}

	void push(int v)
	{
		que[(qt++) % maxn] = v;
	}

	void empty()
	{
		qh = qt = 0;
	}

	bool isempty()
	{
		return qh == qt;
	}

	void addedge(int s, int t, int v, double c)
	{
		e[te].s = s;e[te].t = t;
		e[te].v = v;e[te].c = c;e[te].n = h[s];
		h[s] = te++;
		e[te].s = t;e[te].t = s;
		e[te].v = 0;e[te].c = -c;e[te].n = h[t];
		h[t] = te++;
	}

	bool spfa()
	{
		for (int i = 0; i <= t; i++) dist[i] = 1. / 0.;
//		memset(inq, 0, sizeof(inq));
//		memset(prev, -1, sizeof(prev));
		empty();push(s);
		dist[s] = 0;
		inq[s] = 1;
		while (!isempty())
		{
			int u = front();pop();
			for (int ed = h[u]; ~ed; ed = e[ed].n)
			{
				if (e[ed].v > 0)
				{
					int v = e[ed].t;
					double c = e[ed].c;
					if (dist[v] > dist[u] + c + 1e-6)
					{
						dist[v] = dist[u] + c;
						prev[v] = u;
						pred[v] = ed;
						if (!inq[v])
						{
							inq[v] = 1;
							push(v);
						}
					}
				}
			}
			inq[u] = 0;
		}
//		return prev[t] != -1;
		return !isinf(dist[t]);
	}

	double mcmf()
	{
		double ret = 0;
		while (spfa())
		{
			int mxf = 0x7fffffff;
			for (int tu = t; tu != s; tu = prev[tu])
				mxf = min(mxf, e[pred[tu]].v);
			for (int tu = t; tu != s; tu = prev[tu])
				e[pred[tu]].v -= mxf, e[pred[tu] ^ 1].v += mxf;
			ret += dist[t] * mxf;
		}
		return ret;
	}

	void init()
	{
		scanf("%d%d", &n, &m);
		memset(h, -1, sizeof h);
		s = n;t = n + 1;te = 0;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++)
		{
			int si, bi;
			scanf("%d%d", &si, &bi);
			int mi = min(si, bi);
			si -= mi;bi -= mi;
			if (si) addedge(s, i, si, 0);
			if (bi) addedge(i, t, bi, 0);
		}
		for (int i = 0; i < m; i++)
		{
			int ui, vi, ci;
			double pi;
			scanf("%d%d%d%lf", &ui, &vi, &ci, &pi);
			if (ui == vi) continue;
			ui--;vi--;
			if (ci > 0)
			{
				addedge(ui, vi, 1, 0);
				if (ci - 1 > 0) addedge(ui, vi, ci - 1, -log(1 - pi));
			}
		}
		printf("%.2f\n", 1 - exp(-mcmf()));
	}

	int main()
	{
		int t;
		scanf("%d", &t);
		while (t--) init();
		return 0;
	}
}

int main()
{
	return ejq::main();
}
