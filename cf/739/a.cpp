#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, m, ans;
	scanf("%d%d", &n, &m);
	ans = n + 1;
	for (int i = 0; i < m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		ans = min(ans, r - l + 1);
	}
	printf("%d", ans);
	for (int i = 0; i < n; i++)
		printf("%c%d", i ? ' ' : '\n', i % ans);
	printf("\n");
	return 0;
}
