#include <bits/stdc++.h>
using namespace std;

const int maxn=305;

const double eps=1e-8,inf=1e20;
inline bool _l (const double &_a,const double &_b){return _a<_b-eps;}
inline bool _le(const double &_a,const double &_b){return _a<_b+eps;}
inline bool _eq(const double &_a,const double &_b){return fabs(_a-_b)<eps;}
inline bool _ge(const double &_a,const double &_b){return _b<_a+eps;}
inline bool _g (const double &_a,const double &_b){return _b<_a-eps;}
struct Point{
	double x,y;
	Point(){}
	Point(const double &_x,const double &_y):x(_x),y(_y){}
	Point(const Point &_p):x(_p.x),y(_p.y){}
	friend bool operator < (const Point &_a,const Point &_b)
	{return _l(_a.x,_b.x) || (_eq(_a.x,_b.x) && _l(_a.y,_b.y));}
	friend bool operator ==(const Point &_a,const Point &_b)
	{return _eq(_a.x,_b.x) && _eq(_a.y,_b.y);}
	friend Point operator +(const Point &_a,const Point &_b)
	{return Point(_a.x+_b.x,_a.y+_b.y);}
	friend Point operator -(const Point &_a,const Point &_b)
	{return Point(_a.x-_b.x,_a.y-_b.y);}
	friend double operator *(const Point &_a,const Point &_b)
	{return _a.x*_b.y-_a.y*_b.x;}
	friend double operator /(const Point &_a,const Point &_b)
	{return _a.x*_b.x+_a.y*_b.y;}
};
typedef Point Vector;
struct Line{
	double k,b;
	Line(){}
	Line(const Point &_a,const Point &_b)
	{k=((_a.y-_b.y)/(_a.x-_b.x)),b=(_a.y-k*_a.x);}
	double gety(const double _x)const{return k*_x+b;}
	friend bool operator <(const Line _a,const Line _b)
	{return _a.k<_b.k || (_a.k==_b.k && _a.b>_b.b);}
	friend Point operator *(const Line _a,const Line _b)
	{return Point(-(_a.b-_b.b)/(_a.k-_b.k),_a.gety(-(_a.b-_b.b)/(_a.k-_b.k)));}
};

Point p[maxn],q[maxn];Line l[maxn],s[maxn];

double x[maxn],y[maxn];

int n,m,top;

double binary_find_h(double x,int l,int r,Point *w)
{
	if (_eq(x,w[l].x)) return w[l].y;
	if (_eq(x,w[r].x)) return w[r].y;
	while (l<r-1)
	{
		int m=(l+r)/2;
		if (_eq(x,w[m].x)) return w[m].y;
		if (_l(x,w[m].x)) r=m; else l=m;
	}
	return Line(w[l],w[r]).gety(x);
}

double get_ans(double x)
{
	return binary_find_h(x,1,m,q)-binary_find_h(x,1,n,p);
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lf",&x[i]);
	for (int i=1;i<=n;i++) scanf("%lf",&y[i]);
	for (int i=1;i<=n;i++) p[i]=Point(x[i],y[i]);
	for (int i=1;i< n;i++) l[++m]=Line(p[i],p[i+1]);
	sort(&l[1],&l[m+1]);
	for (int i=1;i<=m;i++)
	{
		if (_eq(l[i].k,l[i-1].k)) continue;
		while (top>1)
		{
			Point t(s[top]*l[i]);
			if (_ge(s[top-1].gety(t.x),t.y)) top--; else break;
		}
		s[++top]=l[i];
	}
	m=0;
	int l=1,r=top;
	while (l<r)
		if (_le((s[l]*s[l+1]).x,p[1].x)) l++;else break;
	while (l<r)
		if (_ge((s[r]*s[r-1]).x,p[n].x)) r--;else break;
	q[++m]=Point(p[1].x,s[l].gety(p[1].x));
	for (int i=l;i<r;i++)
		q[++m]=s[i]*s[i+1];
	q[++m]=Point(p[n].x,s[r].gety(p[n].x));
	double ans=inf;
	for (int i=1;i<=n;i++) ans=min(ans,get_ans(p[i].x));
	for (int i=1;i<=m;i++) ans=min(ans,get_ans(q[i].x));
	printf("%.3f\n",(ans+eps));
	return 0;
}
