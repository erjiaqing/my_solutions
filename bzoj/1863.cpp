#include <bits/stdc++.h>
using namespace std;
const int maxn=20005;
int l[maxn],r[maxn],a[maxn],n,ans;
bool check(int k)
{
	l[1]=r[1]=a[1];
	for (int i=2;i<=n;i++)
	{
		l[i]=0,r[i]=a[i];
		r[i]=min(r[i],a[1]-l[i-1]);
		l[i]=max(l[i],a[1]+a[i]+a[i-1]-r[i-1]-k);
	}
	return l[n]==0;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) ans=max(ans,a[i]+a[i+1]);
	int l=ans,r=ans*2;
	while (l<=r)
	{
		int m=(l+r)/2;
		if (check(m)) r=m-1;
		else l=m+1;
	}
	printf("%d\n",l);
	return 0;
}

