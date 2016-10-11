#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int dp[21][1 << 20][2];
int n, m;

long long sqr(long long x) {return x * x % mod;}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int c, k, mask(0);
		scanf("%d%d", &c, &k);
		for (int j = 0; j < k; j++)
		{
			int a;
			scanf("%d", &a);
			mask |= (1 << (a - 1));
		}
		dp[0][mask][0] += c;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < (1 << n); j++)
		{
			int p = ((j >> (n - i)) << (n - i));
			int s = j & ((1 << (n - i)) - 1);
			int rs = (1 << (n - i - 1));
			int cs = (s & rs);
			if (cs)
			{
				dp[i + 1][p | (s - cs)][0] += dp[i][j][0];
				dp[i + 1][p | (s - cs)][1] += dp[i][j][1];
				dp[i + 1][p | rs | (s - cs)][1] += dp[i][j][0];
				dp[i + 1][p | rs | (s - cs)][0] += dp[i][j][1];
			}
			else
			{
				dp[i + 1][p | (s - cs)][0] += dp[i][j][0];
				dp[i + 1][p | (s - cs)][1] += dp[i][j][1];
				dp[i + 1][p | rs | (s - cs)][0] += dp[i][j][0];
				dp[i + 1][p | rs | (s - cs)][1] += dp[i][j][1];
			}
		}
	}
	long long ans = 0;
	for (int j = 0; j < (1 << n); j++)
		ans += sqr(dp[n][j][1]);
	printf("%lld\n", ans % mod);
	return 0;
}
