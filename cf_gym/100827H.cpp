#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
using namespace std;
const int maxn = 5000 + 1, maxs = 1000 + 1;
set<int> dp[maxn];
int s[15];
int work()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) dp[i].clear();
	dp[0].insert(0);
	for (int i = 0; i < m; i++) scanf("%d", &s[i]);
	for (int i = 0; i < n; i++)
		for (set<int>::iterator it = dp[i].begin(); it != dp[i].end(); it++)
			for (int j = 0; j < m; j++)
				if (i + *it + s[j] <= n)
					dp[i + *it + s[j]].insert(*it + s[j]);
	set<int>::iterator it = dp[n].end();
	if (it == dp[n].begin()) return -1;
	it--;
	return *it;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%d\n", work());
	return 0;
}
