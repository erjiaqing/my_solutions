#include <bits/stdc++.h>
using namespace std;
const int maxn = 500000 + 5;
long long a, b, t;
long long leftT[maxn];
long long rightT[maxn];
char str[maxn];
int n, ans;
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> a >> b >> t >> str;
	str[n] = str[0];
	for (int i = 0; i < n; i++) {
		if (i)
			rightT[i] = rightT[i - 1] + a;
		rightT[i] += b * (str[i] == 'w') + 1;
		if (rightT[i] <= t)
			ans = max(ans, i + 1);
	}
	for (int i = n; i > 0; i--) {
		if (i != n)
			leftT[i] = leftT[i + 1] + a;
		leftT[i] += b * (str[i] == 'w') + 1;
		if (leftT[i] <= t)
			ans = max(ans, n - i + 1);
	}
/*
	for (int i = 0; i < n; i++) cerr << rightT[i] << ' ';
	cerr << '\n';
	for (int i = 1; i <= n; i++) cerr << leftT[i] << ' ';
	cerr << '\n';
*/
	// Case 3 ( Go right -> left )
	int lt = 1, rt = n - 1;
	for (int i = 0; i < n; i++) {
		while (a * i + leftT[lt] + rightT[i] - rightT[0] > t && lt < n)
			lt++;
		if (a * i + leftT[lt] + rightT[i] - rightT[0] <= t && lt < n)
			ans = max(ans, i + 1 + n - lt);
	}
	// Case 4 ( Go left -> right)
	for (int i = n; i > 0; i--) {
		while (a * (n - i) + leftT[i] + rightT[rt] - rightT[0] > t && rt > 0)
			rt--;
		if (a * (n - i) + leftT[i] + rightT[rt] - rightT[0] <= t && rt > 0)
			ans = max(ans, n - i + 1 + rt);
	}
	ans = min(ans, n);
	cout << ans << endl;
	return 0;
}
