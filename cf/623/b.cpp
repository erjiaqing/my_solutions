#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 5;
int arr[maxn], n, a, b;
bool np[maxn];
vector<int> pr, spr;
long long dp[maxn][3];
int main() {
	ios::sync_with_stdio(0);
	for (int i = 2; i < maxn; i++)
		if (!np[i]) {
			pr.push_back(i);
			for (int j = i + i; j < maxn; j += i)
				np[j] = true;
		}
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	int a1 = arr[1] - 1, a2 = arr[1], a3 = arr[1] + 1;
	int a4 = arr[n] - 1, a5 = arr[n], a6 = arr[n] + 1;
	for (int r : pr) {
		if (a1 % r == 0 || a2 % r == 0 || a3 % r == 0 ||
			a4 % r == 0 || a5 % r == 0 || a6 % r == 0) {
			spr.push_back(r);
			while (a1 % r == 0) a1 /= r;
			while (a2 % r == 0) a2 /= r;
			while (a3 % r == 0) a3 /= r;
			while (a4 % r == 0) a4 /= r;
			while (a5 % r == 0) a5 /= r;
			while (a6 % r == 0) a6 /= r;
		}
	}
	if (a1 != 1) spr.push_back(a1);
	if (a2 != 1) spr.push_back(a2);
	if (a3 != 1) spr.push_back(a3);
	if (a4 != 1) spr.push_back(a4);
	if (a5 != 1) spr.push_back(a5);
	if (a6 != 1) spr.push_back(a6);
	long long ans = 0x3f3f3f3f3f3f3f3fll;
	for (int p : spr) {
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = -1; j <= 1; j++) {
				if (arr[i] + j != 1 && (arr[i] + j) % p == 0) {
					dp[i][0] = min(dp[i][0], dp[i - 1][0] + (j != 0) * b);
					dp[i][2] = min(dp[i][2], dp[i - 1][2] + (j != 0) * b);
				}
			}
			dp[i][1] = min(dp[i][1], dp[i - 1][0] + a); // Start
			dp[i][1] = min(dp[i][1], dp[i - 1][1] + a); // Continue
			dp[i][2] = min(dp[i][2], dp[i][1]); // End
		}
		ans = min(ans, min(dp[n][0], dp[n][2]));
	}
	cout << ans << endl;
	return 0;
}
