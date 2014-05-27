#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps=1e-8;
const int maxn=1505;
bool _eq(double a,double b){return fabs(a-b)<eps;}
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):
		x(_x),y(_y){}
	Point operator - (Point b){return Point(x-b.x,y-b.y);}
	Point operator + (Point b){return Point(x+b.x,y+b.y);}
	Point operator / (double c){return Point(x/c,y/c);}
	friend double Dist(Point &a,Point &b)
	{
		return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	}
};
bool _eq(Point a,Point b){return _eq(a.x,b.x)&&_eq(a.y,b.y);}
bool _l (Point a,Point b){return (_eq(a.x,b.x)?(a.y<b.y):(a.x<b.x));}
struct Line
{
	Point a,b,cen;
	double len;
	Line(){}
	Line(Point _a,Point _b)
	{
		a=_a;b=_b;
		cen=(a+b)/2;
		len=Dist(a,b);
	}
}l[maxn*maxn];
bool comp(Line a,Line b)
{
	return _l(a.cen,b.cen);
}
int lnt=0,n;
double ans=0;
int x[maxn],y[maxn];
int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d%d",&x[i],&y[i]);
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (x[i]!=x[j] || y[i]!=y[j])
				l[lnt++]=Line(Point(x[i],y[i]),Point(x[j],y[j]));
	sort(&l[0],&l[lnt],comp);
	for (int i=0;i<lnt;i++)
		for (int j=i+1;_eq(l[i].cen,l[j].cen);j++)
			if (_eq(l[i].len,l[j].len) && _eq(l[i].cen,l[j].cen))
				ans=max(ans,Dist(l[i].a,l[j].a)*Dist(l[i].a,l[j].b));
	printf("%0.lf\n",ans);
	return 0;
}
