#include <bits/stdc++.h>
using namespace std;
const int maxp = 1e5;
long long inv[maxp];
long long fact[maxp];
long long p[10];
long long pow(long long x, long long a, int p)
{
	long long r = 1;
	while (a)
	{
		if (a & 1) r = r * x % p;
		x = x * x % p;
		a >>= 1;
	}
	return r;
}
long long mul(long long a, long long b, long long mod)
{
	long long r = 0;
	while (b)
	{
		if (b & 1) r = (r + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return r;
}
long long ext_gcd(long long a, long long b, long long &x, long long &y)
{
	if (!b)
	{
		x = 1;y = 0;return a;
	}else
	{
		long long ret = ext_gcd(b, a % b, y, x);
		y -= x * (a / b);
		return ret;
	}
}
long long fact_mod(long long n, long long p, long long &e)
{
	e = 0;
	if (!n) return 1;
	long long ret = fact_mod(n / p, p, e);
	e += n / p;
	return (n / p % 2 ? p - fact[n % p] : fact[n % p]) * ret % p;
}
long long comb_mod(long long n, long long k, long long p)
{
	if (n < 0 || k < 0 || n < k) return 0;
	long long e1, e2, e3;
	long long a1 = fact_mod(n, p, e1);
	long long a2 = fact_mod(k, p, e2);
	long long a3 = fact_mod(n - k, p, e3);
	if (e1 > e2 + e3) return 0;
	return a1 * inv[a2 * a3 % p] % p;
}
void init(int p)
{
	fact[0] = 1;
	for (int i = 1; i < p; i++)
	{
		fact[i] = fact[i - 1] * i % p;
		inv[i] = pow(i, p - 2, p);
	}
}
void work()
{
	long long n, m, k, M = 1, ret = 0;
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%lld", &p[i]);
		M *= p[i];
	}
	for (int i = 0; i < k; i++)
	{
		init(p[i]);
		long long tM = M / p[i];
		long long a = comb_mod(n, m, p[i]);
		long long x, y;
		ext_gcd(tM, p[i], x, y);
		long long tmp = tM;
		x = (x % M + M) % M;
		tmp = mul(tmp, x, M);
		tmp = mul(tmp, a, M);
		ret = (ret + tmp) % M;
	}
	ret = (ret + M) % M;
	printf("%lld\n", ret);
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		work();
	return 0;
}
