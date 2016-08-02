#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
using namespace std;
const int maxn = 20000 + 5;
const int maxk = 100 + 2;
typedef pair<int, int> pii;
int n, k;
long long a[maxn], r[maxn], b[maxn], d[maxn];
int leftmost[maxn], rightmost[maxn];
long long dp[maxn + 5][maxk]; // right most

vector<pair<int, pair<int, int> > > vec;

bool check(const pii& i, const pii& j) {
	return i.second + b[j.first] < 
		j.second + b[i.first];
}

int get_leftmost(int p, int _r)
{
	//int ret = 0;
	return lower_bound(&d[1], &d[p + 1], d[p] - _r) - &d[0];
	/*
	for (int i = 1 << 16; i; i >>= 1)
		if ((ret | i) < p && d[p] - d[p - (ret | i)] <= _r)
			ret |= i;
	return p - ret;*/
}

int get_rightmost(int p, int _r)
{
	//int ret = 0;
	return upper_bound(&d[p], &d[n + 1], _r + d[p]) - &d[0] - 1;
	/*
	for (int i = 1 << 16; i; i >>= 1)
		if (p + (ret | i) <= n && d[p + (ret | i)] - d[p] <= _r)
			ret |= i;
	return p + ret;
	*/
}

void sol()
{
	cin >> n >> k;
	memset(dp, 0x01, sizeof(long long) * maxk * (n + 2));
	for (int i = 2; i <= n; i++)
	{
		cin >> d[i];
		d[i] += d[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> r[i] >> b[i];
		b[i] += b[i - 1];
	}
	for (int i = 1; i <= n; i++)
		leftmost[i] = get_leftmost(i, r[i]);
	for (int i = 1; i <= n; i++)
		rightmost[i] = get_rightmost(i, r[i]);
//	for (int i = 1; i <= n; i++)
//		cerr << "lm = " << leftmost[i] << " rm = " << rightmost[i] << " sb = " << b[i] << endl;
	vec.clear();
	for (int i = 1; i <= n; i++)
		vec.push_back(make_pair(leftmost[i], make_pair(rightmost[i], a[i])));
	//
	sort(vec.begin(), vec.end());
	pii current(0, 0);
	int c = 0;
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		if (current.first < i) current = pii(i, b[i] - b[i - 1]);
		while (c < n && vec[c].first <= i)
		{
			if (!check(current, pii(vec[c].second.first, vec[c].second.second)))
				current = pii(vec[c].second.first, vec[c].second.second);
			c++;
		}
		for (int j = 0; j < k; j++)
		{
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + b[i] - b[i - 1]);
			dp[current.first][j + 1] = min(dp[current.first][j + 1], dp[i - 1][j] + current.second);
		}
	}
	long long ans = 0x7fffffffffffffffll;
	for (int i = 0; i <= k; i++)
		ans = min(ans, dp[n][i]);
	cout << ans << "\n";
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
		sol();
	return 0;
}
