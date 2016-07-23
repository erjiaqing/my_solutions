#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
long long dp[maxn][maxn];
int a, b, c, mod;
int n, m;
char mp[maxn][maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 0; i < m; i++)
		scanf("%s", mp[i]);
	a = b = 0;
	for (int i = 0; i < n; i++)
	{
		int c = 0;
		for (int j = 0; j < m; j++)
			if (mp[j][i] == '1') c++;
		if (c == 1)
			b++;
		if (c == 0)
			a++;
	}
	if (m == 0)  a = n;
	int cur = 0, nxt = 1;
	dp[0][a] = 1;
//	cerr << a << ' ' << b << endl;
	for (int i = 0; i < n - m; i++)
		for (int j = 0; j <= n - m - i; j++)
		{
			int k = 2 * (n - m - i) - 2 * j;
			if (j && k)
				(dp[i + 1][j - 1] += dp[i][j] * j % mod * k % mod) %= mod;
			if (j >= 2) 
				(dp[i + 1][j - 2] += dp[i][j] * ((j * (j - 1) / 2) % mod) % mod) %= mod;
			if (k >= 2)
				(dp[i + 1][j] += dp[i][j] * ((k * (k - 1) / 2) % mod) % mod) %= mod;
		}
	printf("%lld\n", dp[n - m][0]);
	return 0;
}
