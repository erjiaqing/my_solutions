#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;
const double eps = 1e-8;
typedef pair<double, double> pdd;
vector<pdd> s;
double d;
int n, b;
int sgn(double x)
{
	return (fabs(x) < eps ? 0 : (x < 0 ? -1 : 1));
}
double solve(int b)
{
	double td = d / b;
	double ct = td / 2;
	double minh = 0;
	for (pdd rr : s)
	{
		double rs = rr.first;
		double rh = rr.second;
		double tr = rs - int(rs / td) * td;
		if (rs < 0) rs += td;
		if (rs >= td) rs -= td;
		if (sgn(rs) == 0 || sgn(rs - td) == 0) return 1e100;
		double k = rh / (tr * (td - tr));
		minh = max(minh, k * ct * ct);
		//printf("x = %.6f, y = %.6f, h = %.6f\n", tr, rh, k * ct * ct);
	}
	minh = max(minh, td / 4);
	return sqrt(2 * minh + td * td / minh / 8);
}
int main()
{
	while (~scanf("%lf%d%d", &d, &n, &b))
	{
		double ans = 1e100;
		s.clear();
		for (int i = 0; i < n; i++)
		{
			double a, b;
			scanf("%lf%lf", &a, &b);
			s.push_back(pdd(a, b));
		}
		for (int i = 0; i <= b; i++)
			ans = min(ans, solve(i + 1));
		printf("%.8f\n", ans);
	}
	return 0;
}
