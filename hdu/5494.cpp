#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 500 + 1;
int a[maxn], b[maxn];
bool solve()
{
	int m, n;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) scanf("%d", &b[i]);
	sort(&a[0], &a[n]);
	sort(&b[0], &b[n], greater<int>());
	int sa = 0, sb = 0;
	for (int i = 0; i < m; i++)
	{
		sa += a[i];
		sb += b[i];
	}
	return sa > sb;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		puts(solve() ? "YES" : "NO");
	return 0;
}

