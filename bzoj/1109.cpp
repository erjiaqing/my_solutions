#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
typedef pair<int,int> pii;
int a[maxn];
pii s[maxn];
int n,k,r,c=0;
int q[maxn];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&r);
		if (r<=i)
			s[c++]=pii(i-r,r);
	}
	sort(&s[0],&s[c]);
	for (int i=0;i<c;i++)
	{
		int x=s[i].second;
		if (!k || q[k-1]<x){q[k++]=x;continue;}
		int l=-1,r=k-1,m;
		while (l<r-1)
			if (q[m=(l+r+1)/2]<x)
				l=m;
			else if (q[m]>x)
				r=m;
			else
			{
				r=m;
				break;
			}
		if (q[r]!=x)
			q[r]=x;
	}
	printf("%d\n",k);
	return 0;
}
