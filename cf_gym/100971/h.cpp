#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

const int maxn = 200000 + 5;
vector<pii> v;

#define LOWBIT( x ) ( ( x ) & ( - ( x ) ) )
int bit[maxn], n;

void add(int x, int v)
{
//	cerr << x << ' ' << v << endl;
	for (; x <= n; x += LOWBIT(x))
		bit[x] += v;
}

int sum(int x)
{
	int ret = 0;
	if (x > n) return n + 1;
	for (; x; x -= LOWBIT(x))
		ret += bit[x];
	return ret;
}

int get(int x)
{
	int ret = 0;
	for (int i = (1 << 20); i; i >>= 1)
		if (sum(ret | i) < x)
			ret |= i;
	if (sum(ret) < x) ret++;
	return sum(ret) == x ? ret : -1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		v.push_back(pii(x, -i));
		v.push_back(pii(y, i));
	}
	sort(v.begin(), v.end());
	int cur = 0;
	for (int i = 1; i <= n; i++)
	{
		while (cur < v.size() && v[cur].second < 0 && v[cur].first <= i)
			add(-v[cur++].second, 1);
		cout << get(i) << ' ';
		while (cur < v.size() && v[cur].second > 0 && v[cur].first <= i)
			add(v[cur++].second, -1);
	}
	cout << "\n";
	return 0;
}
