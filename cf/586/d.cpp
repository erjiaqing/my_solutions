#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100 + 5;
char mp[3][maxn];
int dp[3][maxn];
int n, k;
void solve()
{
	memset(dp, 0, sizeof(dp));
	memset(mp, 0, sizeof(mp));
	scanf("%d%d", &n, &k);
	for (int i = 0; i < 3; i++)
		scanf("%s", mp[i]);
	for (int i = 0; i < 3; i++)
		if (mp[i][0] == 's')
		{
			dp[i][0] = 1;
#ifdef LOCAL
			printf("> %d\n", i);
#endif
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
		{
			if (i % 3 != 0)
			{
				if (dp[j][i] && (mp[j][i + 1] == '.' || mp[j][i + 1] == 0))
					dp[j][i + 1] = 1;
			}
			else
			{
			if (dp[j][i] == 1 && (mp[j][i] == '.' || mp[j][i] == 's' || mp[j][i] == 0))
			{
#ifdef LOCAL
				printf("%d,%d\n", i, j);
#endif
				for (int w = max(0, j - 1); w <= min(2, j + 1); w++)
					if ( (mp[j][i + 1] == '.' || mp[j][i + 1] == 0) && (mp[w][i + 1] == '.' || mp[w][i + 1] == 0) && (1 || (mp[w][i] == '.' || mp[w][i] == 0)))
						dp[w][i + 1] = 1;
			}
			}
		}
	int ans = 0;
	for (int i = 0; i < 3; i++)
		if (dp[i][n - 1])
			ans++;
	printf("%s\n", ans ? "YES" : "NO");
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		solve();
	return 0;
}
