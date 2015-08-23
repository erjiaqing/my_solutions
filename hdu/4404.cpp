#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define x first
#define y second

#define x0 x0233
#define y0 y0233
#define v0 v0233

const int maxn = 100 + 5;
const double eps = 1e-8;
typedef pair<double , double> point;
const double pi = acos(-1);
int n;
double x0 , y0 , v0 , vx , vy , theta , t , g , r;
point res[maxn];
double esqrt(double);
double sqr(const double &x)
{
	return x * x;
}
int dcmp(double k)
{
	return k < -eps ? -1 : k > eps ? 1 : 0;
}
double dot(const point &a , const point &b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(const point &a , const point &b)
{
	return a.x * b.y - a.y * b.x;
}
double abs(const point &o)
{
	return sqrt(dot(o , o));
}
point operator - (const point &a , const point &b)
{
	return point(a.x - b.x , a.y - b.y);
}
point operator * (const point &a , const double b)
{
	return point(a.x * b , a.y * b);
}
point operator / (const point &a , const double b)
{
	return point(a.x / b , a.y / b);
}
void circle_cross_line(point a , point b , point o , double r , point ret[] , int &num)
{
	double x0 = o.x , y0 = o.y;
	double x1 = a.x , y1 = a.y;
	double x2 = b.x , y2 = b.y;
	double dx = x2 - x1 , dy = y2 - y1;
	double A = dx * dx + dy*dy;
	double B = 2 * dx * (x1 - x0) + 2 * dy * (y1 - y0);
	double C = sqr(x1 - x0) + sqr(y1 - y0) - sqr(r);
	double delta = B*B - 4 * A * C;
	num = 0;
	if (dcmp(delta) >= 0)
	{
		double t1 = (-B - esqrt(delta)) / (2 * A);
		double t2 = (-B + esqrt(delta)) / (2 * A);
		if (dcmp(t1 - 1) <= 0 && dcmp(t1) >= 0)
			ret[num++] = point(x1 + t1 * dx , y1 + t1 * dy);
		if (dcmp(t2 - 1) <= 0 && dcmp(t2) >= 0)
			ret[num++] = point(x1 + t2 * dx , y1 + t2 * dy);
	}
}
point crosspt(const point &a , const point &b , const point &p , const point &q)
{
	double a1 = cross(b - a,p - a);
	double a2 = cross(b - a,q - a);
	return (p * a2 - q * a1) / (a2 - a1);
}
double esqrt(double n)
{
	return sqrt(max(0.0 , n));
}
double sector_area(const point &a , const point &b)
{
	double theta = atan2(a.y , a.x) - atan2(b.y , b.x);
	while (theta <= 0)
		theta += 2 * pi;
	while (theta > 2 * pi)
		theta -= 2 * pi;
	theta = min(theta , 2 * pi - theta);
	return r * r * theta / 2;
}
double calc(const point &a , const point &b)
{
	point p[2];
	int num = 0;
	int ina = dcmp(abs(a) - r) < 0;
	int inb = dcmp(abs(b) - r) < 0;
	if (ina)
	{
		if (inb)
			return fabs(cross(a , b)) / 2.0;
		else
		{
			circle_cross_line(a , b , point(0,0) , r , p , num);
			return sector_area(b , p[0]) + fabs(cross(a , p[0])) / 2.0;
		}
	}else
	{
		if (inb)
		{
			circle_cross_line(a , b , point(0,0) , r , p , num);
			return sector_area(p[0] , a) + fabs(cross(p[0] , b)) / 2.0;
		}else
		{
			circle_cross_line(a , b , point(0,0) , r , p , num);
			if (num == 2)
			{
				return sector_area(a , p[0]) + sector_area(p[1] , b) + fabs(cross(p[0] , p[1])) / 2.0;
			}else
			{
				return sector_area(a , b);
			}
		}
	}
}
double area()
{
	double ret = 0;
	for (int i = 0 ; i < n ; i++)
	{
		int sgn = dcmp(cross(res[i] , res[i + 1]));
		if (sgn)
		{
			ret += sgn * calc(res[i] , res[i + 1]);
		}
	}
	return ret;
}
int main()
{
	while (scanf("%lf%lf%lf%lf%lf%lf%lf" , &x0 , &y0 , &v0 , &theta , &t , &g , &r) == 7)
	{
		if (r < eps)
			break;
		theta = theta * pi / 180;
		vx = v0 * cos(theta);
		vy = v0 * sin(theta);
		x0 += vx * t;
		y0 += t * (vy + (vy - t * g)) / 2;
//		cerr << x0 << " " << y0 << endl;
		scanf("%d" , &n);
		for (int i = 0 ; i < n ; i++)
		{
			scanf("%lf%lf" , &res[i].x , &res[i].y);
			res[i].x -= x0;
			res[i].y -= y0;
		}
		res[n] = res[0];
		printf("%.2f\n" , fabs(area()));
	}
	return 0;
}
