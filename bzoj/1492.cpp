#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;
const double eps=1e-8,inf=1e20;
const int maxn=100005;
double f[maxn];
int st[maxn];
struct query{
	double q,a,b,rate,k;
	int pos;
}q[maxn],nq[maxn];
struct point{
	double x,y;
	friend bool operator < (const point &a,const point &b)
	{
		return ((a.x<b.x-eps)||((fabs(a.x-b.x)<eps)&&(a.y<b.y-eps)));
	}
}p[maxn],np[maxn];
double getk(int i,int j)
{
	if (j==0)
		return inf;
	if (i==0 || (fabs(p[i].x-p[j].x)<eps))
		return -inf;
	return (p[i].y-p[j].y)/(p[i].x-p[j].x);
}
void solve(int l,int r)
{
	if (l==r)
	{
		f[l]=max(f[l],f[l-1]);
		p[l].y=f[l]/(q[l].a*q[l].rate+q[l].b);
		p[l].x=p[l].y*q[l].rate;
		return;
	}
	int mid=(l+r)/2;
	int l1=l,l2=mid+1;
	for (int i=l;i<=r;i++)
		if (q[i].pos<=mid)
			nq[l1++]=q[i];
		else
			nq[l2++]=q[i];
	for (int i=l;i<=r;i++)
		q[i]=nq[i];
	solve(l,mid);
	int top=0;
	for (int i=l;i<=mid;i++)
	{
		while (top>=2 && getk(i,st[top])+eps>getk(st[top],st[top-1]))
			top--;
		st[++top]=i;
	}
	int j=1;
	for (int i=r;i>=mid+1;i--)
	{
		while (j<top && q[i].k<getk(st[j],st[j+1])+eps)
			j++;
		f[q[i].pos]=max(f[q[i].pos],p[st[j]].x*q[i].a+p[st[j]].y*q[i].b);
	}
	solve(mid+1,r);
	l1=l;l2=mid+1;
	for (int i=l;i<=r;i++)
		if ((p[l1]<p[l2] || l2>r)&&l1<=mid)
			np[i]=p[l1++];
		else
			np[i]=p[l2++];
	for (int i=l;i<=r;i++)
		p[i]=np[i];
}
bool comp(query a,query b)
{
	return a.k<b.k;
}
int main()
{
	int n;
	scanf("%d%lf",&n,&f[0]);
	for (int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&q[i].a,&q[i].b,&q[i].rate);
		q[i].k=-q[i].a/q[i].b;
		q[i].pos=i;
	}
	sort(&q[1],&q[n+1],comp);
	solve(1,n);
	printf("%.3lf\n",f[n]);
	return 0;
}
