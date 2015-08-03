#include <bits/stdc++.h>
using namespace std;
const int maxn = 360 + 5;
const int mod = 1e9 + 7;

long long c[maxn][maxn];
long long dp[maxn][maxn];

int main()
{
	c[0][0] = 1;
	for (int i = 1 ; i < maxn ; i++)
	{
		c[i][0] = 1;
		for (int j = 1 ; j <= i ; j++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
	}                    // Prepare
	for (int i = 0 ; i < maxn ; i++)
		dp[0][i] = 1;
	for (int i = 1 ; i < maxn ; i++)
		dp[1][i] = 1;
	for (int i = 2 ; i < maxn ; i++)
	{
		// i 个点，深度为j , 左子树有k个点
		for (int j = 1 ; j < maxn ; j++)
		{
			(dp[i][j] += (((dp[i - 1][j - 1]) * 2) % mod * i) % mod) %= mod;
			for (int k = 1 ; k < i - 1 ; k++)
			{
				// 左子树，右子树
				// 最大的在右边,左右子树有C(i-2,k)种选法
				(dp[i][j] += (((((dp[k][j - 1] * dp[i - k - 1][j - 1]) % mod) * c[i - 2][k]) % mod) * i) % mod) %= mod;
			}
		}
	}
	int n , d , t;
	scanf("%d" , &t);
	for (int i = 1 ; i <= t ; i++)
	{
		scanf("%d%d" , &n , &d);
		printf("Case #%d: %lld\n" , i , ((dp[n][d] - dp[n][d - 1]) % mod + mod) % mod);
	}
	return 0;
}
