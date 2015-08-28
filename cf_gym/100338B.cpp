#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <cmath>
using namespace std;
//-- 浮点数运算
const double eps=1e-8;
const double gold = (sqrt(5) - 1) / 2;
bool _l (double a,double b){return a<b-eps;}
bool _g (double a,double b){return b<a-eps;}
bool _le(double a,double b){return a<b+eps;}
bool _ge(double a,double b){return b<a+eps;}
bool _eq(double a,double b){return fabs(a-b)<eps;}
bool _ne(double a,double b){return fabs(a-b)>eps;}
//-- 点和向量
struct Point
{
    double x,y;
    Point(){}
	Point(const Point &_p):x(_p.x), y(_p.y){}
    Point(double _x,double _y):x(_x),y(_y){}
    bool   operator == (Point a){return (fabs(a.x-x)<eps)&&(fabs(a.y-y)<eps);}
    bool   operator != (Point a){return !((*this)==a);}
    bool   operator <  (Point a){return _l(a.y,y)||(_eq(a.y,y)&&_l(a.x,x));}
    bool   operator >  (Point a){return _l(y,a.y)||(_eq(a.y,y)&&_l(x,a.x));}
    Point  operator +  (Point a){return Point(x+a.x,y+a.y);}
    Point  operator -  (Point a){return Point(x-a.x,y-a.y);}
    double operator *  (Point a){return a.x*x+a.y*y;}
    double operator &  (Point a){return x*a.y-y*a.x;}
    Point  operator ~  (void)   {return Point(y,-x);}
    friend Point operator *  (double a,Point  b){return Point(a*b.x,a*b.y);}
    friend Point operator *  (Point  b,double a){return Point(a*b.x,a*b.y);}
	friend Point operator /  (Point  b,double a){return Point(b.x/a,b.y/a);}
};
//-- Line
struct Line
{
    Point a,b;
	Line(){}
	Line(Point _a, Point _b):a(_a), b(_b){}
    Point operator * (Point p)
    {
        double x1 = a.x,x2=b.x,y1=a.y,y2=b.y;
        double A=y1-y2,B=x2-x1,C=x1*y2-x2*y1;
        double delta=(A*p.x+B*p.y+C)/(A*A+B*B);
        return Point(p.x-2*A*delta,p.y-2*B*delta);
    }
	bool on(Point p) // 判断是否在线段上
	{
		if (_eq((p - a) & (b - a), 0))
		{
			double lx = min(a.x, b.x);
			double rx = max(a.x, b.x);
			return _l(lx, p.x) && _l(p.x, rx);
		}
		return 0;
	}
	bool online(Point p)
	{
		return _eq((p - a) & (b - a), 0);
	}
};
double dist(Point a,Point b){return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));}
typedef Point Vector;
//-- 完毕
struct Circle
{
	Point o;
	double r;
	Circle(Point a, Point b, Point c) //给定三点
	{
		// 注意，传入时判断三点共线
		Point p2 = b - a;
		Point p3 = c - a;
		o.y = (p2.x * p3.x * (p3.x - p2.x) + p2.x * p3.y * p3.y - p3.x * p2.y * p2.y) / (2 * (p2.x * p3.y - p3.x * p2.y));
		o.x = (p2.x * p2.x + p2.y * p2.y - 2 * p2.y * c.y) / (2 * p2.x);
		o = o + a;
		r = dist(o, a);
	}
	Circle(Point a, Point b) //给定直径
	{
		o = (a + b) / 2;
		r = dist(a, b) / 2;
	}
	Circle(Point _o, double _r):o(_o), r(_r){} //圆心半径
	Circle(Circle &_c):o(_c.o), r(_c.r){} //复制现有圆
	Circle(){} //暂不构造
};
double x11, y11, x12, y12, x21, y21, x22, y22;
Circle ans;
void rotate(Point &p, double c)
{
	double r = dist(p, Point(0, 0));
	double theta = atan2(p.y, p.x) + c;
	p.x = r * cos(theta);
	p.y = r * sin(theta);
}
void calc()
{
	// 注意：坐标需扰动／旋转
	Point p11(x11, y11);
	Point p12(x12, y12);
	Point p21(x21, y21);
	Point p22(x22, y22);
	rotate(p11, gold);
	rotate(p12, gold);
	rotate(p21, gold);
	rotate(p22, gold);
	Line la(p11, p12);
	Line lb(p21, p22);
	Vector v1 = p12 - p11;
	Vector v2 = p22 - p21;
	double k1 = (p12.y - p11.y) / (p12.x - p11.x);
	double b1 = p12.y - k1 * p12.x;
	double k2 = (p22.y - p21.y) / (p22.x - p21.x);
	double b2 = p22.y - k2 * p22.x;
	Point cp2 = (p21 + p22) / 2;
	Point cp1 = (p11 + p12) / 2;
	// Case1 二线段共线
	if (_eq(v1 & v2, 0))
	{
		// Case 1.1 1.2 两线段有重合
		if (la.on(cp2))
		{
			ans = Circle(cp2, cp2 + v1 * 1e5);
			return;
		}
		else if (lb.on(cp1))
		{
			ans = Circle(cp1, cp1 + v2 * 1e5);
			return;
		}
		else
		{
			// Case 1.3 两线段中点均不在另一线上
			// 无重合，或重合不多
			Point tp = (cp1 + cp2) / 2;
			if (la.online(tp))
				ans = Circle(cp1, cp2);
			else
			{
				Vector vec = cp2 - cp1;
				double rad = (atan2(vec.y, vec.x)) + acos(-1) / 2;
				vec = Vector(1e5 * cos(rad), 1e5 * sin(rad));
				ans = Circle((cp1 + cp2) / 2.0, (cp1 + cp2) / 2.0 + vec);
			}
		}
		//return;
	}
	// Case 2 线段不共线
	double cx = (b2 - b1) / (k1 - k2);
	double cy = cx * k1 + b1;
	Point cp = Point(cx, cy);
	// Case 2.1有交点
	if (la.on(cp) && lb.on(cp))
	{
		double r1 = atan2(v1.y, v1.x);
		double r2 = atan2(v2.y, v2.x);
		double rad = (r1 + r2) / 2;
		Vector vec(5e5 * cos(rad), 5e5 * sin(rad));
		ans = Circle(cp, cp + vec);
		return;
	}
	// Case 2.2无交点
	// Case 2.2无交点
	double td = 1e5;
	if (td > dist(p11, p21))
	{
		td = dist(p11, p21);
		ans = Circle(p11, p21);
	}
	if (td > dist(p11, p22))
	{
		td = dist(p11, p22);
		ans = Circle(p11, p22);
	}
	if (td > dist(p12, p21))
	{
		td = dist(p12, p21);
		ans = Circle(p12, p21);
	}
	if (td > dist(p12, p22))
	{
		td = dist(p12, p22);
		ans = Circle(p12, p22);
	}
	ans.r += 0.002;}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif
	while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x11, &y11, &x12, &y12, &x21, &y21, &x22, &y22))
	{
		if (fabs(x11) + fabs(x12) + fabs(x21) + fabs(x22) + 
			fabs(y11) + fabs(y12) + fabs(y21) + fabs(y22) < eps)
			break;
		calc();
		rotate(ans.o, -gold);
		printf("%.6f %.6f %.6f\n", ans.o.x, ans.o.y, ans.r);
	}
	return 0;
}
