// Happy new year!
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

#define LS( _x ) ( ( _x ) << 1 )
#define RS( _x ) ( ( _x ) << 1 | 1 )
#define LOWBIT( _x ) ( ( _x ) & ( - ( _x ) ) )
#define pb push_back
#define x first
#define y second
#define mp make_pair

namespace sol {

// BEBIN OF NORMAL PROGRAM
typedef pair<int, int> pii;
typedef pair<int, pii> ipii;
set<int> sx;
vector<int> ax;
vector<ipii> lx, ly, rx, ry;
vector<pii> add, rem;

int bit[4000002];
long long getx(int dx)
{
	long long ret = 0;
	for (; dx; dx -= LOWBIT(dx))
		ret += bit[dx];
	return ret;
}

void setx(int dx, int va)
{
	for(; dx < ax.size(); dx += LOWBIT(dx))
		bit[dx] += va;
}

void process()
{
	int lstx = -1000000001, lstyb = -1000000001, lstye = -1000000001;
	for (auto px : lx)
	{
		if (px.x != lstx || lstye < px.y.x) {
			if (lstx != -1000000001)
				rx.pb(mp(lstx, mp(lstyb, lstye)));
			lstx = px.x;lstyb = px.y.x;lstye = px.y.y;
		} else {
			lstye = max(lstye, px.y.y);
		}
	}
	if (lstye != -1000000001)
		rx.pb(mp(lstx, mp(lstyb, lstye)));

	int lsty = -1000000001, lstxb = -1000000001, lstxe = -1000000001;
	for (auto py : ly)
	{
		if (py.x != lsty || lstxe < py.y.x) {
			if (lsty != -1000000001)
				ry.pb(mp(lsty, mp(lstxb, lstxe)));
			lsty = py.x;lstxb = py.y.x;lstxe = py.y.y;
		} else {
			lstxe = max(lstxe, py.y.y);
		}
	}
	if (lstxe != -1000000001)
		ry.pb(mp(lsty, mp(lstxb, lstxe)));
}

int getid(int val)
{
	return lower_bound(ax.begin(), ax.end(), val) - ax.begin();
}

int main() // The true main()
{
	int n;
	int x1, x2, y1, y2;
	long long ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		sx.insert(x1);sx.insert(y1);sx.insert(x2);sx.insert(y2);
		if (x1 == x2) lx.pb(mp(x1, mp(min(y1, y2), max(y1, y2))));
		if (y1 == y2) ly.pb(mp(y1, mp(min(x1, x2), max(x1, x2))));
	}
	sort(lx.begin(), lx.end());
	sort(ly.begin(), ly.end());
	process();
	ax.pb(-1000000002);ax.pb(-1000000001);
	for (auto xx : sx) {ax.pb(xx);}
	ax.pb(1000000001);ax.pb(1000000002);
	for (auto p : rx)
	{
		ans += p.y.y - p.y.x + 1;
		add.pb(mp(p.y.x, p.x));
		rem.pb(mp(p.y.y, p.x));
	}
	sort(add.begin(), add.end());
	sort(rem.begin(), rem.end());
	int addb = 0, remb = 0;
	for (auto p : ry)
	{
		while (addb < add.size() && add[addb].x <= p.x)
			setx(getid(add[addb++].y), 1);
		while (remb < rem.size() && rem[remb].x < p.x)
			setx(getid(rem[remb++].y), -1);
		ans += p.y.y - p.y.x + 1;
		ans -= getx(getid(p.y.y)) - getx(getid(p.y.x) - 1);
	}
	cout << ans << endl;
	return 0;
}

// END OF NORMAL PROGRAM

}

int main() // The fake main()
{
	ios::sync_with_stdio(0);
	return sol::main();
}
