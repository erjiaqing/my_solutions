#include <bits/stdc++.h>
using namespace std;
#define sqr( x ) ( ( x ) * ( x ) )
int main()
{
	long long x0, y0, z0;
	long long x1, y1, z1;
	long long x2, y2, z2;
	long long xr, yr, zr;
	cin >> x0 >> y0 >> z0;
	cin >> x1 >> y1 >> z1;
	cin >> x2 >> y2 >> z2;
	xr = x0, yr = y0, zr = z0;
	xr = min(xr, x2);xr = max(xr, x1);
	yr = min(yr, y2);yr = max(yr, y1);
	zr = min(zr, z2);zr = max(zr, z1);
	printf("%lld\n", sqr(xr - x0) + sqr(yr - y0) + sqr(zr - z0));
	return 0;
}
