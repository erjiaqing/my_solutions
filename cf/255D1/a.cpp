#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int a[maxn],b_0[maxn],b_1[maxn];
int cansel[maxn];
int n;
int main()
{
	scanf("%d",&n);
	a[0]=maxn,a[n+1]=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b_0[i]=b_1[i]=1;
	}
	for (int i=1;i<=n;i++)
		if (a[i]>a[i-1])
			b_0[i]+=b_0[i-1];
	for (int i=n;i>=1;i--)
		if (a[i]<a[i+1])
			b_1[i]+=b_1[i+1];
	int ans=1;
	for (int i=1;i<=n;i++)
	{
		if (a[i+1]-a[i-1]>1)
			ans=max(ans,b_0[i-1]+1+b_1[i+1]);
		if (i>1)
			ans=max(ans,b_0[i-1]+1);
		if (i<n)
			ans=max(ans,b_1[i+1]+1);
	}
	printf("%d\n",ans);
	return 0;
}
