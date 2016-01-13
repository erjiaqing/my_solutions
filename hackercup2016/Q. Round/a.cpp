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
vector<pii> pts;
map<long long, int> cnt;

long long sqr(long long x) {return x * x;}
long long calc(pii a, pii b)
{
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int main() // The true main()
{
	int t;
	char buf[256];
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		int n, x, y;
		long long ans = 0;
		cin >> n;
		pts.clear();
		for (int j = 0; j < n; j++)
		{
			cin >> x >> y;
			pts.pb(mp(x, y));
		}
		for (int j = 0; j < n; j++)
		{
			cnt.clear();
			for (int k = 0; k < n; k++)
			{
				if (k == j) continue;
				ans += cnt[calc(pts[j], pts[k])];
				cnt[calc(pts[j], pts[k])]++;
			}
		}
		sprintf(buf, "Case #%d: %lld\n", i, ans);
		cout << buf;
	}
	return 0;
}


// END OF NORMAL PROGRAM

}

int main() // The fake main()
{
	ios::sync_with_stdio(0);
	return sol::main();
}

