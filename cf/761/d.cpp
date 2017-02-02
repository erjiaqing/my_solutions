#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int n, l, r;
int a[maxn], p[maxn], b[maxn];
typedef pair<int, int> pii;
vector<pii> s;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> p[i];
	for (int i = 0; i < n; i++) s.push_back(pii(p[i], i));
	sort(s.begin(), s.end());
	int current_minimum = -2147483647;
	for (int i = 0; i < n; i++)
	{
		int tb = current_minimum + 1 + a[s[i].second];
		tb = max(tb, l);
		if (tb > r)
		{
			puts("-1");
			return 0;
		}
		current_minimum = tb - a[s[i].second];
		b[s[i].second] = tb;
	}
	for (int i = 0; i < n; i++) printf("%d%c", b[i], i == n - 1 ? '\n' : ' ');
	return 0;
}
