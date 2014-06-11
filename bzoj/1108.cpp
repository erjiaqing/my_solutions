#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long x,y,n,ans(0);
	scanf("%lld",&n);
	for (int i=0;i<n;i++) scanf("%lld%lld",&x,&y),ans+=y-x;
	for (int i=0;i<n;i++) scanf("%lld%lld",&x,&y),ans+=x-y;
	printf("%lld\n",ans);
	return 0;
}
