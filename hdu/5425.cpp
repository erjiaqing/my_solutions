#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 100000 + 5;
int dep[maxn];
long double p2[100];
vector<int> e[maxn];
int n;
void dfs(int u, int d)
{
	dep[u] = d;
	for (int i = 0; i < e[u].size(); i++)
		dfs(e[u][i], d + 1);
}
void work()
{
	int f;
	double ans = 0;
	for (int i = 1; i <= n; i++)
		e[i].clear();
	for (int i = 2; i <= n; i++)
	{
		scanf("%d", &f);
		e[f].push_back(i);
	}
	dfs(1, 1);
	sort(&dep[1], &dep[n + 1]);
	for (int i = max(1, n - 60); i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			long double now = p2[n - i + 1];
			long double v = (dep[i] * dep[j]);
			long double r = (dep[i] + dep[j]);
			if ( i < 60 )
				now -= (long double)(n + 1) / p2[i - 1];
			long double nowx = v / r;
			nowx /= now;
			ans += nowx;
		}
	}
	printf("%.6f\n", ans);
}
int main()
{
	p2[0] = 1;
	p2[1] = 2;
	for (int i = 2; i < 100; i++)
		p2[i] = p2[i / 2] * p2[i - i / 2];
	while (~scanf("%d", &n))
		work();
	return 0;
}
