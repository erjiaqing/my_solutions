#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
long long c[maxn],m,n,t;
int main()
{
	scanf("%lld%lld",&m,&n);
	t=min(m,n);
	for (int i=2;i<=t;i++)
		c[i]=(n/i)*(m/i);
	for (int i=t;i>=1;i--)
		for (int j=2;j*i<=t;j++)
			c[i]-=c[i*j];
	long long ans=0;
	for (int i=1;i<=t;i++)
		ans+=2*(i-1)*c[i];
	printf("%lld\n",ans+m*n);
	return 0;
}
