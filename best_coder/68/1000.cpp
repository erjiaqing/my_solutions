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

double sqr(double x) {return x * x;}

double getcor(double x0, double y0, double x1, double y1)
{
	return sqrt(sqr(x0 - x1) + sqr(y0 - y1));
}

int main() // The true main()
{
	int t, x, y;
	cin >> t;
	while (t--) {
		cin >> x >> y;
		double l = 0, r = 100000000;
		double mi = 1e20;
		while (r - l > 1e-8)
		{
			double yl, yr;
			yl = (r - l) / 3 + l;
			yr = (r - l) * 2 / 3 + l;
			//cerr << l << " " << yl << " " << yr << " " << r << endl;
			double xl, xr;
			xl = x * y / yl;
			xr = x * y / yr;
			double a1 , a2;
			a1 = getcor(x, y, 0, yl + y) * getcor(x, y, xl + x, 0);
			a2 = getcor(x, y, 0, yr + y) * getcor(x, y, xr + x, 0);
			mi = min(mi, min(a1, a2));
			if (a2 < a1) l = yl;
			else r = yr;
		}
		//cerr << l << endl;
		printf("%.0f\n", mi);
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

