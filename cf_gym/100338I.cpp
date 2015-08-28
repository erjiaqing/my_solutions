#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 55;
double prob[maxn];
int c;
int n;
double dfs(int lev, int use, double curr)
{
	if (lev == n)
		return curr;
	if (lev == use)
		return dfs(lev + 1, use, (curr - c) + prob[lev] * (curr - c));
	return max(curr, dfs(lev + 1, use, curr * 2) * prob[lev]);
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("tvshow.in", "r", stdin);
	freopen("tvshow.out", "w", stdout);
#endif
	scanf("%d%d", &n, &c);
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &prob[i]);
		prob[i] /= 100;
	}
	double ans = 0;
	for (int i = 0; i <= n; i++)
		ans = max(ans, dfs(0, i, 100));
	printf("%.12f\n", ans);
	return 0;
}
