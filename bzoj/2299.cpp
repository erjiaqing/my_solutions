#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
long long d;
long long gcd(long long a,long long b)
{
	return (b==0)?(a):(gcd(b,a%b));
}
long long chk(long long x,long long y)
{
	return (x%d==0)&&(y%d==0);
}
int main()
{
	long long a,b,x,y;
	int t;
	scanf("%d",&t);
	while (t--&&(~scanf("%lld%lld%lld%lld",&a,&b,&x,&y)))
	{
		if (a==0&&b==0)
		{
			if (x==0&&y==0)
				printf("Y\n");
			else
				printf("N\n");
		}else
		{
			d=gcd(a,b)*2;
			if (chk(x,y)||chk(x-a,y-b)||chk(x-b,y-a)||chk(x-a-b,y-a-b))
				printf("Y\n");
			else
				printf("N\n");
		}
	}
	return 0;
}
