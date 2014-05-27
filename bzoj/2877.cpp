#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int rp=0,n,m,x,y,t,mask1,mask2,bit2;
long long a[9000005];
inline int pos(int x,int y)
{
	return ((((x|mask1)<<bit2)|mask2|y));
}
long long gcd(long long a,long long b)
{
	if (a<0) a=-a;
	if (b<0) b=-b;
	long long c;
	//cerr<<"GCD\n";
	while (b)
		c=a%b,a=b,b=c;
	return a;
}
void build1()
{
	for (int i=mask1-1;i;i--)
		for (int j=mask2|(m-1);j;j--)
			a[(i<<bit2)|j]=gcd(a[(i<<(1+bit2))|j],a[(((i<<1)+1)<<bit2)|j]);
}
void build2(int mask)
{
	for (int i=mask2-1;i;i--)
		a[mask|i]=gcd(a[mask|(i<<1)],a[mask|((i<<1)|1)]);
}
long long lq(int mask,int x1,int x2)
{
	mask<<=bit2;
	//printf("f:lq %d %d %d\n",mask,x1,x2);
	long long ans=gcd(a[mask|x1],a[mask|x2]);
	for (;x1>>1!=x2>>1;x1>>=1,x2>>=1)
	{
		//printf("f:lq %d %d\n",x1,x2);
		if (!(x1&1))
			ans=gcd(ans,a[mask|(x1^1)]);
		if ( (x2&1))
			ans=gcd(ans,a[mask|(x2^1)]);
	}
	return ans;
}
long long q(int x1,int y1,int x2,int y2)
{
	x1|=mask1;x2|=mask1;
	y1|=mask2;y2|=mask2;
	//printf("f: q %d %d %d %d\n",x1,y1,x2,y2);
	long long ans=gcd(lq(x1,y1,y2),lq(x2,y1,y2));
	for (;x1>>1!=x2>>1;x1>>=1,x2>>=1)
	{
		if (!(x1&1))
			ans=gcd(ans,lq(x1^1,y1,y2));
		if ( (x2&1))
			ans=gcd(ans,lq(x2^1,y1,y2));
	}
	return ans;
}
void M(int x,int y,long long c)
{
	if (x<0||y<0||x>=n||y>=m)
		return;
	int mask=(mask1|x)<<bit2;
	a[pos(x,y)]+=c;
	for (int j=(mask2|y)>>1;j;j>>=1)
		a[mask|j]=gcd(a[mask|(j<<1)],a[mask|(j<<1)|1]);
	for (int i=(mask1|x)>>1;i;i>>=1)
		for (int j=mask2|y;j;j>>=1)
			a[(i<<bit2)|j]=gcd(a[(i<<(bit2+1))|j],a[(((i<<1)+1)<<bit2)|j]);
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&t);
	for (mask1=1;mask1<n;mask1<<=1);
	for (mask2=1,bit2=1;mask2<m;mask2<<=1,bit2++);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf("%lld",&a[pos(i,j)]);
	x--;y--;
	for (int i=0;i<x;++i)
		for (int j=0;j<y;++j)
			a[pos(i,j)]+=a[pos(i+1,j+1)]-a[pos(i,j+1)]-a[pos(i+1,j)];
	for (int i=n-1;i>x;--i)
		for (int j=0;j<y;++j)
			a[pos(i,j)]+=a[pos(i-1,j+1)]-a[pos(i,j+1)]-a[pos(i-1,j)];
	for (int i=0;i<x;++i)
		for (int j=m-1;j>y;--j)
			a[pos(i,j)]+=a[pos(i+1,j-1)]-a[pos(i,j-1)]-a[pos(i+1,j)];
	for (int i=n-1;i>x;--i)
		for (int j=m-1;j>y;--j)
			a[pos(i,j)]+=a[pos(i-1,j-1)]-a[pos(i,j-1)]-a[pos(i-1,j)];
	for (int i=0;i<x;++i)
		a[pos(i,y)]-=a[pos(i+1,y)];
	for (int i=n-1;i>x;--i)
		a[pos(i,y)]-=a[pos(i-1,y)];
	for (int j=0;j<y;++j)
		a[pos(x,j)]-=a[pos(x,j+1)];
	for (int j=m-1;j>y;--j)
		a[pos(x,j)]-=a[pos(x,j-1)];
	for (int i=0;i<n;++i)
		build2((mask1|i)<<bit2);
	build1();
	int op,x1,x2,y1,y2;
	long long c;
	while (t--)
	{
		//printf("233\n");
		scanf("%d%d%d%d%d",&op,&x1,&y1,&x2,&y2);
		if (op)
		{
			x1--;x2--;y1--;y2--;
			scanf("%lld",&c);
			if (x1<=x && y1<=y) M(x1-1,y1-1, c); else
			if (x1> x && y1> y) M(x1  ,y1  , c); else
			if (x1<=x && y1> y) M(x1-1,y1  ,-c); else
			if (x1> x && y1<=y) M(x1  ,y1-1,-c);
			//EJQISMOE233
			if (x1<=x && y2>=y) M(x1-1,y2+1, c); else
			if (x1<=x && y2< y) M(x1-1,y2  ,-c); else
			if (x1> x && y2>=y) M(x1  ,y2+1,-c); else
			if (x1> x && y2< y) M(x1  ,y2  , c);
			//EJQISMOE233
			if (x2>=x && y1<=y) M(x2+1,y1-1, c); else
			if (x2>=x && y1> y) M(x2+1,y1  ,-c); else
			if (x2< x && y1<=y) M(x2  ,y1-1,-c); else
			if (x2< x && y1> y) M(x2  ,y1  , c);
			//EJQISMOE233
			if (x2>=x && y2>=y) M(x2+1,y2+1, c); else
			if (x2>=x && y2< y) M(x2+1,y2  ,-c); else
			if (x2< x && y2>=y) M(x2  ,y2+1,-c); else
			if (x2< x && y2< y) M(x2  ,y2  , c);
			//EJQISMOE233
			if (x1<=x && x2>=x)
			{
				if (y1<=y) M(x   ,y1-1,-c); else
					       M(x   ,y1  , c);
				if (y2>=y) M(x   ,y2+1,-c); else
					       M(x   ,y2  , c);
			}
			//EJQISMOE233
			if (y1<=y && y2>=y)
			{
				if (x1<=x) M(x1-1,y,-c); else
					       M(x1  ,y, c);
				if (x2>=x) M(x2+1,y,-c); else
					       M(x2  ,y, c);
			}
			if (x1<=x && x2>=x && y1<=y && y2>=y)
				M(x,y,c);
		}else
		{
			x1=x-x1,y1=y-y1;
			x2=x+x2,y2=y+y2;
			printf("%lld\n",q(x1,y1,x2,y2));
		}
	}
	return 0;
}
