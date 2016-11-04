#include <bits/stdc++.h>
using namespace std;
map<long long, int> mp2[10];
long long tsum[10][100000 + 5];
int _p[10][10];
long long _pow(int a, int x)
{
	long long ret = 1;
	while (x)
	{
		if (x & 1) ret = ret * a;
		a = a * a;
		x >>= 1;
	}
	return ret;
}
long long f(int y, int k)
{
	long long ret = 0;
	while (y)
	{
		ret += _p[y % 10][k];
		y /= 10;
	}
	return ret;
}
int main()
{
	for (int k = 1; k <= 9; k++)
		for (int i = 0; i <= 9; i++)
			_p[i][k] = _pow(i, k);
	for (int k = 1; k <= 9; k++)
		for (int i = 0; i < 100000; i++)
			tsum[k][i] = f(i, k) - i * 100000ll;
	for (int k = 1; k <= 9; k++)
		for (int i = 1; i < 100000; i++)
			mp2[k][f(i, k) - i]++;
	int t = 0;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		long long x;
		int k;
		int ans = 0;
		scanf("%lld%d", &x, &k);
		for (int i = 0; i < 100000; i++)
		{
			auto fi = mp2[k].find(x - tsum[k][i]);
			if (fi != mp2[k].end())
				ans += fi->second;
		}
		printf("Case #%d: %d\n", i, ans);
	}
	return 0;
}
