#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000 + 5;
int dp[maxn][2];
int main()
{
	dp[0][0] = 0;
	dp[0][1] = -1000000000;
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		dp[i][1] = dp[i - 1][0] + a;
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
	}
	printf("%d\n", max(dp[n][0], dp[n][1]));
	return 0;
}
