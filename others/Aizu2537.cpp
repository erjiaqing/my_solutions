#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int sgn(double x)
{
	if (abs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}

struct Point{
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
	double len(){return sqrt(x * x + y * y);}
	Point operator - (Point _){return Point(x - _.x, y - _.y);}
};

typedef Point Vector;

struct Line{
	Point base;
	Vector dir;
};

double dot(Point a, Point b)
{
	return a.x * b.x + a.y * b.y;
}

double w, h, r, vx, vy, lft;
int n;

vector<Point> ball;
Line st;

double check_hit(Point pt)
{
	pt.x -= st.base.x;
	pt.y -= st.base.y;
	double dist = pt.len();
	double vec = st.dir.len();
	double dotval = dot(st.dir, pt);
	double a = 1, b = - 2 * dotval / vec, c = dot(pt, pt) - 4 * r * r;
	if (sgn(b * b - 4 * c) < 0)
		return 9999999;
	return (-b - sqrt(b * b - 4 * c)) / 2;
}

void sol()
{
	scanf("%lf%lf%lf%lf%lf", &w, &h, &r, &vx, &vy);
	scanf("%lf%lf", &st.base.x, &st.base.y);
	ball.clear();
	for (int i = 1; i < n; i++)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		ball.push_back(Point(x, y));
	}
	st.dir.x = vx;st.dir.y = vy;
	lft = 10000.;
	int ans = -1;
	while ((sgn(lft) > 0) && (ans == -1))
	{
		Line nxt = st;
//		printf("At (%f, %f) / Dir (%f, %f) / Left %f\n", st.base.x, st.base.y, st.dir.x, st.dir.y, lft);
		if (sgn(st.dir.x) > 0)
		{
			double hit_t = (w - r - st.base.x) / st.dir.x;
			double hit_y = hit_t * st.dir.y + st.base.y;
			if (sgn(hit_y - r) >= 0 && sgn(h - hit_y - r) >= 0)
			{
				nxt.base.y = hit_y;
				nxt.base.x = w - r;
				nxt.dir.x = -st.dir.x;
			}
		} else if (sgn(st.dir.x) < 0)
		{
			double hit_t = (r - st.base.x) / st.dir.x;
			double hit_y = hit_t * st.dir.y + st.base.y;
			if (sgn(hit_y - r) >= 0 && sgn(h - hit_y - r) >= 0)
			{
				nxt.base.y = hit_y;
				nxt.base.x = r;
				nxt.dir.x = -st.dir.x;
			}
		}
		if (sgn(st.dir.y) > 0)
		{
			double hit_t = (h - r - st.base.y) / st.dir.y;
			double hit_x = hit_t * st.dir.x + st.base.x;
			if (sgn(hit_x - r) >= 0 && sgn(w - hit_x - r) >= 0)
			{
				nxt.base.x = hit_x;
				nxt.base.y = h - r;
				nxt.dir.y = -st.dir.y;
			}
		} else if (sgn(st.dir.y) < 0)
		{
			double hit_t = (r - st.base.y) / st.dir.y;
			double hit_x = hit_t * st.dir.x + st.base.x;
			if (sgn(hit_x - r) >= 0 && sgn(w - hit_x - r) >= 0)
			{
				nxt.base.x = hit_x;
				nxt.base.y = r;
				nxt.dir.y = -st.dir.y;
			}
		}
		double gonxt = (nxt.base - st.base).len();
		double hitlen = 999999;
		for (int i = 0; i < (int) ball.size(); i++)
		{
			double golen = check_hit(ball[i]);
			if (sgn(golen) >= 0 && golen < hitlen && golen < lft)
			{
				hitlen = golen;
				ans = i;
			}
		}
		st = nxt;
		lft -= gonxt;
	}
	printf("%d\n", (~ans) ? ans + 2 : -1);
}

int main()
{
	while ((~scanf("%d", &n)) && n)
		sol();
	return 0;
}
