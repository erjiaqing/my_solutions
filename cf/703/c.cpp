#include <bits/stdc++.h>
using namespace std;
double mit;
typedef pair<double, double> pdd;
vector<pdd> pd;
#define x first
#define y second
int n, m;
double v, u;
bool check(double t)
{
	for (int i = 0; i < n; i++)
	{
		pdd a = pd[i], b = pd[i + 1];
		double x1 = a.y / u + v * t;
		double x2 = b.y / u + v * t;
		if ((a.x - x1) * (b.x - x2) < 0)
			return false;
	}
	return true;
}
int main()
{
	bool flg = 1;
	scanf("%d%d%lf%lf", &n, &m, &v, &u);
	mit = m / u;
	for (int i = 0; i < n; i++)
	{
		double tx, ty;
		scanf("%lf%lf", &tx, &ty);
		if (ty / u * v > tx)
			flg = false;
		mit = max(mit, tx / v - ty / u + m / u);
//		pd.push_back(pdd(tx + 1e-8, ty + 1e-8));
//		if (tx > 0) flg = 0;
	}
/*	pd.push_back(pd[0]);
	if (check(0.))
	{
		printf("%.10f\n", 1. * m / u);
		return 0;
	}
	double l = 0, r = 1e9;
	while (r - l > 1e-8)
	{
		double mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}*/
	printf("%.10f\n", flg ? m / u : mit);
	return 0;
}
