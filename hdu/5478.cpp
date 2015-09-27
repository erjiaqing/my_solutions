#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;
const int maxc = 200000 + 1;
typedef pair<int, int> pii;
#define x first
#define y second
pii ak1[maxc], bk1[maxc];
int pk1[maxc], pk2[maxc];
long long c, k1, b1, k2;
long long pow(long long x, long long a, long long p)
{
	long long ret = 1;
	while (a)
	{
		if (a & 1) ret = ret * x % p;
		x = x * x % p;
		a >>= 1;
	}
	return ret;
}
void solve()
{
	vector<pii> ans;
	for (int i = 1; i < c; i++)
		ak1[i] = pii(pow(i, b1, c), i),
		pk1[i] = pow(i, k1, c);
	for (int i = 1; i < c; i++)
		bk1[i] = pii(c - pow(pow(i, k2 - 1, c), c - 2, c), i),
		pk2[i] = pow(i, k2, c);
	sort(&ak1[1], &ak1[c]);
	sort(&bk1[1], &bk1[c]);
	for (int i = 1; i < c; i++)
	{
		int pos = lower_bound(&bk1[1], &bk1[c], pii(ak1[i].x, 0)) - &bk1[0];
		while (bk1[pos].x == ak1[i].x)
		{
			if (pk1[ak1[i].y] == pk2[bk1[pos].y])
				ans.push_back(pii(ak1[i].y, bk1[pos].y));
			pos++;
		}
	}
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		printf("%d %d\n", ans[i].x, ans[i].y);
	if (ans.size() == 0)
		printf("-1\n");
}
int main()
{
	int t = 0;
	while (~scanf("%lld%lld%lld%lld", &c, &k1, &b1, &k2)) printf("Case #%d:\n", ++t), solve();
	return 0;
}
