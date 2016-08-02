#include <iostream>
using namespace std;
long long pow_mod(long long a, long long b, long long m)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1)
			(ret *= a) %= m;
		(a *= a) %= m;
		b >>= 1;
	}
	return ret;
}

int main()
{
	long long x, m, c, k, t;
	scanf("%lld", &t);
	for (int i = 1; i <= t; i++)
	{
		scanf("%lld%lld%lld%lld", &x, &m, &k, &c);
		printf("Case #%d:\n", i);
		(c *= 9) %= k;
		long long tmp = (pow_mod(10, m, k) - 1 + k) % k;
		tmp = tmp * x % k;
		if (tmp == c)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}

