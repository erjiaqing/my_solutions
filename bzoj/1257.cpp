#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long n,k,ans;
int main()
{
	scanf("%lld%lld",&n,&k);
	for (long long i=1;i<=n;)
	{
		if (i>k)
		{
			ans+=(n-i+1)*k;
			break;
		}
		long long pos=min(k/(k/i),n);
		ans+=(k*(pos-i+1)-(k/i)*(pos-i+1)*(i+pos)/2);
		i=pos+1;
	}
	printf("%lld\n",ans);
	return 0;
}
