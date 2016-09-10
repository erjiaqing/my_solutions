#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long a, b, c;
	scanf("%lld%lld%lld", &a, &b, &c);
	long long ans = 0x3fffffffffffffffll;
	ans = min(ans, (b & 1) * (a * c));
	ans = min(ans, (a & 1) * (b * c));
	ans = min(ans, (c & 1) * (a * b));
	printf("%lld\n", ans);
	return 0;
}

