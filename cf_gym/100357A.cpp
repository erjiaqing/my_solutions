#include <bits/stdc++.h>

using namespace std;

double dp[1005][105];
int n, m, s;

typedef pair<int, int> pw;
#define p first
#define w second
pw r[25];

int main()
{
	freopen("casino.in", "r", stdin);
	freopen("casino.out", "w", stdout);
	cin >> n >> m >> s;
	for (int t = 0; t <= 1000; t++)
	for (int i = n + 1; i <= n + 50; i++) dp[t][i] = 1;
	for (int i = 0; i < m; i++)
		cin >> r[i].p >> r[i].w;
	for (int t = 1; t <= 1000; t++)
	for (int i = n; i >= 1; i--)
		for (int j = 0; j < m; j++)
			dp[t][i] = max(max(dp[t - 1][i], dp[t][i]), dp[t - 1][i + r[j].w] * 1.0 * r[j].p / s + dp[t - 1][i - 1] * 1.0 * (s - r[j].p) / s);
//	double ans = 0;
//	double current = 1;
	printf("%.20f\n", dp[1000][n]);
	return 0;
}
