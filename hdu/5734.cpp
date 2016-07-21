#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 5;
long long w[maxn];
void sol()
{
	int n;
	long long l1 = 0;
	long long l2 = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &w[i]);
		if (w[i] < 0) w[i] = -w[i];
		l1 += w[i] * w[i];
		l2 += w[i];
	}
	l2 = l2 * l2;
	l1 *= n;
	long long r = l1 - l2;
	long long gc = __gcd(r, (long long)n);
	printf("%lld/%lld\n", r / gc, n / gc);
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
