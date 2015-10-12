#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50 + 2;
int urd[maxn], drd[maxn], ave[maxn];
int n;
int ans = 1e9;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
		scanf("%d", &urd[i]), urd[i] += urd[i - 1];
	for (int i = 1; i < n; i++)
		scanf("%d", &drd[i]), drd[i] += drd[i - 1];
	for (int i = 1; i <= n; i++)
		scanf("%d", &ave[i]);
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			ans = min(ans, ave[i] + ave[j] +
					urd[i - 1] + drd[n - 1] - drd[i - 1] +
					urd[j - 1] + drd[n - 1] - drd[j - 1]
					);
	printf("%d\n", ans);
	return 0;
}
