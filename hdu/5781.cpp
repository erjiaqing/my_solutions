#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000 + 5;
int dp[maxn][16];
int main()
{
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i < 16; i++) dp[0][i] = 0;
	dp[1][1] = 2;
	for (int j = 2; j < maxn; j++)
		dp[j][1] = dp[j - 1][1] + j + 1;
	for (int tk = 2; tk < 16; tk++)
		for (int tq = 1; tq < maxn; tq++)
			for (int tw = 1; tw <= tq; tw++)
				dp[tq][tk] = min(dp[tq][tk], dp[tw - 1][tk - 1] + dp[tq - tw][tk] + tq + 1);
	int k, w;
	while (~scanf("%d%d", &k, &w))
		printf("%.6f\n", dp[k][min(w, 15)] / (k + 1.));
}
