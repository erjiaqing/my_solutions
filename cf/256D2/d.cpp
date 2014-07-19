#include <bits/stdc++.h>
using namespace std;
long long n,m,k,l,r,mid;
long long calc(long long val)
{
	long long ret=0;
	for (int i=1;i<=n;i++)
		ret+=min(m,(val-1)/i);
	return ret;
}
int main()
{
	cin>>n>>m>>k;
	l=1,r=n*m;
	k--;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (calc(mid)>k) r=mid;
		else l=mid;
	}
	if (calc(r)>k) cout<<l<<endl;
	else cout<<r<<endl;
	return 0;
}
