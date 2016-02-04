#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 2;
long long a[maxn], b[maxn];
int jb[maxn], d[maxn], f[maxn];
int n;
int main() {
	ios::sync_with_stdio(0);
	memset(f, -1, sizeof(f));
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		b[i] += b[i - 1];
	}
	b[n + 1] = 0x3f3f3f3f3f3f3f3fll;
	int cr = 0;
	for (int i = 0; i <= n; i++) {
		while (b[cr + 1] <= a[i]) cr++;
		jb[i] = cr;
		d[i] = a[i] - b[cr];
	}
	for (int i = 0; i <= n; i++) {
		int &tp = f[d[i]];
		if (tp == -1) {
			tp = i;
		} else {
			cout << i - tp << endl;
			for (int j = tp + 1; j <= i; j++)
				cout << j << ' ';
			cout << endl << jb[i] - jb[tp] << endl;
			for (int j = jb[tp] + 1; j <= jb[i]; j++)
				cout << j << ' ';
			cout << endl;
			break;
		}
	}
	return 0;
}
