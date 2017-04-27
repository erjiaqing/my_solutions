#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;

typedef pair<double, double> point;
point pts[maxn];
#define x first
#define y second
double ans = 0;
int n;

point _(const point &a, const point &b)
{
	return point(a.x - b.x, a.y - b.y);
}

double x(const point &a, const point b)
{
	return a.x * b.y - a.y * b.x;
}

double ll(const point &a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> pts[i].x >> pts[i].y;
	pts[0] = pts[n];
	pts[n + 1] = pts[1];
	double ans = 1e20;
	for (int i = 1; i <= n; i++)
	{
		ans = min(ans, fabs(x(_(pts[i - 1], pts[i]), _(pts[i + 1], pts[i]))) / (ll(_(pts[i - 1], pts[i + 1])) * 2));
	}
	printf("%.10f\n", ans);
	return 0;
}
