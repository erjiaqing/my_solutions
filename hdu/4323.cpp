#include <bits/stdc++.h>
using namespace std;
const int maxn = 1500 + 5;
char num[maxn][15];
int len[maxn];
char n2[15];
int len2;
int dp[15][15];
int n, m, k;
bool compare(char *s, int len1, int p) {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 0;
	if (abs(len1 - len2) > p) continue;
	for (int i = 1; i <= len2; i++) dp[i][0] = i;
	for (int j = 1; j <= len1; j++) dp[0][j] = j;
	for (int i = 1; i <= len2; i++)
		for (int j = 1; j <= len1; j++)
			if (n2[i] == s[j])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
	return dp[len2][len1] <= p;
}
int match(int _k) {
	int ret = 0;
	for (int i = 0; i < n; i++)
		ret += compare(num[i], len[i], _k);
	return ret;
}
void sol() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", num[i] + 1);
		len[i] = strlen(num[i] + 1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%s %d", n2 + 1, &k);
		len2 = strlen(n2 + 1);
		printf("%d\n", match(k));
	}
}
int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t;) {
		printf("Case #%d:\n", ++i);
		sol();
	}
	return 0;
}
