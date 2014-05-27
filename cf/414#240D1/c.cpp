#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=22;
int num[1<<22],tnum[1<<22];
long long rev[maxn],ans[maxn],s[maxn];
void divide(int l,int r,int lay)
{
	if (l==r)
		return;
	int mid=(l+r)>>1;
//	printf("%d %d %d\n",l,r,mid);
	divide(l,mid,lay-1);
	divide(mid+1,r,lay-1);
	int tl=l,tr;
	for (tr=mid+1;tr<=r;tr++)
	{
		while (tl<=mid && num[tl]<=num[tr]) tl++;
		ans[lay]+=mid-tl+1;
	}
	tl=l;
	for (tr=mid+1;tr<=r;tr++)
	{
		while (tl<=mid && num[tl]<num[tr]) tl++;
		rev[lay]+=tl-l;
	}
	tl=l;tr=mid+1;
	for (int i=l;i<=r;i++)
		if ((tr>r) || (tl<=mid && num[tl]<=num[tr]))
			tnum[i]=num[tl++];
		else
			tnum[i]=num[tr++];
	for (int i=l;i<=r;i++)
		num[i]=tnum[i];
}
int main()
{
	int n;
//	ios::sync_with_stdio(0);
	scanf("%d",&n);
//	cin>>n;
	for (int i=0;i<(1<<n);i++)
		scanf("%d",&num[i]);
//		cin>>num[i];
//		rnum[(1<<n)-1-i]=num[i];
	divide(0,(1<<n)-1,n);
	for (int i=0;i<=n;i++)
		s[i]=ans[i]+rev[i];
	long long a=0;
	int q,p;
//	cerr<<a<<endl;
	scanf("%d",&q);
//	cin>>q;
	while (q--)
	{
//		cin>>p;
		a=0;
		scanf("%d",&p);
		for (int i=0;i<=p;i++)
			ans[i]=s[i]-ans[i];
		for (int i=0;i<=n;i++)
			a+=ans[i];
//		cout<<a<<endl;
		printf("%lld\n",a);
	}
	return 0;
}
