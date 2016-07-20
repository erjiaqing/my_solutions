#include <bits/stdc++.h>
using namespace std;

const int maxn = 11, mod = 1000000007;
long long c[maxn * maxn][maxn * maxn];
long long ans[maxn][maxn][maxn * maxn];
long long rans[maxn][maxn];

long long powmod(long long a, long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ret;
}

long long get(int x, int y, int k)
{
	if (x < y)
		return ans[y][x][k];
	return ans[x][y][k];
}

int main()
{
	c[0][0] = 1;
	for (int i = 1; i < maxn * maxn; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j < maxn * maxn; j++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
	}
	ans[1][0][0] = 1;
	for (int i = 1; i < maxn; i++)
		for (int j = 1; j <= i; j++)
		{
			for (int k = 1; k <= i * j; k++)
			{
				ans[i][j][k] = c[i * j][k];
				for (int i0 = 1; i0 <= i; i0++)
				{
					for (int j0 = 0; j0 <= j; j0++)
					{
						for (int k0 = 0; k0 <= min(i0 * j0, k); k0++)
						{
							if (i0 == i && j0 == j) break;
							if ((i - i0) * (j - j0) >= k - k0)
							{
								ans[i][j][k] -=
									c[i - 1][i0 - 1] * c[j][j0] % mod
									* get(i0, j0, k0) % mod
									* c[(i - i0) * (j - j0)][k - k0] % mod;
								ans[i][j][k] += mod;
								ans[i][j][k] %= mod;
							}
						}
					}
				}
			}
		}
	int m, n;
	while (~scanf("%d%d", &m, &n))
	{
		long long rans = 0;
		for (int i = 1; i <= m * n; i++)
			(rans += get(m, n, i) * powmod(2, i)) %= mod;
		printf("%lld\n", rans);
	}
	return 0;
}
