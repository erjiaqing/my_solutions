#include <bits/stdc++.h>
using namespace std;

double eps = 1e-6;

int n;

struct point{
	double x, y;
	point(){}
	point(double a, double b):
		x(a), y(b){}
	friend point operator - (const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend point operator + (const point &a, const point &b) {
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator * (const double x, const point &b)
	{
		return point(b.x * x, b.y * x);
	}
	friend point operator / (const point &a, const double x)
	{
		return point(a.x / x, a.y / x);
	}
	double norm() {
		return sqrt(x * x + y * y);
	}
}pt[120];
int totpt;

struct line{
	point a, b;
	point _a, _b, dir;
	double v;
	int id;
}ln[12];

bool parallel[12][12];

double det(const point &a, const point &b){return a.x * b.y - a.y * b.x;}
double dist(const point &a, const point &b){return (a - b).norm();}

bool line_make_point(line a, line b, point &res)
{
	double s1 = det(a.a - b.a, b.b - b.a);
	double s2 = det(a.b - b.a, b.b - b.a);
	res = (s1 * a.b - s2 * a.a) / (s1 - s2);
	return true;
}

int sgn(double x)
{
	return x < -eps ? -1 : x > eps;
}

bool _cmp(const point &p1, const point &p2)
{
	double tmp = det((p1 - pt[0]), (p2 - pt[0]));
	if (sgn(tmp) > 0) return true;
	else if (sgn(tmp) == 0 && sgn((p1 - pt[0]).norm() - (p2 - pt[0]).norm()) <= 0)
		return true;
	return false;
}

double graham(int n)
{
	int top;
	static int sta[120];
	point p0;
	int k = 0;
	p0 = pt[0];
	for (int i = 1; i < n; i++)
	{
		if ( (p0.y > pt[i].y) || (p0.y == pt[i].y && p0.x > pt[i].x) )
		{
			p0 = pt[i];
			k = i;
		}
	}
	swap(pt[k], pt[0]);
	sort(&pt[1], &pt[n], _cmp);
	if (n < 3)
		return 0.;
//	cerr << "Graham\n";
///	for (int i = 0; i < n; i++)
//		cerr << pt[i].x << ' ' << pt[i].y << endl;
	sta[0] = 0;
	sta[1] = 1;
	top = 2;
	for (int i = 2; i < n; i++)
	{
		while (top > 1 &&
				sgn(det(pt[sta[top - 1]] - pt[sta[top - 2]], pt[i] - pt[sta[top - 2]])
					) <= 0)
			top--;
		sta[top++] = i;
	}
//	cerr << top << endl;
	double ans = 0;
	for (int i = 2; i < top; i++)
		ans += fabs(det(pt[sta[i]] - pt[0], pt[sta[i - 1]] - pt[0]));
//	cerr << "Graham " << ans / 2 << endl;
	return ans / 2;
}

int prepare()
{
	int tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (!parallel[i][j])
			{
				line_make_point(ln[i], ln[j], pt[tot]);
				tot++;
			}/*
	for (int i = 0; i < tot; i++)
		cerr << "Pt " << pt[i].x << ' ' << pt[i].y << endl;
	cerr << "Prep " << tot << endl;*/
	return tot;
}

double f(double t)
{
//	cerr << "T = " << t << endl;
	for (int i = 1; i <= n; i++)
	{
		ln[i].a = ln[i]._a + ln[i].v * t * ln[i].dir;
		ln[i].b = ln[i]._b + ln[i].v * t * ln[i].dir;
	}
	return graham(prepare());
}

template<class T>
double romberg(const T &f, double a, double b, double eps = 1e-4)
{
	vector<double> t;
	double h = b - a, last, curr;
	int k = 1, i = 1;
	t.push_back(h * (f(a) + f(b)) / 2);
	do
	{
		last = t.back();
		curr = 0;
		double x = a + h / 2;
		for (int j = 0; j < k; j++)
		{
			curr += f(x);
			x += h;
		}
		curr = (t[0] + h * curr) / 2;
		double k1 = 4.0 / 3.0, k2 = 1.0 / 3.0;
		for (int j = 0; j < i; j++)
		{
			double temp = k1 * curr - k2 * t[j];
			t[j] = curr;
			curr = temp;
			k2 /= 4 * k1 - k2;
			k1 = k2 + 1;
		}
		t.push_back(curr);
		k *= 2;
		h /= 2;
		i++;
	}while (fabs(last - curr) > eps);
	return t.back();
}

int main()
{
	freopen("convex.in", "r", stdin);
	freopen("convex.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		double a, b, c, d, v;
		cin >> a >> b >> c >> d >> v;
		ln[i]._a = point(a, b);
		ln[i]._b = point(c, d);
		ln[i].dir = (ln[i]._b - ln[i]._a);
		ln[i].dir = ln[i].dir / ln[i].dir.norm();
		swap(ln[i].dir.x, ln[i].dir.y);
		ln[i].dir.y = -ln[i].dir.y;
//		cerr << ln[i].dir.x << ' ' << ln[i].dir.y << endl;
		ln[i].v = v;
		ln[i].id = i;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			parallel[i][j] = (sgn(det(ln[i]._b - ln[i]._a, ln[j]._b - ln[j]._a)) == 0);
	double t;
	cin >> t;
	printf("%.10f\n", romberg(f, 0, t) / t);
	return 0;
}
