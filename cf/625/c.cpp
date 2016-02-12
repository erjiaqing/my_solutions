#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
int res[maxn][maxn];
int k, n;
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> k;
	int tr = n * n, ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = n; j >= k; j--)
			res[i][j] = tr--;
	for (int i = 1; i <= n; i++)
		for (int j = k - 1; j >= 1; j--)
			res[i][j] = tr--;
	for (int i = 1; i <= n; i++)
		ans += res[i][k];
	cout << ans << endl;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cout << res[i][j] << (j == n ? '\n' : ' ');
	return 0;
}
