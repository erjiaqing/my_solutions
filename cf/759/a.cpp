#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;
int p[maxn], b[maxn];
int vis[maxn];
int n;
int ans = 0, ans2 = 0;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		ans ^= b[i];
	}
	for (int i = 1; i <= n; i++)
	{
		int ti = i;
		if (!vis[ti]) ans2++;
		while (!vis[ti])
		{
			vis[ti] = 1;
			ti = p[ti];
		}
	}
	if (ans2 == 1) ans2 = 0;
	ans ^= 1;
	printf("%d\n", ans + ans2);
	return 0;
}
