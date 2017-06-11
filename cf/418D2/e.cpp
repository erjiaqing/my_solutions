#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxn = 55;
long long dp[3][maxn][maxn][maxn][maxn];
int n, deg[maxn];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> deg[i];
	int cnt[3] = {0, 0, 0};
	for (int i = 2; i <= 1 + deg[1]; i++)
		deg[i]--;
	dp[1][0][0][0][0] = 1;
	for (int i = 2; i <= n; i++)
	{
		memset(dp[i % 3], 0, sizeof dp[i % 3]);
		int ii = i % 3;
		for (int j = 0; j <= i; j++)
			for (int k = 0; k <= i - j; k++)
				for (int l = 0; l <= i - j - k; l++)
					for (int m = 0; m <= i - j - k - l; m++)
					{
						if (i <= deg[1] + 1)
						{
							if (deg[i] == 1)
							{
								if (l > 0) (dp[ii][j][k][l - 1][m] += l * dp[(ii - 1 + 3) % 3][j][k][l][m]) %= mod;
								if (m > 0) (dp[ii][j][k][l + 1][m - 1] += m * dp[(ii - 1 + 3) % 3][j][k][l][m]) %= mod;
								dp[ii][j][k][l + 1][m] += dp[(ii - 1 + 3) % 3][j][k][l][m];
							} else if (deg[i] == 2)
							{
								if (l >= 2)
									(dp[ii][j][k][l - 2][m] += l * (l - 1) / 2 * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								if (l >= 1)
									(dp[ii][j][k][l][m] += l * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								if (m >= 2)
									(dp[ii][j][k][l + 2][m - 2] += m * (m - 1) / 2 * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								if (m >= 1)
									(dp[ii][j][k][l + 2][m - 1] += m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								if (l && m)
									(dp[ii][j][k][l][m - 1] += l * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								(dp[ii][j][k][l][m + 1] += dp[(i - 1) % 3][j][k][l][m]) %= mod;
							}
							assert(deg[i] != 3);
						} else {
							assert(deg[i] != 1);
							if (deg[i] == 2)
							{
								if (j != 0)
								{
									if (l) (dp[ii][j - 1][k][l - 1][m] += j * l * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (m) (dp[ii][j - 1][k][l + 1][m - 1] += j * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									(dp[ii][j - 1][k][l + 1][m] += j * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								}
								if (k != 0)
								{
									if (l) (dp[ii][j + 1][k - 1][l - 1][m] += k * l * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (m) (dp[ii][j + 1][k - 1][l + 1][m - 1] += k * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									(dp[ii][j + 1][k - 1][l + 1][m] += k * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								}
							} else if (deg[i] == 3)
							{
								if (j != 0)
								{
									if (l >= 2)
										(dp[ii][j - 1][k][l - 2][m] += j * l * (l - 1) / 2 * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (l >= 1)
										(dp[ii][j - 1][k][l][m] += j * l * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (m >= 2)
										(dp[ii][j - 1][k][l + 2][m - 2] += j * m * (m - 1) / 2 * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (m >= 1)
										(dp[ii][j - 1][k][l + 2][m - 1] += j * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (l && m)
										(dp[ii][j - 1][k][l][m - 1] += j * l * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									(dp[ii][j - 1][k][l][m + 1] += j * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								}
								if (k != 0)
								{
									if (l >= 2)
										(dp[ii][j + 1][k - 1][l - 2][m] += k * l * (l - 1) / 2 * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (l >= 1)
										(dp[ii][j + 1][k - 1][l][m] += k * l * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (m >= 2)
										(dp[ii][j + 1][k - 1][l + 2][m - 2] += k * m * (m - 1) / 2 * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (m >= 1)
										(dp[ii][j + 1][k - 1][l + 2][m - 1] += k * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									if (l && m)
										(dp[ii][j + 1][k - 1][l][m - 1] += k * l * m * dp[(i - 1) % 3][j][k][l][m]) %= mod;
									(dp[ii][j + 1][k - 1][l][m + 1] += k * dp[(i - 1) % 3][j][k][l][m]) %= mod;
								}
							}
						}
					}
		if (i >= deg[1] + 1)
			for (int l = 0; l <= n; l++)
				for (int m = 0; m <= n; m++)
					if (l + m)
						(dp[ii][l][m][0][0] += dp[ii][0][0][l][m]) %= mod;
/*/		cerr << "----- " << i << " -----\n";
		for (int j = 0; j <= i; j++)
			for (int k = 0; k <= i; k++)
				for (int l = 0; l <= i; l++)
					for (int m = 0; m <= i; m++)
					{
						if (dp[ii][j][k][l][m])
						{
							cerr << j << ' ' << k << ' ' << l << ' ' << m << ' ' << dp[ii][j][k][l][m] << endl;
						}
					}
/*/
	}
	cout << dp[n % 3][0][0][0][0] << endl;
	return 0;
}
