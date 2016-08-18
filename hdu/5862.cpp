#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010 + 5;

typedef pair<int, int> pii;
typedef pair<int, pii> ipii;

set<int> sx;
vector<int> ax;
vector<ipii> lx, ly;//, rx, ry;
vector<pii> add, rem;

int n, m;

long long bit[maxn * 4];

void clear()
{
	sx.clear();ax.clear();
	lx.clear();ly.clear();
	add.clear();rem.clear();
	memset(bit, 0, sizeof(long long) * (n + 10) * 4);
}

#define pb push_back
#define x first
#define y second
#define mp make_pair

#define LOWBIT(x) ( ( x ) & ( - ( x ) ) )

long long getx(int dx)
{
	long long ret = 0;
	for (; dx; dx -= LOWBIT(dx))
		ret += bit[dx];
	return ret;
}

void setx(int dx, int va)
{
	for (; dx < ax.size(); dx += LOWBIT(dx))
		bit[dx] += va;
}

void process()
{
//  int lstx = -1000000001, lstyb = -1000000001, lstye = -1000000001;
//	for (auto px : lx)
//	{
//		rx.pb(mp(px.x, mp(px.y.x, px.y.y)));
/*		if (px.x != lstx || lstye < px.y.x)
		{
			if (lstx != 1000000001)
				rx.pb(mp(lstx, mp(lstyb, lstye)));
			lstx = px.x;
			lstyb = px.y.x;
			lstye = px.y.y;
		}
*/
//	}
//	if (lstye != -1000000001)
//		rx.pb(mp(lstx, mp(lstyb, lstye)));
//	int lsty = -1000000001, lstxb = -1000000001, lstxe = -1000000001;
//	for (auto py : ly)
//	{
//		ry.pb(mp(py.x, mp(py.y.x, py.y.y)));
		/*
		if (py.x != lsty || lstxe < py.y.x) {
			if (lsty != -1000000001)
				ry.pb(mp(lsty, mp(lstxb, lstxe)));
			lsty = py.x;lstxb = py.y.x;lstxe = py.y.y;
		} else {
			lstxe = max(lstxe, py.y.y);
		}*/
//	}
/*
	if (lstxe != -1000000001)
		ry.pb(mp(lsty, mp(lstxb, lstxe)));
*/
}

int getid(int val)
{
	return lower_bound(ax.begin(), ax.end(), val) - ax.begin();
}

long long sol()
{
//	int n;
	int x1, x2, y1, y2;
	long long ans = 0;
	scanf("%d", &n);
	clear();
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		sx.insert(x1);sx.insert(y1);sx.insert(x2);sx.insert(y2);
		if (x1 == x2) lx.pb(mp(x1, mp(min(y1, y2), max(y1, y2))));
		if (y1 == y2) ly.pb(mp(y1, mp(min(x1, x2), max(x1, x2))));
	}
	sort(lx.begin(), lx.end());
	sort(ly.begin(), ly.end());
//	process();
	ax.pb(-1000000002);ax.pb(-1000000001);
	for (auto xx : sx) ax.pb(xx);
	ax.pb(1000000001);ax.pb(1000000002);
	for (auto p : lx)
	{
//		ans += p.y.y - p.y.x + 1;
		add.pb(mp(p.y.x, p.x));
		rem.pb(mp(p.y.y, p.x));
	}
	sort(add.begin(), add.end());
	sort(rem.begin(), rem.end());
	int addb = 0, remb = 0;
	for (auto p : ly)
	{
		while (addb < add.size() && add[addb].x <= p.x)
			setx(getid(add[addb++].y), 1);
		while (remb < rem.size() && rem[remb].x < p.x)
			setx(getid(rem[remb++].y), -1);
//		ans += p.y.y - p.y.x + 1;
		ans += getx(getid(p.y.y)) - getx(getid(p.y.x) - 1);
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%lld\n", sol());
	return 0;
}
