#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

typedef pair<long long, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > pq;
long long dist[maxn];

vector<pii> e[maxn];
int valid[maxn];

int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(pii(w, v));
		e[v].push_back(pii(w, u));
	}
	memset(valid, -1, sizeof valid);
	memset(dist, 0x3f, sizeof dist);
	for (int i = 1; i <= k; i++)
	{
		int u;
		scanf("%d", &u);
		valid[u] = 0;
	}
	for (int i = 1; i <= n; i++)
		if (valid[i]) e[0].push_back(pii(0, i));
	dist[0] = 0;
	pq.push(pii(0, 0));
	while (!pq.empty())
	{
		pii u = pq.top();
		pq.pop();
		if (u.first != dist[u.second]) continue;
		for (pii ee : e[u.second])
		{
			int v = ee.second;
			int w = ee.first;
			if (u.first + w < dist[v])
			{
				dist[v] = u.first + w;
				pq.push(pii(dist[v], v));
			}
		}
	}
	long long ans = 0x3f3f3f3f3f3f3f3fll;
	for (int i = 1; i <= n; i++)
		if (!valid[i]) ans = min(ans, dist[i]);
	printf("%lld\n", ans == 0x3f3f3f3f3f3f3f3f ? -1ll : ans);
	return 0;
}
