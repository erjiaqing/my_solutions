#include <cstdio>
int n, m, k;
unsigned long long sol()
{
	unsigned long long ret = 0;
	k /= 2;
	for (int i = 1; i < k && i <= n ; i++)
	{
		int maxm = m;
		if (k - i > m) maxm = 1;
		else maxm = m - (k - i) + 1;
		int minm = m;
		int cntm = minm - maxm + 1;
		__int128 tr = 1;
		tr = tr * (n - i + 1) * (maxm + minm) * cntm / 2;
		ret += tr;
	}
	return ret;
}
int main()
{
	while (scanf("%d%d%d", &n, &m, &k) != EOF)
		printf("%llu\n", sol());
}
