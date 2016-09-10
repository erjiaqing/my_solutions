#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;

#define x first
#define y second

struct line{
	int x, y, dx, dy;
	line(){}
	line(int x, int y, int dx, int dy):x(x), y(y), dx(dx), dy(dy) {}
}l[maxn];
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef pair<pii, pll> ppiipll;
map<ppiipll, int> mp;

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int dx = x2 - x1;
		int dy = y2 - y1;
		if (dx < 0) {dx = -dx;dy = -dy;}
		else if (dx == 0) {dy = abs(dy);}
		int dg = __gcd(dx, dy);
		dx /= dg;dy /= dg;
		l[i] = line(x1, y1, dx, dy);
	}
//	for (int i = 0; i < n; i++)
//		printf("%d > %d %d %d %d\n", i, l[i].x, l[i].y, l[i].dx, l[i].dy);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (l[i].dx != l[j].dx || l[i].dy != l[j].dy) continue;
			int dx = l[i].dx, dy = l[i].dy;
			long long tdx = -dy, tdy = dx;
			long long tx = l[j].x - l[i].x, ty = l[j].y - l[i].y;
			long long dst = abs(tx * tdx + ty * tdy);
			long long dst2 = tdx * tdx + tdy * tdy;
			dst *= dst;
			long long tg = __gcd(dst, dst2);
			dst /= tg;dst2 /= tg;
//			printf("--(%d, %d)--> len = %lld / %lld\n", dx, dy, dst, dst2);
			mp[ppiipll(pii(l[i].dx, l[i].dy), pll(dst, dst2))]++;
		}
	}
	long long ans = 0;
	for (auto re : mp)
	{
		int dx = re.x.x.y, dy = -re.x.x.x;
	   	long long rx = re.x.y.x, ry = re.x.y.y;
		auto tr = mp.find(ppiipll(pii(dx, dy), pll(rx, ry)));
		if (tr != mp.end())
			ans += re.y * tr->y;
	}
	printf("%lld\n", ans);
	return 0;
}
