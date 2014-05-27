#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=100005;
const double eps=1e-25;
long long inf=(1LL<<60);

bool _le(double a,double b){return a<b+eps;}
bool _ge(double a,double b){return a>b-eps;}
bool _l (double a,double b){return a<b-eps;}
bool _g (double a,double b){return a>b+eps;}
bool _eq(double a,double b){return fabs(a-b)<eps;}
int  sgn(double a)         {if (a>eps) return 1; else if (a<-eps)return -1; else return 0;}
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
	Point  operator + (Point  b){return Point(x+b.x,y+b.y);}
	Point  operator - (Point  b){return Point(x-b.x,y-b.y);}
	Point  operator * (double b){return Point(x*b,y*b);}
	Point  operator / (double b){return Point(x/b,y/b);}
	double operator * (Point  b){return x*b.x+y*b.y;}
	double operator & (Point  b){return x*b.y-y*b.x;}
}a[2][maxn];int cur;
int cnt[2],pre,n;
void add(Point p)
{
	a[cur][cnt[cur]++]=p;
}
int getdir(Point p,Point q,Point a)
{
	double t=((q-p)&(a-p));
	return sgn(t)>=0;
}
Point X(Point a,Point b,Point p,Point q)
{
	double s1=(a-p)&(b-p);
	double s2=(b-q)&(a-q);
	return (p*s2+q*s1)/(s1+s2);
}
void cut(double k,double b,int pos)
{
	Point p=Point(0,b),q=Point(100,100*k+b);
	cnt[cur]=0;
	a[pre][cnt[pre]]=a[pre][0];
	Point p1,q1;
	int x,y;
	for (int i=0;i<cnt[pre];i++)
	{
		p1=a[pre][i];
		q1=a[pre][i+1];
		x=getdir(p,q,p1)==pos;
		y=getdir(p,q,q1)==pos;
		if (x && y)
			add(p1);
		else if (x)
		{
			add(p1);
			add(X(p,q,p1,q1));
		}else if (y)
		{
			add(X(p,q,p1,q1));
		}
	}
}
int main()
{
	scanf("%d",&n);
	pre=0;cur=1;
	a[0][0]=Point(inf,0);
	a[0][1]=Point(inf,inf);
	a[0][2]=Point(-inf,inf);
	a[0][3]=Point(-inf,0);
	cnt[0]=4;
	double x,y1,y2;
	int ans;
	for (int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&x,&y1,&y2);
		ans=i;
		cut(-x,y1/x,1);swap(pre,cur);
		cut(-x,y2/x,0);swap(pre,cur);
		if (cnt[pre]<=2)
		{
			ans=i-1;
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
