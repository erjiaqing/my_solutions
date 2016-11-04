#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

long long a[maxn], diff[maxn], t[maxn];
int n;

long long sol()
{
	scanf("%d", &n);
	for (int i = n - 1; i >= 0; i--)
		scanf("%lld", &a[i]);
	a[n] = 0;
	for (int i = 0; i < n; i++)
		diff[i] = a[i + 1] - a[i];
	long long ans = 1;
	t[0] = 1;
	for (int i = 1; i < n; i++)
	{
		long long dt = diff[i] * t[i - 1];
		long long tt = dt / diff[i - 1] + (dt % diff[i - 1] != 0);
		ans += tt;
		t[i] = tt;
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %lld\n", i, sol());
	return 0;
}
