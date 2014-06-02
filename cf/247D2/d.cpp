#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long dp[70][70];
long long m;int k;
inline int countBit(long long x)
{
	int ret=0;
	while (x)
		ret+=(x&1),x/=2;
	return ret;
}
inline long long countBitSum(long long x)
{
	int tk=k;
	long long ret=0;
	for (int i=62;i>=0 && tk;i--) if (x&(1ll<<i)) ret+=dp[i][tk--];
	ret+=(countBit(x)==k);
	return ret;
}
int main()
{
	dp[0][0]=1;
	for (int i=1;i<=64;i++)
		for (int j=0;j<=i;j++)
			dp[i][j]=dp[i-1][j]+(j?dp[i-1][j-1]:0);
	scanf("%lld%d",&m,&k);
	long long l=1,r=(1ll<<62)-1,mid,tmp;
	while (l<r)
	{
		mid=l+(r-l)/2;
//		cerr<<mid<<endl;
		tmp = countBitSum(mid*2)-countBitSum(mid);
		if (tmp<m)
			l=mid+1;
		else
			r=mid;
	}
	printf("%lld\n",l);
	return 0;
}
