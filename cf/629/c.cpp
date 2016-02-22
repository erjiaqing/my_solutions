#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
long long dp[2005][2005];
int s, mis;
char c;
int main() {
	int n, m;
	ios::sync_with_stdio(0);
	cin >> n >> m;
	dp[0][0] = 1;
	for (int i = 1; i <= 2000; i++)
		for (int j = 0; j <= 2000; j++) {
			dp[i][j] = ( dp[i - 1][j + 1] + (j ? dp[i - 1][j - 1] : 0) ) % mod;
		}
	for (int i = 0; i < m; i++) {
		cin >> c;
		if (c == '(') s++;
		else s--;
		mis = min(mis, s);
	}
	int nmm = n - m;
	long long ans = 0;
	for (int i = 0; i <= nmm; i++) {
		for (int j = 0; j <= i; j++) {
			if (j + mis < 0 || (j + s) > nmm - i)
				continue;
			(ans += dp[i][j] * dp[nmm - i][j + s] % mod) %= mod;
		}
	}
	cout << ans << endl;
	return 0;
}
