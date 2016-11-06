#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = acos(-1);
const double eps = 1e-8;

double r, l, w;

struct point{
	double x, y;
	point(){}
	point(double _x, double _y):
		x(_x), y(_y){}
	point operator - (point _)
	{
		return point(x - _.x, y - _.y);
	}
	double len()
	{
		return sqrt(x * x + y * y);
	}
};

double sqr(double a) {return a * a;}
double dot(point a, point b){return a.x * b.x + a.y * b.y;}
double det(point a, point b){return a.x * b.y - a.y * b.x;}
int cmp(double x)
{
	if (x < -eps) return -1;
	return x > eps;
}

double dist(point p, point s, point t)
{
	if (cmp(dot(p - s, t - s)) < 0) return (p - s).len();
	if (cmp(dot(p - t, s - t)) < 0) return (p - t).len();
	return fabs(det(s - p, t - p) / (s - t).len());
}

double sol()
{
	double a, b;
	scanf("%lf%lf", &a, &b);
	double ans = min(l, w);
	point pbs(l - l * cos(b), l * sin(b));
	point pbe(l, 0);
	point pas(l, w);
	point pae(l - l * cos(a), w + l * sin(a));
	if (cmp(a - PI / 2) < 0)
		ans = min(ans, l * sin(a));
	if (cmp(b - PI / 2) > 0)
		ans = min(ans, w - l * sin(b));
	else
		ans = min(ans, dist(pas, pbs, pbe));
	if (cmp(a - PI / 2) < 0 && cmp(b - PI / 2) <= 0)
		ans = min(ans, dist(pbs, pas, pae));
	return ans;
}
int main()
{
	scanf("%lf%lf%lf", &r, &l, &w);
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%.8f\n", max(0., min(sol() / 2, r)));
	return 0;
}
