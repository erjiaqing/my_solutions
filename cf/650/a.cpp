#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int main() {
	ios::sync_with_stdio(0);
	int n;
	vector<pii> p;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(pii(x, y));
	}
	sort(p.begin(), p.end());
	//for (auto r : p) {cerr << '{' << r.first << ' ' << r.second << endl;}
	//p.push_back(pii(1000000001, 1000000001));
	long long cnt = 1;
	long long ans = 0;
	for (int i = 1; i < n; i++) {
		if (p[i].first == p[i - 1].first) cnt++;
		else {
			ans += (cnt) * (cnt - 1) / 2;
			cnt = 1;
		}
	}
	ans += (cnt) * (cnt - 1) / 2;
	cnt = 1;
	sort(p.begin(), p.end(), [](pii a, pii b){return (a.second < b.second) || (a.second == b.second && a.first < b.first);});
	//for (auto r : p) {cerr << '[' << r.first << ' ' << r.second << endl;}
	//cnt = 1;
	for (int i = 1; i < n; i++) {
		if (p[i].second == p[i - 1].second) cnt++;
		else {
			ans += (cnt) * (cnt - 1) / 2;
			cnt = 1;
		}
	}
	ans += (cnt) * (cnt - 1) / 2;
	cnt = 1;
	for (int i = 1; i < n; i++) {
		if (p[i] == p[i - 1]) cnt++;
		else {
			ans -= (cnt) * (cnt - 1) / 2;
			cnt = 1;
		}
	}
	ans -= (cnt) * (cnt - 1) / 2;
	cnt = 1;
	cout << ans << endl;
	return 0;
}
