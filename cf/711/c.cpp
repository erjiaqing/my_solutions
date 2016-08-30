#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;

long long dp[maxn][maxn][maxn], ndp[maxn][maxn][maxn];
long long p[maxn][maxn];
int curc[maxn];
int K, n, m;

int main()
{
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; i++)
		scanf("%d", &curc[i]);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			scanf("%lld", &p[i][j]);
		if (curc[i])
			for (int j = 1; j <= m; j++)
				p[i][j] = 0x3f3f3f3f3f3f3f3f;
		p[i][curc[i]] = 0;
	}
	memset(dp, 0x3f, sizeof dp);
	memset(ndp, 0x3f, sizeof ndp);
	dp[0][0][0] = 0;
	for (int i = 1; i <= m; i++) ndp[0][0][i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int k = 1; k <= min(i, K); k++)
		{
			long long minv, minv2;
			int minc, minc2;
			minv = minv2 = 0x3f3f3f3f3f3f3f3fll;
			minc = minc2 = 0;
			for (int c = 1; c <= m; c++)
			{
				dp[i][k][c] = min(dp[i - 1][k][c], ndp[i - 1][k - 1][c]) + p[i][c];
				if (dp[i][k][c] < minv)
				{
					minv2 = minv;
					minc2 = minc;
					minv = dp[i][k][c];
					minc = c;
				} else if (dp[i][k][c] < minv2)
				{
					minv2 = dp[i][k][c];
					minc2 = c;
				}
			}
			for (int c = 1; c <= m; c++)
			{
				if (c == minc) ndp[i][k][c] = minv2;
				else ndp[i][k][c] = minv;
			}
		}
	}
	long long ans = 0x3f3f3f3f3f3f3f3fll;
	for (int c = 1; c <= m; c++) ans = min(ans, dp[n][K][c]);
	printf("%lld\n", ans == 0x3f3f3f3f3f3f3f3fll ? -1ll : ans);
	return 0;
}
