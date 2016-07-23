#include <bits/stdc++.h>
using namespace std;
const int maxn = 3000 + 5;
int n, m;
int cnt[maxn];
vector<int> e[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int tu, tv;
		scanf("%d%d", &tu, &tv);
		e[tu - 1].push_back(tv - 1);
	}
	long long ans = 0;
	for (int i = 0; i < n; i++)
	{
		memset(cnt, 0, sizeof(int) * n);
		for (int v : e[i])
			for (int t : e[v])
				cnt[t]++;
		for (int j = 0; j < n; j++)
		{
			if (i == j) continue;
			ans += cnt[j] * (cnt[j] - 1) / 2;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
