#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
const int maxn=205;
int a[maxn],b[maxn];
int n,k;
int check(int l,int r)
{
	int tmp=0,ans=0;
	priority_queue<int> H;
	for (int i=1;i<l;i++)
		H.push(a[i]);
	for (int i=l;i<=r;i++)
		b[i]=a[i];
	for (int i=r+1;i<=n;i++)
		H.push(a[i]);
	sort(&b[l],&b[r+1]);
	for (int i=l,j=1;i<=r && j<=k && !H.empty();i++,j++)
	{
		tmp=H.top();
		if (b[i]<tmp)
		{
			b[i]=tmp;
		}else
		{
			break;
		}
		H.pop();
	}
	for (int i=l;i<=r;i++)
		ans+=b[i];
	return ans;
}
int main()
{
	int ans=-9999;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
			ans=max(ans,check(i,j));
	printf("%d\n",ans);
	return 0;
}
