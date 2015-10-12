#include <cstdio>
int n;
long long pow(long long a, long long b, long long mod)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
bool m_r_prime(long long k, long long x)
{
	int d = x - 1;
	while ((d & 1) == 0) d >>= 1;
	int s1 = pow(k, d, x);
	if (s1 == 1 || s1 == x - 1) return true;
	int t = (x - 1) / 2;
	while (d != t)
	{
#ifdef LOCAL
		//printf("** %d\n", d);
#endif
		d <<= 1;
		if (pow(k, d, x) == x - 1) return true;
	}
	return false;
}
bool check_prime(long long x)
{
	if (x % 2 == 0 && x != 2) return false;
	if (x == 2) return true;
	if (x == 61) return true;
	if (x == 3) return true;
	if (x == 7) return true;
	if (x < 61)
	{
#ifdef LOCAL
	printf("%d %d\n", m_r_prime(2, x), m_r_prime(3, x));
#endif
		return m_r_prime(2, x) && m_r_prime(3, x);
	}
#ifdef LOCAL
	printf("%d %d %d\n", m_r_prime(2, x), m_r_prime(7, x), m_r_prime(61, x));
#endif
	return m_r_prime(2, x) && m_r_prime(7, x) && m_r_prime(61, x);
}
int ns[3], k;
int main()
{
	scanf("%d", &n);
	if (check_prime(n)) {printf("1\n%d\n", n);return 0;}
	for (int i = n - 2; i > 1; i--)
	{
#ifdef LOCAL
		printf("%d\n", i);
#endif
		if (check_prime(i))
		{
			ns[0] = i;
			n -= i;
			break;
		}
	}
#ifdef LOCAL
	printf("NUM1 = %d REM = %d\n", ns[0], n);
#endif
	if (check_prime(n)) {printf("2\n%d %d\n", ns[0], n);return 0;}
	for (int i = n - 2; i > 1; i--)
	{
#ifdef LOCAL
		printf("%d: %d\n", __LINE__, i);
#endif
		if (check_prime(i) && check_prime(n - i))
		{
			ns[1] = i;
			n -= i;
			break;
		}
	}
	printf("3\n%d %d %d\n", ns[0], ns[1], n);
	return 0;
}
