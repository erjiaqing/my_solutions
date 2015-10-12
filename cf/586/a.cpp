#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100 + 2;
int n;
int a[maxn];
int ans, beg, fin;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if (a[i])
		{
			if (!beg) beg = i;
			fin = i + 1;
		}
	}
	ans = fin - beg;
#ifdef LOCAL
	cerr << fin << " " << beg << endl;
#endif
	for (int i = beg; i < fin; i++)
	{
		int t = 0;
		while (a[i] == 0)
		{
			t++;
			if (a[i + 1] != 0)
				break;
			i++;
		}
		if (t >= 2) ans -= t;
	}
	printf("%d\n", ans);
	return 0;
}
