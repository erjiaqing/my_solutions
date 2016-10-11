#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	long long a, sg = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &a);
		sg += a - 1;
		printf("%lld\n", 2 - (sg & 1));
	}
	return 0;
}
