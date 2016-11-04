#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
long long a[maxn];

long long sol()
{
	long long n, k, op = 0;
	long long sum = 0, each = 0;
	scanf("%lld%lld", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	if (sum % k) return -1;
	each = sum / k;
	for (int i = 0; i < n; i++)
	{
		if (a[i] > each)
		{
			int tot = a[i] / each;
			int rem = a[i] % each;
			op += tot - (rem == 0);
			op += (rem != 0);
			a[i + 1] += rem;
		} else if (a[i] < each)
		{
			op++;
			a[i + 1] += a[i];
		} else {
			continue;
		}
	}
	return op;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %lld\n", i, sol());
	return 0;
}
