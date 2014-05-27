//-- 必载库系列
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=50005;
//-- 浮点数运算部分
const double eps=1e-8;
bool _l (double a,double b){return a<b-eps;}
bool _g (double a,double b){return b<a-eps;}
bool _le(double a,double b){return a<b+eps;}
bool _ge(double a,double b){return b<a+eps;}
bool _eq(double a,double b){return fabs(a-b)<eps;}
//-- 向量和点部分
struct Point
{
    double x,y;
    Point(){}
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

    double get(void){return sqrt(x*x+y*y);}
};
double dist (Point a,Point b){return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));}
double dist2(Point a,Point b){return      pow(a.x-b.x,2)+pow(a.y-b.y,2) ;}
typedef Point Vector;
//-- 完毕
Point c[maxn];
bool comp(Point a,Point b)
{
    a=a-c[0];
    b=b-c[0];
    double tmp=a&b;
	if (_ge(tmp,0))
		return 1;
	else if (_eq(tmp,0))
        return _ge(-dist(c[0],a)-dist(c[0],b),0);
    else
        return 0;
}
int n,top;
double ans=1e50;
double len[maxn],h[maxn],ll[maxn],rr[maxn];
double dx,dy;
Point ansp[5];
bool comp2(Point a,Point b)
{
    a=a-ansp[0];
    b=b-ansp[0];
    double tmp=a&b;
    return _g(tmp,0);
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++)
        scanf("%lf%lf",&c[i].x,&c[i].y);
    for (int i=1;i<n;i++)
        if (c[i]<c[0])
            swap(c[i],c[0]);
    sort(&c[1],&c[n],comp);
    top=1;
    for (int i=1;i<n;i++)
    {
        while (_le((c[top-1]-c[top])&(c[i]-c[top]),0)&&top>=1)
            top--;
        c[++top]=c[i];
    }
    c[++top]=c[0];
    n=top;
    int l=0,r=0,t=0;
    for (int i=1;i<n;i++)
    {
        if (_g((c[1]-c[0])&(c[i]-c[0]),(c[1]-c[0])&(c[t]-c[0])))
            t=i;
        if (_g((c[1]-c[0])&(c[i]-c[0]),(c[1]-c[0])&(c[l]-c[0])))
            l=i;
        if (_l((c[1]-c[0])&(c[i]-c[0]),(c[1]-c[0])&(c[r]-c[0])))
            r=i;
    }
    for (int i=0;i<n;i++)
    {
        len[i]=(c[i]-c[i+1]).get();
        while ((t+1)%n!=i  &&_g((c[i+1]-c[i])&(c[t+1]-c[i]),(c[i+1]-c[i])&(c[t]-c[i])))
            (t+=1)%=n;
        h[i]=((c[i+1]-c[i])&(c[t]-c[i]))/len[i];
        while ((l+1)%n!=i  &&_g((c[i+1]-c[i])*(c[l+1]-c[i]),(c[i+1]-c[i])*(c[l]-c[i])))
            (l+=1)%=n;
        ll[i]=(((c[i+1]-c[i])*(c[l]-c[i]))/len[i]);
        while ((r+1)%n!=i+1&&_l((c[i+1]-c[i])*(c[r+1]-c[i]),(c[i+1]-c[i])*(c[r]-c[i])))
            (r+=1)%=n;
        rr[i]=((c[i+1]-c[i])*(c[r]-c[i]))/len[i];
    }
    for (int i=0;i<n;i++)
        ans=min((ll[i]-rr[i])*h[i],ans);
    //ans=fabs(ans);
    for (int i=0;i<n;i++)
    {
        if (_eq((ll[i]-rr[i])*h[i],ans))
        {
            ansp[0]=Point(c[i].x+ll[i]*(c[i+1].x-c[i].x)/len[i],
                          c[i].y+ll[i]*(c[i+1].y-c[i].y)/len[i]);
            ansp[1]=Point(c[i].x+rr[i]*(c[i+1].x-c[i].x)/len[i],
                          c[i].y+rr[i]*(c[i+1].y-c[i].y)/len[i]);
            dx=-(c[i+1].y-c[i].y)*h[i]/len[i];
            dy= (c[i+1].x-c[i].x)*h[i]/len[i];
            ansp[2]=Point(ansp[0].x+dx,ansp[0].y+dy);
            ansp[3]=Point(ansp[1].x+dx,ansp[1].y+dy);
            break;
        }
    }
    //cerr<<"***"<<ans<<endl;
    printf("%.5f\n",fabs(ans));
    for (int i=1;i<4;i++)
        if (_eq(ansp[i].y,ansp[0].y)?_l(ansp[i].x,ansp[0].x):_l(ansp[i].y,ansp[0].y))
            swap(ansp[i],ansp[0]);
    sort(&ansp[1],&ansp[4],comp2);
    for (int i=0;i<4;i++)
        //cout<<ansp[i].x<<" "<<ansp[i].y<<endl;
        printf("%.5f %.5f\n",ansp[i].x+eps,ansp[i].y+eps);
    return 0;
}
