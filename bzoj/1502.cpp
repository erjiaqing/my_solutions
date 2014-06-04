#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
double sqr(double x) {return x*x;}
struct line{
	double x1,x2,y1,y2;
	line(){}
	line(double _x1,double _x2,double _y1,double _y2):
		x1(_x1),x2(_x2),y1(_y1),y2(_y2){}
}ln[maxn];
double h[maxn],r[maxn],alpha,th,_l,_r,_d;
int n,cln;
double f(double x)
{
	double t=0;
	for (int i=0;i<n;i++)
		if (fabs(x-h[i])<r[i])
			t=max(t,sqrt(sqr(r[i])-sqr(x-h[i])));
	for (int i=0;i<cln;i++)
		if (ln[i].x1<x&&x<ln[i].x2)
			t=max(t,ln[i].y1+(x-ln[i].x1)*(ln[i].y2-ln[i].y1)/(ln[i].x2-ln[i].x1));
	return t;
}
double get_area(double l,double r,double fl,double fmid,double fr,bool ejq)
{
	return (fl+4*fmid+fr)*(r-l)/6;
}
double get_area(double l,double r,double fl,double fmid,double fr)
{
	double mid=(l+r)/2;
	double lm=f((l+mid)/2),rm=f((r+mid)/2);
	double st=get_area(l,r,fl,fmid,fr,233),sl=get_area(l,mid,fl,lm,fmid,233),sr=get_area(mid,r,fmid,rm,fr,233);
	if (fabs(st-sl-sr)<1e-4)
		return st;
	else
		return get_area(l,mid,fl,lm,fmid)+get_area(mid,r,fmid,rm,fr);
}
int main()
{
	scanf("%d%lf",&n,&alpha);
	alpha=1.0/tan(alpha);
//	scanf("%lf",&th);
	for (int i=0;i<=n;i++)
		scanf("%lf",&h[i]),th+=h[i],h[i]=th*alpha;
	for (int i=0;i<n;i++)
		scanf("%lf",&r[i]),_l=min(_l,h[i]-r[i]),_r=max(_r,h[i]+r[i]);
//	cerr<<"~\n";
	r[n]=0;_r=max(_r,h[n]);
	for (int i=0;i<n;i++)
	{
		_d=h[i+1]-h[i];
		if (_d>fabs(r[i]-r[i+1]))
			ln[cln++]=line(
					h[i]-r[i]*(r[i+1]-r[i])/_d,
					h[i+1]-r[i+1]*(r[i+1]-r[i])/_d,
					sqrt(sqr(r[i])-sqr(h[i]-r[i]*(r[i+1]-r[i])/_d-h[i])),
					sqrt(sqr(r[i+1])-sqr(h[i+1]-r[i+1]*(r[i+1]-r[i])/_d-h[i+1]))
					);
	}
	printf("%.2lf\n",2*get_area(_l,_r,f(_l),f(_r),f((_l+_r)/2)));
	return 0;
}
