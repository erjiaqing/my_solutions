#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
#include <cmath>
using namespace std;
const double eps=1e-12;
bool _g (double a,double b){return a>b+eps;}
bool _l (double a,double b){return a<b-eps;}
bool _ge(double a,double b){return a>b-eps;}
bool _le(double a,double b){return a<b+eps;}
bool _eq(double a,double b){return fabs(a-b)<eps;}
typedef pair<double,int> di;
priority_queue<pair<double,int> >delta_p;
priority_queue<pair<double,int> >delta_m;
const int maxn=10005;

int n;
double E,T=0;
double Eu[maxn],Eua[maxn],Eub[maxn];
double Ti[maxn],Tia[maxn],Tib[maxn];
double s[maxn],k[maxn],v[maxn];
double delta=0;
double calc_time(double eu,double si,double ki,double vi)
{
	return si/max(sqrt(eu/(si*ki))+vi,vi-sqrt(eu/(si*ki)));
}
void make_heap()
{
	while (!delta_p.empty())
		delta_p.pop();
	while (!delta_m.empty())
		delta_m.pop();
	for (int i=1;i<=n;i++)
	{
		Eua[i]=Eu[i]+delta;Eub[i]=Eu[i]-delta;
		Tia[i]=calc_time(Eua[i],s[i],k[i],v[i]);
		if (Tia[i]>0)
			delta_p.push(di(Ti[i]-Tia[i],i));
		if (Eub[i]>0)
		{
			Tib[i]=calc_time(Eub[i],s[i],k[i],v[i]);
			if (Tib[i]>0)
				delta_m.push(di(Ti[i]-Tib[i],i));
		}
	}
}
void work()
{
	di topa,topb;
	double tma=0,tmb=0;
	int pna=0,pnb=0;
	while (1)
	{
//		printf("%.6lf\n",T);
		make_heap();
		if (delta_p.empty()||delta_m.empty())
		{
			delta*=0.9;
			continue;
		}
		topa=delta_p.top();delta_p.pop();
		topb=delta_m.top();delta_m.pop();
		while (_g(topa.first+topb.first,0))
		{
			tma=topa.first;pna=topa.second;
			tmb=topb.first;pnb=topb.second;
			T=T-tma-tmb;
			Ti[pna]=Tia[pna];Eu[pna]=Eua[pna];
			Ti[pnb]=Tib[pnb];Eu[pnb]=Eub[pnb];
			if (delta_p.empty()||delta_m.empty())
				break;
			topa=delta_p.top();delta_p.pop();
			topb=delta_m.top();delta_m.pop();
		}
		delta*=0.9;
		if (delta<eps)
			break;
	}
}
int main()
{
	scanf("%d%lf",&n,&E);
	double anE=E;
	delta=E/n;
	for (int i=1;i<n;i++)
	{
		scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
		Eu[i]=k[i]*s[i]*pow(v[i]-max(v[i],50.0),2);
		Ti[i]=calc_time(Eu[i],s[i],k[i],v[i]);
		anE-=Eu[i];
		T+=Ti[i];
	}
	scanf("%lf%lf%lf",&s[n],&k[n],&v[n]);
	Eu[n]=anE;
	Ti[n]=calc_time(Eu[n],s[n],k[n],v[n]);
	T+=Ti[n];
//	printf("%.6lf\n",T);
	work();
	printf("%.6lf\n",T);
	return 0;
}
