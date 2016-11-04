#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
typedef pair<int, int> pii;
#define x first
#define y second
int n;
pii pt[maxn];
int c[maxn];
long long r[maxn];
vector<int> e[maxn];

long long sqr(long long x) {return x * x;}

int low[maxn], dfn[maxn], sta[maxn], ins[maxn], bel[maxn], ind, tp;
int indeg[maxn], scc, scc_cost[maxn];

void tarjan(int u)
{
	low[u] = dfn[u] = ++ind;
	sta[tp++] = u;ins[u] = true;
	for (int v : e[u])
	{
		if (dfn[v] == -1) {
			tarjan(v);
			if (low[u] > low[v])
				low[u] = low[v];
		} else if (ins[v] && low[u] > dfn[v]) {
			low[u] = dfn[v];
		}
	}
	if (low[u] == dfn[u])
	{
		scc++;
		int v;
		do {
			v = sta[--tp];
			ins[v] = false;
			bel[v] = scc;
			scc_cost[scc] = min(scc_cost[scc], c[v]);
		} while (v ^ u);
	}
}

int sol()
{
	scanf("%d", &n);
	ind = scc = tp = 0;
	for (int i = 0; i <= n; i++)
	{
		low[i] = dfn[i] = -1;
		ins[i] = bel[i] = 0;
		indeg[i] = 0;
		scc_cost[i] = 0x7fffffff;
		e[i].clear();
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%lld%d", &pt[i].x, &pt[i].y, &r[i], &c[i]);
		r[i] = sqr(r[i]);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j) continue;
			if (sqr(pt[i].x - pt[j].x) + sqr(pt[i].y - pt[j].y) <= r[i])
				e[i].push_back(j);
		}
	for (int i = 0; i < n; i++)
		if (dfn[i] == -1)
			tarjan(i);
//	for (int i = 0; i < n; i++)
//	{
//		cerr << "Bomb " << i << " scc" << bel[i] << endl;
//		for (int v : e[i]) cerr << "--->" << v << endl;
//	}
	for (int i = 0; i < n; i++)
		for (int v : e[i])
			if (bel[i] != bel[v])
				indeg[bel[v]]++;
	int ans = 0;
	for (int i = 1; i <= scc; i++)
	{
		if (indeg[i] == 0)
			ans += scc_cost[i];
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %d\n", i, sol());
	return 0;
}
