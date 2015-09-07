#include <iostream>
using namespace std;
const long long mod = 1000000007;
const int maxn = 1000000 + 1;
long long frac[maxn];
inline long long pow(long long a, long long b)
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
inline long long inv(long long n, long long p)
{
	return pow(n, p - 2);
}
inline long long c(long long n, long long k)
{
	if (n < k) return 0;
	return frac[n] * inv(frac[k], mod) % mod * inv(frac[n - k], mod) % mod;
}
int main()
{
	frac[0] = 1;
	for (int i = 1; i <= maxn; i++)
		frac[i] = frac[i - 1] * i % mod;
	long long ans = 0;
	int n;
	cin >> n;
	n++;
	for (int i = 1; i <= n; i++)
	{
		long long tmp = 0;
		tmp = c(n, i);
		tmp = tmp * tmp % mod;
		ans = (ans + tmp) % mod;
	}
	cout << ans << endl;
	return 0;
}
