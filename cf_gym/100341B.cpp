#include <algorithm>
#include <iostream>
#include <cstring>
#include <utility>
#include <cstdio>
#include <vector>
#include <cmath>
#define PROB "astronomy"
using namespace std;
const int maxn = 10;
const double eps = 1e-8;
const double pi = acos(-1);
typedef pair<double, double> Point;
#define x first
#define y second
int n;
Point p[maxn]; // Point
Point ap[maxn]; // ans-Point
double apv[maxn]; // ans-Point-val

inline double dot(const Point &a, const Point &b)
{
	return a.x * b.x + a.y * b.y;
}
inline double len(const Point &a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}
inline double rad(const Point &a, const Point &b, const Point &o)
{
	Point pa = Point(a.x - o.x, a.y - o.y);
	Point pb = Point(b.x - o.x, b.y - o.y);
	double dt = dot(pa, pb);
	double ln = len(pa) * len(pb);
	return acos(dt / ln);
}
inline double calc(const Point &a)
{
	double ret = 10;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			ret = min(ret, rad(p[i], p[j], a));
	return ret;
}
inline bool check(const Point &a)
{
	for (int i = 0; i < n; i++)
		if (len(Point(p[i].x - a.x, p[i].y - a.y)) < 1 - eps)
			return false;
	return true;
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen(PROB".in", "r", stdin);
	freopen(PROB".out", "w", stdout);
#endif
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	double step = 1e3;
	double nstep = 0.95;
	double teps = 1e-8;
	for (int i = 0; i < maxn; i++)
	{
		ap[i].x = 2e3 * rand() / RAND_MAX - 1000;
		ap[i].y = 2e3 * rand() / RAND_MAX - 1000;
		apv[i] = calc(ap[i]);
	}
	while (step > teps)
	{
		for (int i = 0; i < maxn; i++)
		{
			Point np;
			for (int j = 0; j < 10; j++)
			{
				double theta = 2 * pi * rand() / RAND_MAX;
				double dx = step * cos(theta);
				double dy = step * sin(theta);
				np = Point(ap[i].x + dx, ap[i].y + dy);
				while (!check(np))
				{
					double theta = 2 * pi * rand() / RAND_MAX;
					double dx = step * cos(theta);
					double dy = step * sin(theta);
					np = Point(ap[i].x + dx, ap[i].y + dy);
				}
				double tans = calc(np);
				if (tans > apv[i])
				{
					apv[i] = tans;
					ap[i] = np;
				}
			}
		}
		step = step * nstep;
	}
	double ans = 0;
	int apn = 0;
	for (int i = 0; i < maxn; i++)
		if (apv[i] > ans)
		{
			ans = apv[i];
			apn = i;
		}
	printf("%.6f %.6f\n", ap[apn].x, ap[apn].y);
	return 0;
}
