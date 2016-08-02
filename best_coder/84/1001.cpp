#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

void sol()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int ans = 0;
	if (m < 30)
	{
		ans += (n >> m);
		n = (((1 << m) - 1) & n);
	}
	while (n)
	{
		ans += (n & 1);
		n >>= 1;
	}
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
