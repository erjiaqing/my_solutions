#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m,x,y,z,p;
int u,v,u0,v0;
int n0,m0,x0,y0,z0;
int main()
{
	scanf("%d%d%d%d%d%d",&n,&m,&x,&y,&z,&p);
	n0=n;m0=m;
	x&=3;y&=1;z*=3;z&=3;
	x0=x;y0=y;z0=z;
	while (p--)
	{
		n=n0,m=m0;
		x=x0;y=y0;z=z0;
		scanf("%d%d",&u,&v);
//		u0=u;v0=v;
		while (x--)
		{
			u0=u;
			u=v;
			v=n-u0+1;
			swap(m,n);
		}
		if (y)
		{
			v=m-v+1;
		}
//		u0=u;v0=v;
		while (z--)
		{
			u0=u;
			u=v;
			v=n-u0+1;
			swap(m,n);
		}
		printf("%d %d\n",u,v);
	}
	return 0;
}
