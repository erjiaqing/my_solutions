#include <bits/stdc++.h>
using namespace std;
int equations[36][10], totequ;
int equtype[36], equsum[36];
int maxneed[10];
int cur[10], mark[10], ans;
void dfs(int lay, int curr)
{
	if (lay == totequ)
	{
		ans = max(ans, curr);
		return;
	}
	bool flg1 = 1, flg2 = (equtype[lay] == 2);
	for (int i = 1; i <= 9; i++)
		flg1 = flg1 && (cur[i] >= equations[lay][i]),
		flg2 = flg2 && (cur[i] >= equations[lay][i] * 2);
	if (flg2)
	{
		for (int i = 1; i <= 9; i++)
			cur[i] -= equations[lay][i] * 2;
		dfs(lay + 1, curr + 2);
		for (int i = 1; i <= 9; i++)
			cur[i] += equations[lay][i] * 2;
	}
	if (flg1 && 36 - equsum[lay] + curr + 1 > ans)
	{
		for (int i = 1; i <= 9; i++)
			cur[i] -= equations[lay][i];
		dfs(lay + 1, curr + 1);
		for (int i = 1; i <= 9; i++)
			cur[i] += equations[lay][i];
	}
	if (ans < 36 - equsum[lay] + curr)
		dfs(lay + 1, curr);
}
int main()
{
	// Init
	for (int i = 1; i <= 9; i++)
		if (i + i <= 9)
		{
			equations[totequ][i] += 2;
			equations[totequ][i + i]++;
			maxneed[i] += 2;maxneed[i + i]++;
			equtype[totequ] = 1;
			totequ++;
		}
	for (int i = 1; i <= 9; i++)
		for (int j = i + 1; j <= 9; j++)
			if (i + j <= 9)
			{
				equations[totequ][i]++;
				equations[totequ][j]++;
				equations[totequ][i + j]++;
				equtype[totequ] = 2;
				totequ++;
				maxneed[i]+=2;maxneed[j]+=2;maxneed[i + j]+=2;
			}
	equsum[0] = equtype[0];
	for (int i = 1; i < totequ; i++) equsum[i] = equsum[i - 1] + equtype[i];
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		for (int j = 1; j <= 9; j++)
			scanf("%d", &cur[j]);
		for (int j = 1; j <= 9; j++)
			cur[j] = min(cur[j], maxneed[j]);
		ans = 0;
		dfs(0, 0);
		printf("Case #%d: %d\n", i, ans);
	}
	return 0;
}
