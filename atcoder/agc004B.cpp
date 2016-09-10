#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000 + 5;
int n;
long long a[maxn], b[maxn], x, ans;

int main()
{
	ans = 0x7fffffffffffffffll;
	scanf("%d%lld", &n, &x);
	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	memset(b, 0x3f, sizeof b);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			b[j] = min(b[j], a[(j - i + n) % n]);
		long long tans = 0;
		for (int j = 0; j < n; j++)
			tans += b[j];
		ans = min(ans, tans + i * x);
	}
	printf("%lld\n", ans);
	return 0;
}
