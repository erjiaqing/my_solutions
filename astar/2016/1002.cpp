#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 18;
long long dp[1 << 16][17];
bool ded[1 << 16][17];
long long a[maxn];
int p[maxn];
int use[maxn];
int n;
long long ans = 0;

long long dfs(int u, int pos, int x)
{
	if (pos == n + 1) return 0;
	if (ded[u][x]) return dp[u][x];
	ded[u][x] = true;
	if (use[pos] != -1)
	{
		int tt = use[pos];
		return dp[u][x] = a[x] * a[tt] + dfs(u | (1 << (tt - 1)), pos + 1, tt); 
	}
	for (int i = 1; i <= n; i++)
		if (p[i] == -1 && (u & (1 << (i - 1))) == 0)
			dp[u][x] = max(dp[u][x], a[x] * a[i] + dfs(u | (1 << (i - 1)), pos + 1, i));
	return dp[u][x];
}

void sol()
{
	scanf("%d", &n);
	memset(dp, 0xA0, sizeof(dp));
	memset(use, -1, sizeof(use));
	memset(ded, 0, sizeof(ded));
	dp[0][0] = 0;
	use[0] = 0;
	a[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%d", &a[i], &p[i]);
		if (p[i]+1)
			use[p[i]+1] = i;
	}
	printf("%lld\n", dfs(0, 1, 0));
}

int main()
{
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
	{
		printf("Case #%d:\n", i);
		sol();
	}
	return 0;
}
