#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 2;
vector<int> e[maxn];
int n, an;
long long x, y;
int dfs(int nd, int fa) {
	int sc = 0, nsc = 0;
	for (int nx : e[nd]) {
		if (nx == fa) continue;
		int tnsc = dfs(nx, nd);
		sc++;
		if (tnsc <= 1) nsc++;
	}
	an += sc - nsc + max(0, nsc - 2);
	return nsc;
}
int main() {
	ios::sync_with_stdio(0);
	int tu, tv, flg = 0;
	cin >> n >> x >> y;
	for (int i = 1; i < n; i++) {
		cin >> tu >> tv;
		e[tu].push_back(tv);
		e[tv].push_back(tu);
	}
	for (int i = 1; i <= n; i++)
		if (int(e[i].size()) == n - 1) flg = true;
	if (x >= y) {cout << (flg ? x + y * (n - 2) : y * (n - 1)) << endl;return 0;}
	dfs(1, -1);
	cout << an * y + (n - 1 - an) * x << endl;
	return 0;
}
