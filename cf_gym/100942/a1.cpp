#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <utility>
#include <vector>
#include <cassert>
using namespace std;

namespace ejq{
const long double pi = acos((long double)(-1.0));
const long double eps = 1e-12;

struct circle{
	long double cx, cy, r, rr;
	circle(){}
	circle(long double _cx, long double _cy, long double _r, long double _rr):
		cx(_cx), cy(_cy), r(_r), rr(_rr){}
}a[2], b[2];

long double x0, y0, x1, y1, x2, y2, m1, m2, l1, l2;
long double cx, cy, dx, dy, tl;

long double ax, ay;

long double sqr(long double x)
{
	return x * x;
}
long double dest(long double x, long double y)
{
	return sqrt(sqr(x) + sqr(y));
}
long double sgn(long double x)
{
	return ((fabs(x) < eps) ? 0 : (x < 0 ? -1 : 1));
}

bool check(long double x, long double y)
{
	long double c = dest(x1 - x0, y1 - y0),
		   a = dest(x - x0, y - y0),
		   b = dest(x - x1, y - y1);
	if (sgn((a * a + b * b - c * c) / (2 * a * b) - cos(m1))) return false;
	c = dest(x1 - x2, y1 - y2),
	a = dest(x - x1, y - y1),
	b = dest(x - x2, y - y2);
	if (sgn((a * a + b * b - c * c) / (2 * a * b) - cos(m2))) return false;
	return true;
}

bool solve(const circle &a, const circle &b)
{
	long double len = dest(a.cx - b.cx, a.cy - b.cy);
	if (sgn(len - (a.r + b.r)) >= 0)
		return false;
	if (sgn(len) == 0)
	{
		ax = a.cx + a.r * sin(2424234);
		ay = a.cy + a.r * cos(2424234);
		return true;
	}
//	long double _ = a.r, __ = len, c = b.r;
//	long double alpha = (a.rr + sqr(__) - b.rr) / (2 * _ * __);
	long double dx = b.cx - a.cx;
	long double dy = b.cy - a.cy;
	long double dl = dest(dx, dy);
	dx /= dl;
	dy /= dl;
	long double rx = -dy;
	long double ry = dx;
	long double aa = (a.rr - b.rr + sqr(a.cx - b.cx) + sqr(a.cy - b.cy)) / (2 * len);
	//fprintf(stderr, "dx = %f, dr = %f, rx = %f, ry = %f\n", dx, dy, rx, ry);
	long double ql = aa;
	long double qr = sqrt(a.rr - sqr(aa));
	long double xx = a.cx + ql * dx + qr * rx;
	long double yy = a.cy + ql * dy + qr * ry;
	if ((sgn(xx - x0) || sgn(yy - y0)) && (sgn(xx - x2) || sgn(yy - y2)) && (sgn(xx - x1) || sgn(yy - y1)) && check(xx, yy))
	{
		ax = xx;
		ay = yy;
		return true;
	}
	xx = a.cx + ql * dx - qr * rx;
	yy = a.cy + ql * dy - qr * rx;
	if ((sgn(xx - x0) || sgn(yy - y0)) && (sgn(xx - x2) || sgn(yy - y2)) && (sgn(xx - x1) || sgn(yy - y1)) && check(xx, yy))
	{
		ax = xx;
		ay = yy;
		return true;
	}
	return false;
}

bool sol()
{
	cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> m1 >> m2;
//	scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x0, &y0, &x1, &y1, &x2, &y2, &m1, &m2);
	m1 = m1 * pi / 180;
	m2 = m2 * pi / 180;
	l1 = dest(x0 - x1, y0 - y1);
	l2 = dest(x1 - x2, y1 - y2);

	long double yxj1 = m1 * 2, yxj2 = m2 * 2;
	if (yxj1 > pi) yxj1 = 2 * pi - yxj1;
	if (yxj2 > pi) yxj2 = 2 * pi - yxj2;

	// solve r0;
	cx = (x1 + x0) / 2;
	cy = (y1 + y0) / 2;
	dy = (x1 - x0);
	dx = (y0 - y1);
	long double ql;
	ql = tl = dest(dy, dx);
	dx /= tl;dy /= tl;
	tl = l1 / 2;
	if (sgn(tan(yxj1 / 2)))
	{
		long double ln = tl / tan(yxj1 / 2);
		long double rr = tl / sin(yxj1 / 2);
		a[0] = circle(cx + dx * ln, cy + dy * ln, rr, tl * tl / (sqr(sin(yxj1))));
		a[1] = circle(cx - dx * ln, cy - dy * ln, rr, tl * tl / (sqr(sin(yxj1))));
	} else
	{
		a[0] = circle(cx, cy, tl, tl);
		a[1] = circle(cx, cy, tl, tl);
	}
	// solve r1
	cx = (x2 + x1) / 2;
	cy = (y2 + y1) / 2;
	dy = (x2 - x1);
	dx = (y1 - y2);
	ql = tl = dest(dy, dx);
	dx /= tl;dy /= tl;
	tl = l2 / 2;
	if (sgn(tan(yxj2 / 2)))
	{
		long double ln = tl / tan(yxj2 / 2);
		long double rr = tl / sin(yxj2 / 2);
		b[0] = circle(cx + dx * ln, cy + dy * ln, rr, tl * tl / (sqr(sin(yxj2))));
		b[1] = circle(cx - dx * ln, cy - dy * ln, rr, tl * tl / (sqr(sin(yxj2))));
	} else
	{
		b[0] = circle(cx, cy, tl, tl);
		b[1] = circle(cx, cy, tl, tl);
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (solve(a[i], b[j]))
				return true;
	return false;
}
int main()
{
	ios::sync_with_stdio(0);
	int t = 0;
	cin >> t;
	char buf[100];
//	scanf("%d", &t);
//	cin >> t;
	while (t--)
	{
		assert(sol());
		sprintf(buf, "%.10f %.10f\n", double(ax), double(ay));
		cout << buf;
		//printf("%.10f %.10f\n", ax, ay);
	}
	return 0;
}
}
int main()
{
	return ejq::main();
}
