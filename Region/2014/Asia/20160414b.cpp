#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
double k, r, h, y0;
double sqr(double x){return x * x;}
double f(double y)
{
	double ans1 = h * (sqrt(4 - y * y) - sqrt(max(.0, r * r - (y*y + sqr(k * (y - y0) + h)))));
	double int_up = sqrt(r * r - y * y);
	double int_dn = sqrt(max(.0, r * r - (y*y + sqr(k * (y - y0) + h))));
	double int_r2 = r * r - y * y;
	double int_r = sqrt(int_r2);
	double dega = acos(int_up / sqrt(int_r2));
	double degb = acos(int_dn / sqrt(int_r2));
	double upval = int_r * sin(dega), dnval = int_r * sin(degb);
	double area = (fabs(int_r * (degb - dega)) + int_up * upval - int_dn * dnval) / 2 + int_dn * dnval;
	return area + ans1;
}
double fst(double l, double r, double fl, double fm, double fr)
{
	return (fl + 4 * fm + fr) * (r - l) / 6;
}
double simpson(double l, double r, double fl, double fm, double fr)
{
	double m = (l + r) / 2;
	double lm = f((l + m) / 2), rm = r((r + m) / 2);
	double st = fst(l, r, fl, fm, fr), sl = fst(l, m, fl, lm, fm),
		   sr = fst(m, r, fm, rm, fr);
	if (fabs(st - sl - sr) < 1e-5)
		return st;
	else
		return simpson(l, m, fl, lm, fm) + simpson(m, r, fm, rm, fr);
}
int main()
{
	return 0;
}
