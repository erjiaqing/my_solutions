#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

int n, k;
vector<int> e[maxn];

long long cnt[maxn][5];
long long sum[maxn][5];
long long ans;

void sol(int u, int fa)
{
	cnt[u][0] = 1;
	for (int v : e[u])
	{
		if (v == fa) continue;
		sol(v, u);
		for (int i = 0; i < k; i++)
			for (int j = 0; j < k; j++)
			{
				long long tcnt = cnt[u][i] * cnt[v][j];
				long long m = (i + j + 1) % k;
				long long tsum = cnt[u][i] * sum[v][j] + cnt[v][j] * sum[u][i] + tcnt;
				if (m) tsum += (k - m) * tcnt;
				ans += tsum / k;
			}
		for (int i = 0; i < k; i++)
		{
			cnt[u][(i + 1) % k] += cnt[v][i];
			sum[u][(i + 1) % k] += sum[v][i] + cnt[v][i];
		}
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	sol(1, -1);
	cout << ans << endl;
	return 0;
}
