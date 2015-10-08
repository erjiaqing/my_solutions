#include <cstdio>
const int maxn = 202;
int ans[maxn][maxn];
int main()
{
	int n, t;
	scanf("%d", &n);
	t = 2 * n + 1;
	for (int i = 1; i <= t; i++)
	{
		int k = i % t;
		for (int j = 0; j < t; j++)
			ans[j + 1][((k - j) % t + t) % t + 1] = i;
	}
	for (int i = 1; i <= t; i++)
	{
		ans[i][i] = 0;
		for (int j = 1; j <= t; j++)
			printf("%d%c", ans[i][j], j != t ? ' ' : '\n');
	}
	return 0;
}

