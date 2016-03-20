#include <bits/stdc++.h>
using namespace std;
map<string, set<string> > M;
const int bufsize = 10000 + 5;
char buf[bufsize];
int n, t;
stringstream ss;
int main() {
	ios::sync_with_stdio(0);
	cin.getline(buf, bufsize);	
	sscanf(buf, "%d", &t);
	for (int i = 1; i <= t; i++) {
		cin.getline(buf, bufsize);
		sscanf(buf, "%d", &n);
		for (int j = 0; j < n; j++) {
			string s, s0;
			cin.getline(buf, bufsize);
			ss << buf;
			ss >> s0;
			while (ss >> s)
				M[s0].insert(s);
			ss.clear();
		}
		double ans = 0;
		for (int j = 0; j < n; j++) {
			string s, s0;
			cin.getline(buf, bufsize);
			ss << buf;
			ss >> s0;
			int c = 0, w = 0;
			auto &res = M[s0];
			double tres = 0;
			while (ss >> s) {
				c++;
				if (res.find(s) != res.end()) {
					w++;
					tres += (1.0 * w / c);
				}
			}
			//cerr << endl;
			ss.clear();
			if (res.size())
				ans += tres / res.size();
		}
		ans /= n;
		sprintf(buf, "Case #%d: %.6f\n", i, ans);
		cout << buf;
	}
	return 0;
}
