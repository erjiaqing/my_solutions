#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 500000 + 1;
int c[maxn], c2[maxn];
long long n, k, avg, flg;
long long check(long long mi)
{
	long long ret = 0;
	for (int i = 0; i < n; i++)
		if (c[i] <= mi)
			ret += mi - c[i];
	return ret;
}
long long check2(long long mx)
{
	long long ret = 0;
	for (int i = 0; i < n; i++)
		if (c[i] >= mx)
			ret += c[i] - mx;
	return ret;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> c[i];
		avg += c[i];
	}
	flg = (avg % n) != 0;
	avg /= n;
	sort(&c[0], &c[n]);
	long long max_poorest = 0, min_richest = (1ll << 30) - 1;
	for (long long i = 1ll << 30; i > 0; i >>= 1)
		if (((max_poorest | i) <= avg) && check(max_poorest | i) <= k)
			max_poorest |= i;
	for (long long i = 1ll << 29; i > 0; i >>= 1)
		if ((min_richest ^ i) >= (avg + flg) && check2(min_richest ^ i) <= k)
			min_richest ^= i;
	cout << min_richest - max_poorest << endl;
	return 0;
}
