#include <cstdio>
#include <cstring>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = 1000 + 5;
const int mod = 1000000007;


struct point
{
	long long x, y;
	point(){}
	point(long long _x, long long _y):
		x(_x), y(_y){}
	point operator - (point p)
	{
		return point(x - p.x, y - p.y);
	}
};

point pt[maxn], spt[maxn];
int cpt[maxn];
long long pow2[maxn];

void sol()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld%lld", &pt[i].x, &pt[i].y);
	//sort(&pt[0], &pt[n], [](point &a, point &b){return a.x < b.x || (a.x == b.x)});
	long long ans = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int all = 0;
		map<pair<long long, long long>, int> mp;
		for (int j = i + 1; j < n; j++)
		{
			point tpt = pt[j] - pt[i];
			if (tpt.x == 0 && tpt.y == 0)
			{
				all++;
				continue;
			}
			if (tpt.x < 0) {tpt.x = -tpt.x;tpt.y = -tpt.y;}
			if (tpt.x == 0 && tpt.y < 0) {tpt.y = -tpt.y;}
			long long g = __gcd(tpt.x, tpt.y);
			mp[make_pair(tpt.x / g, tpt.y / g)]++;
		}
		ans += pow2[all] - 1;
		for (auto r : mp)
			ans += pow2[all] * (pow2[r.second] - 1) % mod;
		ans %= mod;
	}
	printf("%lld\n", ans);
	return;
}


int main()
{
	pow2[0] = 1;
	for (int i = 1; i < maxn; i++) pow2[i] = 2 * pow2[i - 1] % mod;
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
