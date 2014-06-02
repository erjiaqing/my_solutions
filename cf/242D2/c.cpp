#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int f[1000005];
int main()
{
	int imod=0,q=0,p=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		f[i]=f[i-1]^i;
	for (int i=1;i<=n;i++)
		scanf("%d",&p),q^=(p^(((n/i)&1)?(f[i-1]^f[n%i]):(f[n%i])));
	printf("%d\n",q);
	return 0;
}
