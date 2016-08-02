#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 100000 + 1;
//typedef pair<int, int> pii;
struct edg{
	int v, n;
}ed[maxn];
int h[maxn];
int deg[maxn];
int n, m, te, curmin;

priority_queue<int> q;

void add_edge(int u, int v)
{
	ed[te].v = v;ed[te].n = h[u];h[u] = te++;
}

void sol()
{
	int n, m;
	long long ans = 0;
	te = 0;
	scanf("%d%d", &n, &m);
	memset(h, -1, sizeof(int) * (n + 1));
	curmin = n;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		deg[v]++;
		add_edge(u, v);
	}
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0)
			q.push(i);
	while (!q.empty())
	{
		int qu = q.top();q.pop();
		curmin = min(curmin, qu);
		ans += curmin;
		for (int tv = h[qu]; ~tv; tv = ed[tv].n)
		{
			deg[ed[tv].v]--;
			if (deg[ed[tv].v] == 0)
				q.push(ed[tv].v);
		}
	}
	printf("%lld\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
