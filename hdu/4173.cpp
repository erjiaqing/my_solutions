#include <bits/stdc++.h>
using namespace std;
const int maxn = 200 + 5;
const double eps = 1e-8;
struct Point {
	double x , y;
	Point(){}
	Point( const double & _x , const double & _y ):
		x ( _x ) , y ( _y ){}
}p[maxn];
inline double sqr(const double x)
{
	return x * x;
}
inline double dest(const Point &a , const Point &b)
{
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
int n;
void work()
{
	int ans = 1;
	for (int i = 0 ; i < n ; i++)
		scanf("%lf%lf" , &p[i].x , &p[i].y);
	for (int i = 0 ; i < n ; i++)
		for (int j = i + 1 ; j < n ; j++)
		{
			double d = dest(p[i] , p[j]);
			if (d > 5 + eps)
				continue;
			Point m((p[i].x + p[j].x) / 2 , (p[i].y + p[j].y) / 2);
			d /= 2;
			double d2 = sqrt(sqr(2.5) - sqr(d));
			double r = d2 / d;
			Point c1(m.x + ( m.y - p[i].y ) * r , m.y - ( m.x - p[i].x ) * r );
			Point c2(m.x - ( m.y - p[i].y ) * r , m.y + ( m.x - p[i].x ) * r );
			int tans = 0;
			for (int k = 0 ; k < n ; k++)
				if (dest(c1 , p[k]) < 2.5 + eps)
					tans++;
			ans = max(ans , tans);
			tans = 0;
			for (int k = 0 ; k < n ; k++)
				if (dest(c2 , p[k]) < 2.5 + eps)
					tans++;
			ans = max(ans , tans);
		}
	printf("%d\n" , ans);
}
int main()
{
	while (~scanf("%d" , &n)) work();
	return 0;
}
