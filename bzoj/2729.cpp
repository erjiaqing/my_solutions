#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod=100000000;
long long a[2005];
int n,m;
void X(int x)
{
	for (int i=1;i<=a[0];i++)
		a[i]*=x;
	for (int i=1;i<=a[0];i++)
	{
		a[i+1]+=a[i]/mod;
		a[i]%=mod;
	}
	while (a[a[0]+1])
		a[0]++;
}
int main()
{
	scanf("%d%d",&n,&m);
	if (n+3<m)
	{
		printf("%d",0);
		return 0;
	}
	a[0]=1;
	a[1]=n*n+3*n+2*m;
	for (int i=1;i<=(n+1);i++)
		X(i);
	for (int j=n+4-m;j<=(n+2);j++)
		X(j);
	printf("%lld",a[a[0]]);
	for (int i=a[0]-1;i>0;i--)
		printf("%08lld",a[i]);
	printf("\n");
	return 0;
}
