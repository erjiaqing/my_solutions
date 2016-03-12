#include <cstdio>
using namespace std;
const int maxn = 2005;
const int mod = 1000000007;
int dp[maxn][27][4];
int ans[maxn];
int main() {
	dp[0][0][0] = 1;
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= 26; i++) dp[1][i][1] = 1;
	ans[1] = 26;
	for (int i = 2; i <= 2000; i++) {
		for (int j = 1; j <= 26; j++) {
			for (int k = 1; k <= 26; k++) {
				for (int l = 1; l <= 3 - (j == k); l++) {
					if (j == k) {
						(dp[i][j][l + 1] += dp[i - 1][k][l]) %= mod;
					} else {
						(dp[i][j][1] += dp[i - 1][k][l]) %= mod;
					}
				}
			}
		}
		for (int j = 1; j <= 26; j++) {
			for (int l = 1; l <= 3; l++) (ans[i] += dp[i][j][l]) %= mod;
		}
	}
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
