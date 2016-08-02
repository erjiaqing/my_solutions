#include <bits/stdc++.h>
using namespace std;
#define _________B namespace ejq{
#define _________E }
_________B

double a[205];
double dp[2][205][205][205];
double dp2[17][17][17];
//bool sel[2][205][205][205];
//double dfs()

double sol2(int n, int k)
{
	double ret = 0;
	for (int i = 0; i < (1 << n); i++)
	{
	//	memset(dp2, 0, sizeof(dp2));
//		dp2[0][0] = 1;
		bool flg = 0;
		int cntbit = 0;
		for (int j = 0; j < n; j++)
			if (i & (1 << j)) cntbit++;
		if (cntbit != k)
			continue;
		memset(dp2, 0, sizeof(dp2));
		dp2[0][0][0] = 1;
		int tr = 0;
		for (int j = 0; j < n; j++)
		{
			if ((i & (1 << j)) == 0) continue;
			tr++;
			for (int l = 0; l < k; l++)
				for (int m = 0; m < k; m++)
				{
					dp2[tr][l + 1][m] += dp2[tr - 1][l][m] * a[j];
					dp2[tr][l][m + 1] += dp2[tr - 1][l][m] * (1 - a[j]);
				}
		}
		ret = max(ret, dp2[k][k / 2][k / 2]);
	}
	return ret;
}

double sol()
{
	memset(dp, 0, sizeof(dp));
	//dp[0][0][0][0] = dp[1][n][0][0] = 1;
	int n, k;
	//dp[0][0][0][0] = dp[1][n][0][0] = 1;
	scanf("%d%d", &n, &k);
	dp[0][0][0][0] = dp[1][n][0][0] = 1;
	int c0 = 0, c1 = 0;
	int tr = 0;
	for (int i = 0; i < n; i++)
	{
		double t;
		scanf("%lf", &t);
//		if (t < 1e-8)
//		{
//			c0++;
//		} else if (t > 1-1e-8)
//		{
//			c1++;
//		} else {
			a[tr++] = t;
//		}
	}
	if (n <= 16) return sol2(n, k);
	sort(&a[0], &a[tr], [](double x, double y){
			return (abs(x - 0.5) < abs(y - 0.5));
			});
	int _ = k;
	for (int i = 0; i < _ && i < tr; i++)
		for (int j = 0; j <= _; j++)
			for (int k = 0; k <= _; k++)
			{
				dp[0][i + 1][j + 1][k] += dp[0][i][j][k] * a[i];
				dp[0][i + 1][j][k + 1] += dp[0][i][j][k] * (1 - a[i]);
//				dp[0][j + 1][k] = dp[0][j][k] * a[i];
//				dp[0][j][k + 1] = dp[0][j][k] * (1 - a[i]);
			}
	/*
	for (int i = n - 1; i >= n - _ / 2; i--)
		for (int j = 0; j <= _; j++)
			for (int k = 0; k <= _; k++)
			{
				dp[1][i][j + 1][k] += dp[1][i + 1][j][k] * a[i];
				dp[1][i][j][k + 1] += dp[1][i + 1][j][k] * (1 - a[i]);
//				dp[1][j + 1][k] = dp[1][j][k] * a[i];
//				dp[1][j][k + 1] = dp[1][j][k] * (1 - a[i]);
			}*/
	int tp = k / 2;
	double ans = 0;
//	return dp[0][_][k / 2][k / 2];
	for (int i = 0; i <= c1; i++)
		for (int j = 0; j <= c0; j++)
		{
			if (k / 2 >= i && k / 2 >= j)
			{
				ans = max(ans, dp[0][_ - i - j][k / 2 - i][k / 2 - j]);
			}
		}
	return ans;
	/*
	for (int i = 0; i <= tp; i++)
	{
		cerr << dp[0][tp][i][tp - i] << ' ' << dp[1][n - tp][tp - i][i] << endl;
		ans += dp[0][tp][i][tp - i] * dp[1][n - tp][tp - i][i];
	}
	return ans;*/
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		fprintf(stderr, "Case #%d\n", i);
		printf("Case #%d: %.10f\n", i, sol());
	}
	return 0;
}

_________E
int main()
{
	return ejq::main();
}
