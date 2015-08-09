#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-2;
const int maxn = 1000 + 5;
const double _pi_ = acos(-1);
bool _l (double a , double b){return a < b - eps;}
bool _g (double a , double b){return b < a - eps;}
bool _le(double a , double b){return a < b + eps;}
bool _ge(double a , double b){return b < a + eps;}
bool _eq(double a , double b){return fabs(a - b) < eps;}

struct Point
{
	double x , y;
	Point() {}
	Point(double _x , double _y):x(_x) , y(_y){}
	Point(pair<double , double> _a):x(_a.first) , y(_a.second){}
	Point operator - (Point a){return Point(x - a.x , y - a.y);}
	bool operator == (Point a){return _eq(a.x , x) && _eq(a.y , y);}
	bool operator != (Point a){return ((*this) == a);}
	double operator * (Point a){return x * a.y - y * a.x;}
};

struct Line
{
//	Point a , b;
	double k , b;
	bool flg;
	Line(){flg = false;}
	Line( Point _a , Point _b )
	{
		flg = false;
//		a = _a;
//		b = _b;
		if (_a.x == _b.x)
		{
			flg = true;
			b = _a.x;
		}else
		{
			k = (_b.y - _a.y)/(_b.x - _a.x);
			b = (_b.y - k * _b.x);
		}
	}
	Point operator * (Line _a)
	{
		double rx , ry;
		if (_eq(k , _a.k))
		{
			return Point(1e8 , 1e8);
		}
		/*
		if ( _a.flg && flg )
		{
			return Point(1e8 , 1e8);
		}
		else if ( _a.flg )
		{
			ry = k * _a.b;
			rx = _a.b;
		}
		else if ( flg )
		{
			ry = b * _a.k;
			rx = b;
		}
		else
		{*/
		rx = (_a.b - b) / (k - _a.k);
		ry = k * rx + b;
		return Point(rx , ry);
	}
};

Point P[maxn];
Point P2[maxn];
int n , tn , tn2;
double s1 , s2;
void work()
{
	memset(P , 0 , sizeof(P));
	memset(P2 , 0 , sizeof(P2));
	n = tn = tn2 = 0;
	s1 = s2 = 0;
	scanf("%d" , &n);
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%lf%lf" , &P[tn].x , &P[tn].y);
		if (i == 1)
		{
			tn++;
			P[tn].x = (P[0].x + P[1].x) / 2;
			P[tn].y = (P[0].y + P[1].y) / 2;
			swap(P[2] , P[1]);
		}
		tn++;
	}
/*	for (int i = 0 ; i < tn ; i++)
	{
		printf("%.6f %.6f\n" , P[i].x , P[i].y);
	}*/
	P[tn] = P[0];
	for (int i = 0 ; i <= tn ; i++)
	{
		double r = sqrt(P[i].x * P[i].x + P[i].y * P[i].y);
		double deg = atan2(P[i].y , P[i].x) + sqrt(2);
		P[i] = Point(r * cos(deg) , r * sin(deg));
	}
/*
	for (int i = 0 ; i < tn ; i++)
	{
	     printf("%.6f %.6f\n" , P[i].x , P[i].y);
	}
*/
	for (int i = 0 ; i < tn ; i++)
	{
		s1 += (P[i + 1] - P[i]) * (P[i] - P[0]);
//		cerr << s1 << endl;
	}
//	cerr << s1 << endl;
	bool flg = false;
	double k1 , b1 , k2 , b2;
	Line lin , lout;
	Line La = Line(P[0] , P[2]);
	
	k1 = tan(atan(La.k) + _pi_ / 4);
	b1 = P[1].y - k1 * P[1].x;
	k2 = tan(atan(La.k) - _pi_ / 4);
	b2 = P[1].y - k2 * P[1].x;
	
	lin.k = k1;
	lin.b = b1;
	lout.k = k2;
	lout.b = b2;
	
	P2[tn2++] = P[1];
	for (int i = 3 ; i <= tn ; i++)
	{
		Line L(P[i - 1] , P[i]);
//		printf("{%d} (%.2f %.2f) -> (%.2f %.2f)\n" , i , P[i-1].x,P[i-1].y,
//				P[i].x,P[i].y);
		if (flg)
			P2[tn2++] = P[i - 1];
		if (!flg)
		{
			Point tp = lin * L;
			if (_le(min(P[i - 1].x , P[i].x) , tp.x) &&
				_le(tp.x , max(P[i - 1].x , P[i].x)))
			{
//				printf(" > %.6f %.6f\n" , tp.x , tp.y);
				P2[tn2++] = tp;
				flg = true;
			}
			//flg = true;
		}
		if (flg)
		{
             Point tp = lout * L;
		//	 printf(" < %.6f %.6f\n" , tp.x , tp.y);
             if (_le(min(P[i - 1].x , P[i].x) , tp.x) &&
                _le(tp.x , max(P[i - 1].x , P[i].x)))
			 {
//				 printf(" < %.6f %.6f\n" , tp.x , tp.y);
                 P2[tn2++] = tp;
				 flg = false;
				 break;
             }

		}
	}
//	cerr << "\n";
//	for (int i = 0  ; i < tn2 ; i++)
//		printf("%.6f %.6f\n" , P2[i].x , P2[i].y);
	P2[tn2] = P[1];
	for (int i = 0 ; i < tn2 ; i++)
		s2 += (P2[i + 1] - P2[i]) * (P2[i] - P[1]);
	printf("%.6f\n" , s2 / s1);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
}
