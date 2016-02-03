#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef pair<long long, long long> pll;
typedef pair<pll, int> pii;
int n;
vector<pii> nds;
pll vec(pll a, pll b) {
	return pll(b.x - a.x, b.y - a.y);
}
long long sze(const pll a, const pll b) {
	return a.x * b.y - a.y * b.x;
}
int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		double tx, ty;
		cin >> tx >> ty;
		nds.push_back(make_pair(make_pair(tx, ty), i + 1));
	}
	sort(nds.begin(), nds.end());
	for (int i = 2; i < n; i++)
		if (sze(vec(nds[i - 1].x, nds[i - 2].x), vec(nds[i - 1].x, nds[i].x)) != 0) {
			cout << nds[i - 2].y << ' ' << nds[i - 1].y << ' ' << nds[i].y << endl;
			break;
		}
	return 0;
}
