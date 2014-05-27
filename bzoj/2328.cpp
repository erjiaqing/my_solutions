#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps=1e-12;
bool _le(double a,double b){return a<b+eps;}
bool _l (double a,double b){return a<b-eps;}
bool _eq(double a,double b){return fabs(a-b)<eps;}
bool _g (double a,double b){return b<a-eps;}
bool _ge(double a,double b){return b<a+eps;}
double a,b,vmax,f,tdx,tdy;
int n,up;
struct seg{
	/**
	 * struct Seg(ment)
	 * dx -> delta x
	 * dy -> delta y
	 * k  -> dy/dx
	 * d  -> lenth sqrt(dx^2+dy^2)
	 * s  -> speed
	 */
	double dx,dy,k,d,s;
	seg(){}
	seg(double _dx,double _dy)
	{
		dx=_dx;dy=_dy;
		k=dy/dx;
		d=sqrt(dy*dy+dx*dx);
		if (_ge(k,0))
			s=0,up=1;
		else
			s=min(vmax,-b*k/a);
	}
}road[10005];
bool comp(seg x,seg y)
{
	return x.s<y.s;
}
void work()
{
	scanf("%lf%lf%lf%lf",&a,&b,&vmax,&f);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%lf%lf",&tdx,&tdy),road[i]=seg(tdx/1000,tdy/1000);
	for (int i=0;i<n;i++)
		f-=max(0.0,b*road[i].k+a*road[i].s)*road[i].d;
//	printf("%lf\n",f);
	if (_l(f,0.0) || (_eq(f,0.0)&&up))
	{
		printf("IMPOSSIBLE\n");
		return;
	}
	sort(&road[0],&road[n],comp);
	double nowv=road[0].s,nowd=road[0].d;
	for (int i=1;i<n;i++)
	{
		double df=(road[i].s-nowv)*a*nowd;
		if (_le(f-df,0.0))
		{
			nowv=nowv+f/a/nowd;
			double ans=nowd/nowv;
			for (int j=i;j<n;j++)
				ans=ans+road[j].d/road[j].s;
			printf("%.5lf\n",ans);
			return;
		}
		nowv=road[i].s;nowd+=road[i].d;f-=df;
	}
	nowv=min(vmax,nowv+f/a/nowd);
	printf("%.5lf\n",nowd/nowv);
}
void clear()
{
	memset(road,0,sizeof(road));
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		up=0;
		clear();
		work();
	}
	return 0;
}
