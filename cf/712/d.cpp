#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007, maxn = 2001 * 100 + 500;

long long pow_m(long long a, long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

long long frac[maxn], ifrac[maxn];
long long cnta[maxn], cntb[maxn];
long long ccnt[102][maxn];

int main()
{
	frac[0] = 1;
	for (int i = 1; i < maxn; i++) frac[i] = frac[i - 1] * i % mod;
	for (int i = 0; i < maxn; i++) ifrac[i] = pow_m(frac[i], mod - 2);
	int a, b, k, t;
	cin >> a >> b >> k >> t;
	// Select from 0 to 2k, start from 0
	ccnt[0][0] = 1;
	for (int i = 1; i <= t; i++)
	{
		long long tsum = 0;
		for (int j = 0; j < maxn; j++)
		{
			(tsum += ccnt[i - 1][j]) %= mod;
			int low = max(0, j - k * 2) - 1;
			if (low >= 0)
				tsum = (tsum - ccnt[i - 1][low] + mod) % mod;
			ccnt[i][j] = tsum;
		}
	}
	for (int i = a; i < maxn; i++)
		cnta[i] = ccnt[t][i - a];
	for (int i = b; i < maxn; i++)
		cntb[i] = (cntb[i - 1] + ccnt[t][i - b]) % mod;
//	for (int i = a; i <= a + t * k * 2 + 5; i++) cerr << i << "(" << cnta[i] << ") ";
//	cerr << endl;
//	for (int i = a; i <= a + t * k * 2 + 5; i++) cerr << i << "(" << cntb[i] << ") ";
	long long ans = 0;
	for (int i = a; i < maxn; i++)
		ans += cnta[i] * cntb[i - 1] % mod;
	ans %= mod;
	printf("%lld\n", ans);
	return 0;
}
