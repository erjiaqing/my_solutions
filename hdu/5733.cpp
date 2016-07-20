#include <bits/stdc++.h>
using namespace std;
struct point{
	double x, y, z;
	point(){}
	point(double _x, double _y, double _z):
		x(_x), y(_y), z(_z){}
	int read()
	{
		return scanf("%lf%lf%lf", &x, &y, &z);
	}
	point X(point p)
	{
		return point(
				y * p.z - z * p.y,
				z * p.x - x * p.z,
				x * p.y - y * p.x);
	}
	void md(double _)
	{
		x /= _;y /= _;z /= _;
	}
	void _()
	{
		x = -x;y = -y;z = -z;
	}
	double dist()
	{
		return sqrt(x * x + y * y + z * z);
	}
	point _(point p)
	{
		return point(x - p.x, y - p.y, z - p.z);
	}
	double o(point p)
	{
		return x * p.x + y * p.y + z * p.z;
	}
	void print()
	{
		printf("%.3f %.3f %.3f\n", x, y, z);
	}
}a, b, c, d;
double m[3][4];
double det()
{
	return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
		+ m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2])
		+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}
#define reset_matrix {\
		m[0][0] = mabc.x - mabd.x;m[0][1] = mabc.y - mabd.y;m[0][2] = mabc.z - mabd.z;m[0][3] = dabc - dabd;\
		m[1][0] = mabc.x - macd.x;m[1][1] = mabc.y - macd.y;m[1][2] = mabc.z - macd.z;m[1][3] = dabc - dacd;\
		m[2][0] = mabc.x - mbcd.x;m[2][1] = mabc.y - mbcd.y;m[2][2] = mabc.z - mbcd.z;m[2][3] = dabc - dbcd;\
}
int main()
{
	while (~a.read())
	{
		b.read();c.read();d.read();
		point rb = b._(a),
		rc = c._(a),
		rd = d._(a),
		ra(0,0,0);
		point mabc = rb.X(rc),
			  mabd = rb.X(rd),
			  macd = rc.X(rd),
			  mbcd = (d._(c)).X(b._(c));
		double dabc = 0, dabd = 0, dacd = 0, dbcd = mbcd.o(rc);
		if (fabs(rb.X(rc).o(rd)) < 1e-6)
		{
			puts("O O O O");
			continue;
		}
		double labc = mabc.dist(),
			   labd = mabd.dist(),
			   lacd = macd.dist(),
			   lbcd = mbcd.dist();
		mabc.md(labc);mabd.md(labd);macd.md(lacd);mbcd.md(lbcd);
		if (mabc.o(rd) < 0) mabc._();
		if (mabd.o(rc) < 0) mabd._();
		if (macd.o(rb) < 0) macd._();
		if (mbcd.o(a._(c)) < 0) mbcd._();
		dabc = 0, dabd = 0, dacd = 0, dbcd = mbcd.o(rc);
		reset_matrix
		double det0 = det();
		if (fabs(det0) < 1e-6)
		{
			puts("O O O O");
			continue;
		}
		m[0][0] = dabc - dabd;m[1][0] = dabc - dacd;m[2][0] = dabc - dbcd;
		double x = det() / det0;
		reset_matrix
		m[0][1] = dabc - dabd;m[1][1] = dabc - dacd;m[2][1] = dabc - dbcd;
		double y = det() / det0;
		reset_matrix
		m[0][2] = dabc - dabd;m[1][2] = dabc - dacd;m[2][2] = dabc - dbcd;
		double z = det() / det0;
		point p0(x, y, z);
		double r = mabc.o(p0);
		printf("%.4f %.4f %.4f %.4f\n", p0.x + a.x, p0.y + a.y, p0.z + a.z, r);
	}
	return 0;
}
