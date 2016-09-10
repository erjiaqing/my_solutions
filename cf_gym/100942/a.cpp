#include <iostream>
#include <cmath>
using namespace std;
namespace e
{
typedef long double ld;
const ld pi = acos(ld(-1));
const ld eps = 1e-8;
char buf[256];
int sgn(ld _x)
{
	return (fabs(_x) < eps) ? 0 : (_x < 0 ? -1 : 1);
}

template <typename T>
struct point
{
	T x, y;
	point():
		x(0), y(0){}
	point(const point<T> &_):
		x(_.x), y(_.y){}
	point(const T &_x, const T &_y):
		x(_x), y(_y){}
	point<T> operator + (const point<T> &_) const
	{
		return point<T>(x + _.x, y + _.y);
	}
	point<T> operator - (const point<T> &_) const
	{
		return point<T>(x - _.x, y - _.y);
	}
	T operator * (const point<T> &_) const
	{
		return (x * _.x + y * _.y);
	}
	point<T> operator * (const T &_) const
	{
		return point(x * _, y * _);
	}
	point<T> operator / (const T &_) const
	{
		return point(x / _, y / _);
	}
	point<T> operator ~() const
	{
		return point<T>(-y, x);
	}
	bool operator == (const point<T> &_) const
	{
		return sgn(x - _.x) == 0 && sgn(y - _.y) == 0;
	}
	bool operator != (const point<T> &_) const
	{
		return !(*this == _);
	}
	T dist2() const
	{
		return x * x + y * y;
	}
	T dist() const
	{
		return sqrt(dist2());
	}
	T angular(const point<T> &_0, const point<T> &_1) const
	{
		T c = (_1 - _0).dist2(),
		  bb = (_1 - *this).dist2(),
		  aa = (_0 - *this).dist2();
		T a = sqrt(aa), b = sqrt(bb); 
		return (aa + bb - c) / (2 * a * b);
	}
	bool angular(const point<T> &_0, const point<T> &_1, const ld &_a) const
	{
		T c = (_1 - _0).dist2(),
		  bb = (_1 - *this).dist2(),
		  aa = (_0 - *this).dist2();
		T a = sqrt(aa), b = sqrt(bb); 
		return sgn((aa + bb - c) - (2 * a * b * _a)) == 0;
	}
};

typedef point<ld> pt;

pt m1, m2, m3, m12, m23;
pt o1[2], o2[2];
pt ans;
ld a12, a23, r12, r23, l12, l23, c12, c23;

ld cos_the(ld a, ld b, ld c)
{
	return (a * a + b * b - c * c) / (2 * a * b);
}

bool check(pt c1, pt c2)
{
	ld lc = (c2 - c1).dist();
	pt cc = (c2 - c1) / lc, rcc = ~cc;
	ld cdg1 = cos_the(lc, c12, c23);

#ifdef LOCAL
	cerr << "---checking---\n";
	cerr << c1.x << "," << c1.y << "; " << c2.x << "," << c2.y << endl;
	cerr << "three len = " << c12 << ',' << c23 << ',' << lc << endl;
#endif

	if (sgn(lc - fabs(c12) - fabs(c23)) >= 0) 
	{
		return false;
	}

	if (c1 == c2)
	{
		if (sgn(c12 - c23) == 0)
		{
			ans = c1 + pt(cos(123), sin(123)) * c12;
			return  (ans != m1 && ans != m2 && ans != m3 &&
				ans.angular(m1, m2, cos(a12)) &&
				ans.angular(m2, m3, cos(a23)));
		} else {
			return false;
		}
	}

	ld ln = c12 * cdg1, l2 = sqrt(c12 * c12 - ln * ln);
#ifdef LOCAL
	cerr << "deg = " << acos(cdg1) * 180 / pi << endl;
#endif
	pt tmp;
	tmp = c1 + cc * ln + rcc * l2;
#ifdef LOCAL
	cerr << cos(a12) << ' ' << cos(a23) << endl;
#endif
//	if (fabs(tmp.x) > 1e15 || fabs(tmp.y) > 1e15) {
//		exit(1);
//	}

	if (tmp != m1 && tmp != m2 && tmp != m3 &&
			tmp.angular(m1, m2, cos(a12)) &&
			tmp.angular(m2, m3, cos(a23)))
	{
#ifdef LOCAL
	cerr << "angular : " << tmp.angular(m1, m2) << ' ' << tmp.angular(m2, m3) << endl;
#endif
		ans = tmp;
		return true;
	}

//	if (fabs(tmp.x) > 1e15 || fabs(tmp.y) > 1e15) {
//		exit(1);
//	}

	tmp = c1 + cc * ln - rcc * l2;
	if (tmp != m1 && tmp != m2 && tmp != m3 &&
			tmp.angular(m1, m2, cos(a12)) &&
			tmp.angular(m2, m3, cos(a23)))
	{
#ifdef LOCAL
	cerr << "angular : " << tmp.angular(m1, m2) << ' ' << tmp.angular(m2, m3) << endl;
#endif
		ans = tmp;
		return true;
	}
	return false;
}

bool sol()
{
	cin >> m1.x >> m1.y >> m2.x >> m2.y >> m3.x >> m3.y;
	cin >> a12 >> a23;

	m12 = (m1 + m2) / 2;
	m23 = (m2 + m3) / 2;
	
	r12 = a12 * 2;r23 = a23 * 2;
	if (sgn(r12 - 180) >= 0) r12 = 360 - r12;
	if (sgn(r23 - 180) >= 0) r23 = 360 - r23;
#ifdef LOCAL
	cerr << "deg : " << r12 / 2 << "," << r23 / 2 << endl;
	cerr << "cos " << a12 << " -> " << cos(a12 * pi / 180) << ", " << a23 << " -> " << cos(a23 * pi / 180) << endl;
#endif
	a12 = a12 * (pi / 180);a23 = a23 * (pi / 180);
	r12 = r12 * (pi / 180);r23 = r23 * (pi / 180);
	l12 = (m2 - m1).dist();l23 = (m3 - m2).dist();

	c12 = (l12 / (2 * sin(r12 / 2)));
	c23 = (l23 / (2 * sin(r23 / 2)));
	
	ld vl1, vl2;
	pt v12 = ~(m2 - m1), v23 = ~(m3 - m2);
	vl1 = v12.dist();
//	v12 = v12 / vl;
	vl2 = v23.dist();
//	v23 = v23 / vl;
#ifdef LOCAL
	cerr << "cos 12 = " << cos(r12) << endl;
	cerr << "cos 23 = " << cos(r23) << endl;
#endif
	o1[0] = m12 + v12 / tan(r12 / 2) / 2;
	o1[1] = m12 - v12 / tan(r12 / 2) / 2;
	o2[0] = m23 + v23 / tan(r23 / 2) / 2;
	o2[1] = m23 - v23 / tan(r23 / 2) / 2;
#ifdef LOCAL
	sprintf(buf, "r12 = %.6Lf, r12 ^ 2 = %.6Lf, r23 = %.6Lf, r23 ^ 2 = %.6Lf\n"
			"c1 = (%.6Lf, %.6Lf) or (%.6Lf, %.6Lf)\n"
			"c2 = (%.6Lf, %.6Lf) or (%.6Lf, %.6Lf)\n",
			c12, c12 * c12, c23, c23 * c23,
			o1[0].x, o1[0].y, o1[1].x, o1[1].y,
			o2[0].x, o2[0].y, o2[1].x, o2[1].y);
	cerr << buf << endl;
#endif
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (check(o1[i], o2[j]))
				return true;
	return false;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		if (sol())
		{
			sprintf(buf, "%.10f %.10f", double(ans.x), double(ans.y));
			cout << buf << endl;
		} else {
			exit(-1);
		}
	}
	return 0;
}
}
int main()
{
	ios::sync_with_stdio(0);
	return e::main();
}
