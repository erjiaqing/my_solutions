#include <bits/stdc++.h>
using namespace std;

int a, b, c, aa, bb;
vector<long long> u, p, l;

int main()
{
	ios::sync_with_stdio(0);
	cin >> a >> b >> c;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int t;
		char buf[10];
		cin >> t >> buf;
		if (buf[0] == 'U') u.push_back(t);
		else p.push_back(t);
	}
	sort(u.begin(), u.end());
	sort(p.begin(), p.end());
	long long ans = 0;
	while (aa < a && aa < u.size())
		ans += u[aa++];
	while (bb < b && bb < p.size())
		ans += p[bb++];
	for (int ta = aa; ta < u.size(); ta++)
		l.push_back(u[ta]);
	for (int tb = bb; tb < p.size(); tb++)
		l.push_back(p[tb]);
	sort(l.begin(), l.end());
	int cc = 0;
	while (cc < c && cc < l.size())
		ans += l[cc++];
	cout << aa + bb + cc << ' ' << ans << endl;
	return 0;
}
