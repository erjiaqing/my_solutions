#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=2005,maxm=4005,maxk=1000005;
int bit[2][maxn][maxm],x[maxk],y[maxk];
int n,m,len;
int lowbit(int x)
{
	return x&(-x);
}
void add(int p,int x,int y,int d)
{
	x++;y++;
	for (;x<maxn;x+=lowbit(x))
		for (int i=y;i<maxm;i+=lowbit(i))
			bit[p][x][i]+=d;
}
void update(int t,int c,int l,int r,int d)
{
	x[c]=(t-l*d+n)%n;
	y[c]=r-l;
	add(0,x[c],y[c]+x[c],1);
	add(1,x[c],y[c]-x[c]+n,1);
}
void del(int c)
{
	add(0,x[c],y[c]+x[c],-1);
	add(1,x[c],y[c]-x[c]+n,-1);
}
int sum(int p,int x,int y)
{
	if (x<0||y<0)
		return 0;
	int ret=0;
	if (++x>n)
		x=n+1;
	if (++y>m)
		y=m+1;
	for (;x;x-=lowbit(x))
		for (int i=y;i;i-=lowbit(i))
			ret+=bit[p][x][i];
	return ret;
}
int area(int p,int x1,int y1,int x2,int y2)
{
	return sum(p,x2,y2)+sum(p,x1-1,y1-1)
		  -sum(p,x1-1,y2)-sum(p,x2,y1-1);
}
int ask(int t,int l,int r)
{
	int d=r==len;
	return area(0,t,l+t,t+r,m)+
		   area(0,0,l+t-n,t+r-n-d,m)+
		   area(1,n-r+t+d,l-t,n,m)+
		   area(1,t-r,l-t+n,t-1,m);
}
int main()
{
	int q,t,c,l,r,d,p;
	scanf("%d%d",&q,&len);
	n=len<<1;m=len<<2;
	while (q--)
	{
		scanf("%d%d",&p,&t);
		if (p==1)
		{
			scanf("%d%d%d%d",&c,&l,&r,&d);
			update(t,c,l,r,d);
		}else if (p==2)
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",ask(t%n,l,r));
		}else
		{
			scanf("%d",&c);
			del(c);
		}
	}
	return 0;
}
