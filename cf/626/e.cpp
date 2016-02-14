#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 1;
int n, mxi = 1, mxj = 0;
double mxa = 0;
int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	vector<int> a(n + 1);
	vector<long long> prefix(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a.begin(), a.end());
	for (int i = 1; i <= n; i++)
		prefix[i] = prefix[i - 1] + a[i];
	for (int i = 1; i <= n; i++) {
		int tj = 0, rj = 0;
		double lxa = 0;
		for (int j = 1 << 30; j; j >>= 1) {
			int nj = tj + j;
			double txa;
			if (i - nj < 1 || i + nj > n) continue;
			txa = 1.0 * (prefix[n] - prefix[n - nj] + prefix[i] - prefix[i - nj - 1]) / (nj * 2 + 1) - a[i];
			if (txa > lxa) {
				lxa = txa;
				rj = nj;
			}
			if (i - nj < 2 || i + nj > n - 1) {
				continue;
			} else {
				double txb = 1.0 * (prefix[n] - prefix[n - nj - 1] + prefix[i] - prefix[i - nj - 2]) / (nj * 2 + 3) - a[i];
				if (txa < txb) tj = nj;
			}
		}
		if (lxa > mxa) {
			mxa = lxa;
			mxi = i;
			mxj = rj;
		}
	}
	cout << mxj * 2 + 1 << endl;
	for (int i = mxi - mxj; i < mxi; i++) cout << a[i] << ' ';
	cout << a[mxi];
	for (int i = n - mxj + 1; i <= n; i++) cout << ' ' << a[i];
	cout << endl;
	cerr << mxa << endl;
	return 0;
}
