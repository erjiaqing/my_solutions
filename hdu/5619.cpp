#include <bits/stdc++.h>

using namespace std;

const int maxn = 20 + 2;
struct edg{
	int t, c, v, n;
	edg(){};
	edg(int _t, int _c, int _v, int _n):
		t(_t), c(_c), v(_v), n(_n){}
}e[maxn * maxn * maxn * 2 * 2];

int h[maxn * maxn + maxn];
int staff[maxn][maxn];
int guest[maxn];
int tn = 2;
int te;

int dist[maxn * maxn + maxn], inq[maxn * maxn + maxn], pre[maxn * maxn + maxn];
int ped[maxn * maxn + maxn];

void addedge(int s, int t, int c, int v)
{
	int e1 = te++;
	int e2 = te++;
	e[e1] = edg(t, c, v, h[s]);h[s] = e1;
	e[e2] = edg(s, -c, 0, h[t]);h[t] = e2;
}

bool bfs()
{
	memset(dist, 0x3f, sizeof(int) * tn);
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		int u = q.front();
		inq[u] = 0;
		q.pop();
		for (int eg = h[u]; ~eg; eg = e[eg].n)
		{
			edg &ed = e[eg];
			if (ed.v && dist[u] + ed.c < dist[ed.t])
			{
				dist[ed.t] = dist[u] + ed.c;
				pre[ed.t] = u;ped[ed.t] = eg;
				if (!inq[ed.t])
				{
					q.push(ed.t);
					inq[ed.t] = 1;
				}
			}
		}
	}
	return dist[1] != 0x3f3f3f3f;
}

int mcmf()
{
	int ans = 0;
	int mxf = 0;
	while (bfs())
	{
		int u = 1;
		for (; u; u = pre[u])
		{
			int v = ped[u];
			e[v].v--;
			e[v ^ 1].v++;
		}
		mxf++;
		ans += dist[1];
	}
	return ans;
}

void sol()
{
	int m, n;
	scanf("%d%d", &m, &n);
	memset(h, -1, sizeof(h));
	te = 0;tn = 2;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			staff[i][j] = tn++;
			addedge(staff[i][j], 1, 0, 1);
		}
	for (int i = 1; i <= n; i++)
	{
		guest[i] = tn++;
		addedge(0, guest[i], 0, 1);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			int t;
			scanf("%d", &t);
			for (int k = 1; k <= n; k++)
				addedge(guest[i], staff[j][k], k * t, 1);
		}
	printf("%d\n", mcmf());
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
