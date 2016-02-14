#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 * 5 + 5;
bool used[maxn];
int main() {
	int n, m, n1 = 0, m1 = 0;
	cin >> n >> m;
	used[0] = true;
	while (n || m) {
		if (n > m) {
			while (used[n1])
				n1 += 2;
			used[n1] = true;
			n--;
		} else {
			while (used[m1])
				m1 += 3;
			used[m1] = true;
			m--;
		}
	}
	cout << max(n1, m1) << endl;
	return 0;
}
