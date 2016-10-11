#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cassert>
using namespace std;

const int maxn = 200000 + 5;
int n, m;
long long t[maxn], fstcopy[maxn];

typedef pair<long long, int> plli;

priority_queue<plli, vector<plli>, greater<plli> > pq;
map<long long, int> mp[1001];
vector<plli> vv[1001];

long long check(long long limtime)
{
	long long res = 0;
	for (int i = 1; i <= 1000; i++)
		for (plli ls : vv[i])
		{
			if (limtime < ls.first) continue;
			res += (limtime - ls.first) / i * ls.second;
		}
//	cerr << limtime << ' ' << res << endl;
	return res;
}
int main()
{
//	freopen("d.in", "r", stdin);
	scanf("%d%d", &n, &m);
//	ios::sync_with_stdio(0);
//	cin >> n >> m;
	for (int i = 0; i < n; i++)
		scanf("%lld", &t[i]);
//		cin >> t[i];
	sort(&t[0], &t[n]);
	fstcopy[0] = 0;
	pq.push(plli(t[0], 0));
	for (int i = 1; i < n; i++)
	{
		assert(pq.size());
		plli fst = pq.top();pq.pop();
		pq.push(plli(fst.first + t[fst.second], fst.second));
		fstcopy[i] = fst.first;
		pq.push(plli(fstcopy[i] + t[i], i));
	}
//	cerr << n << ' ' << m << endl;
	for (int i = 0; i < n; i++)
	{
//		printf("%d, %lld, %lld\n", i, t[i], fstcopy[i]);
		mp[t[i]][fstcopy[i]]++;
	}
	for (int i = 1; i <= 1000; i++)
		for (auto pp : mp[i])
			vv[i].push_back(plli(pp.first, pp.second));
//	for (int i = 0; i < n; i++) cout << fstcopy[i] << ' ';
//	cout << '\n';
	for (int i = 0; i < m; i++)
	{
		long long a;
		cin >> a;
		long long ans = (1ll << 40) - 1;
		for (long long ii = 1ll << 39; ii; ii >>= 1)
			if (check(ans - ii) >= a)
				ans -= ii;
		printf("%lld\n", ans);
//		cout << ans << '\n';
//		printf("%lld\n", ans);
	}
	return 0;
}
