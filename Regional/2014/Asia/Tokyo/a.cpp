#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 16;
int src[maxn], dst[maxn];
int p[maxn], mv[maxn], mv2[maxn];
int n, m;
int abs(int x)
{
	return x < 0 ? -x : x;
}
int check()
{
	int ans = 0;
	int t1 = 0, tt1 = 0;
	for (int i = 0; i < n; i++)
		if (src[i])
			mv[t1++] = i;
	for (int i = 0; i < n; i++)
		if (dst[i])
			mv[tt1++] -= i;
	if (t1 != tt1) return 0x7fffffff;
	for (int i = 0; i < t1; i++)
		ans += abs(mv[i]);
	return ans;
}
int check2()
{
	int ans = 0;
	int t1 = 0, tt1 = 0;
	for (int i = 0; i < n; i++)
		if (!src[i])
			mv[t1++] = i;
	for (int i = 0; i < n; i++)
		if (!dst[i])
			mv[tt1++] -= i;
	if (t1 != tt1) return 0x7fffffff;
	for (int i = 0; i < t1; i++)
		ans += abs(mv[i]);
	return ans;
}
int solve()
{
	int ans = 0x7fffffff;
	for (int i = 0; i < n; i++)
		scanf("%d", &src[i]);
	for (int i = 0; i < m; i++)
		scanf("%d", &p[i]);
	int pt = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < p[i]; j++, pt++)
			dst[pt] = (i & 1);
	ans = min(ans, min(check(), check2()));
	pt = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < p[i]; j++, pt++)
			dst[pt] = ((i & 1) ^ 1);
	ans = min(ans, min(check(), check2()));
	return ans;
}
int main()
{
	while (~scanf("%d%d", &n, &m))
		printf("%d\n", solve());
	return 0;
}
